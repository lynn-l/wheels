/*serv.c*/
/*
 *This file implement some modules that the TLS server need sometimes.
 */
#include "general_api.h"
#include "ssl_api.h"

#define buflen 1024 * 100

char *CERT_DIR = "../certs_data/Cert0.pem";
char *KEY_DIR = "../certs_data/PriKey0.pem";
char *PKCS8_DIR = "../certs_data/PKCS8";

int PKCS8_test(char *file)
{
	FILE *fp = fopen(KEY_DIR, "r");
	if(NULL == fp) {
		DEBUG(LEVEL_ERROR, "fopen %s failed\n", KEY_DIR);
		return -1;		
	}

	EVP_PKEY *pkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
	if(NULL == pkey) {
		DEBUG(LEVEL_ERROR, "PEM_read_PrivateKey failed\n");
		return -1;		
	}
	fclose(fp);

	int ret = saveKeyPKCS8(pkey, NULL, file);
	EVP_PKEY_free(pkey);
	if(ret < 0) {
		DEBUG(LEVEL_ERROR, "saveKeyPKCS8 failed\n");
		return -1;		
	}
	
	fp = fopen(file, "r");
	if(NULL == fp) {
		DEBUG(LEVEL_ERROR, "fopen %s failed\n", file);
		perror("fopen:");
		return -1;
	}

	char buf[4096] = {0};
	int len = fread(buf, 1, 4096, fp);
	fclose(fp);
	if(len <= 0) {
		DEBUG(LEVEL_ERROR, "fread error, len = %d\n", len);
		perror("fread:");
		return -1;
	}

	EVP_PKEY *priKey = NULL;
	EVP_PKEY *pubKey = NULL;
	ret = parsePKCS8FromBuf(buf, len, NULL, 0, &priKey, &pubKey);
	if(ret < 0) {
		DEBUG(LEVEL_ERROR, "parsePKCS8FromBuf failed, ret = %d\n", ret);
		return -1;
	}	
	DEBUG(LEVEL_DEBUG, "parsePKCS8FromBuf success\n");
/*
	BIO *out = BIO_new(BIO_s_file());
	BIO_set_fp(out, stdout, BIO_NOCLOSE);
	EVP_PKEY_print_private(out, priKey, 0, NULL);
	EVP_PKEY_print_public(out, pkey, 0, NULL);
	EVP_PKEY_print_params(out, pkey, 0, NULL);
	BIO_free(out);
*/	
	if(priKey)
		EVP_PKEY_free(priKey);
	if(pubKey)
		EVP_PKEY_free(priKey);
	
	return 0;
}

int main()
{
	int listenfd = -1;
	int connectfd = -1;
	struct sockaddr_in cliaddr;
	int cliaddrlen = sizeof(cliaddr);
	SSL_CTX *ctx = NULL;
	SSL *ssl = NULL;
	char requestBuf[buflen] = {0};
	char responseBuf[buflen] = {0};
	int ret = 0;
	
	INIT_SSL();

	PKCS8_test(PKCS8_DIR);
	return 0;

	listenfd = tcp_listen("127.0.0.1", 5443);
	if(listenfd < 0) {
		DEBUG(LEVEL_ERROR, "tcp_listen failed\n");
		goto ERROR;
	}
	else
		DEBUG(LEVEL_INFO, "listen ok, fd = %d\n", listenfd);

	memset(&cliaddr, 0, sizeof(cliaddr));
	connectfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
	if(connectfd < 0) {
		perror("accept:");
		goto ERROR;
	}
	
	ctx = my_ctx_new(CERT_DIR, KEY_DIR);
	if(NULL == ctx) {
		DEBUG(LEVEL_ERROR, "my_ctx_new failed\n");
		goto ERROR;
	}	

	ssl = SSL_new(ctx);
	if(ssl == NULL) {
		DEBUG(LEVEL_ERROR, "SSL_new failed\n");
		goto ERROR;
	}
	
	SSL_set_fd(ssl, connectfd);
	
	if(SSL_accept(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}
	ret = SSL_read(ssl, requestBuf, buflen);
	if(ret <= 0) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}
	DEBUG(LEVEL_DEBUG, "SSL_read %d: %s\n", ret, requestBuf);

	snprintf(responseBuf, buflen, "I received you msg. %d:%s\n", ret, requestBuf);
	ret = SSL_write(ssl, responseBuf, strlen(responseBuf));
	if(ret <= 0) {
		ERR_print_errors_fp(stderr);
		goto ERROR;
	}
	DEBUG(LEVEL_DEBUG, "SSL_write %d: %s\n", ret, responseBuf);

	SSL_shutdown(ssl);
	
	close(listenfd);
	close(connectfd);
	SSL_CTX_free(ctx);
	SSL_free(ssl);
	
	return 0;
	
ERROR:
	if(listenfd > 0)
		close(listenfd);
	if(connectfd > 0)
		close(connectfd);
	if(ctx)
		SSL_CTX_free(ctx);
	if(ssl)
		SSL_free(ssl);

	return -1;
}
