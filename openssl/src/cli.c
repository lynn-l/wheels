/*serv.c*/
/*
 *This file implement some modules that the TLS client need sometimes.
 */

#include "general_api.h"
#include "ssl_api.h"

#define buflen 1024 * 100

char *servAddr = "127.0.0.1";

int main()
{
	int fd = -1;
	struct sockaddr_in serv_addr;
	SSL_CTX *ctx = NULL;
	SSL *ssl = NULL;
	char requestBuf[buflen] = {0};
	char responseBuf[buflen] = {0};
	int ret = 0;

	INIT_SSL();

	if ((fd = socket (AF_INET, (int)SOCK_STREAM, 0)) < 0) {
		perror("socket:");
		goto ERROR;
	}
	
	serv_addr.sin_family = AF_INET;
	inet_aton(servAddr, &serv_addr.sin_addr);
	serv_addr.sin_port = htons(5443);
	
	if(connect(fd,	(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect:");
		goto ERROR;
	}
	
	ctx = SSL_CTX_new(TLSv1_method());
	if(ctx == NULL) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}
	
	ssl = SSL_new(ctx);
	if(ssl == NULL) {
		ERR_print_errors_fp(stderr);
		goto ERROR;

	}
	SSL_set_fd(ssl, fd);

	if(SSL_connect(ssl) < 0) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}

	strcpy(requestBuf, "Hello, I'm client\n");
	ret = SSL_write(ssl, requestBuf, strlen(requestBuf));
	if(ret <= 0) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}
	DEBUG(LEVEL_DEBUG, "SSL_write %d:%s\n", ret, requestBuf);

	ret = SSL_read(ssl, responseBuf, buflen);
	if(ret <= 0) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}
	DEBUG(LEVEL_DEBUG, "SSL_read %d:%s\n", ret, responseBuf);

	SSL_shutdown(ssl);
	close(fd);	
	SSL_free(ssl);
	SSL_CTX_free(ctx);
		
	return 0;
ERROR:
	if(fd > 0)
		close(fd);
	if(ctx)
		SSL_CTX_free(ctx);
	if(ssl)
		SSL_free(ssl);

	return -1;
}
