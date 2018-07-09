#ifndef _GENERAL_API_H_
#define _GENERAL_API_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <netdb.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/prctl.h>

#define thread_func void * (*)(void *)

typedef int BOOL;

enum DEBUG_LEVEL_E {
	LEVEL_NONE,
	LEVEL_EMERG,
	LEVEL_ALERT,
	LEVEL_CRIT,
	LEVEL_ERROR,
	LEVEL_WARNING,
	LEVEL_NOTICE,
	LEVEL_INFO,
	LEVEL_DEBUG
};

#define DEBUG_LEVEL LEVEL_DEBUG

#define DEBUG(pos,fmt,args...)\
	do{\
		if (pos <= DEBUG_LEVEL)\
		{\
			printf("%s:%d ", __FUNCTION__, __LINE__);\
			printf(fmt, ##args); \
		}\
	}while(0)

int tcp_listen(const char *hostip, int servport);

int tcp_connect(const char *servIp,int servport);

void sleep_rand_ms(int min, int max);

#endif
