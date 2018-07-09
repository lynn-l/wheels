/*general_api.h*/
/*
 *This file implement the most frequently used APIs. Continuously updating.
 */

#include "general_api.h"

int tcp_listen(const char *hostip, int servport)
{
	int sockfd = -1;
	struct sockaddr_in addr;
	
	sockfd = socket(AF_INET, (int)SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("socket:");
		return -1;
	}
	
	int set = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&set, sizeof(int))) {
		perror("setsockopt(SO_REUSEADDR):");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	
	if(NULL != hostip)
		inet_aton(hostip, &addr.sin_addr);
	else
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	addr.sin_port = htons(servport);
	if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind:");
		close(sockfd);
		return -1;
	}

	if(listen(sockfd, 10) < 0) {
		perror("listen:");
		close(sockfd);
		return -1;
	}
	
	return sockfd;
}

int tcp_connect(const char *servIp,int servport)
{
	if(NULL == servIp)
		return -1;

	int fd = socket (AF_INET, (int)SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket:");
		return -1;
	}
	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	inet_aton(servIp, &serv_addr.sin_addr);
	serv_addr.sin_port = htons(5443);
	
	if(connect(fd,	(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect:");
		close(fd);
		return -1;
	}

	return fd;
}

void sleep_rand_ms(int min, int max)
{
	if(min > max)
		usleep((min + max) / 2 * 1000);
	else if(min == max)
		usleep(min * 1000);
	else
		usleep((min + (rand()%(max - min))) * 1000);
}

