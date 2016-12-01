/*
 * socket_define.h
 *
 *  Created on: 2014��10��30��
 *      Author: mengpl
 */

#ifndef SOCKET_DEFINE_H_
#define SOCKET_DEFINE_H_

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#ifndef OK
#define OK 0
#endif

#ifndef FAIL
#define FAIL -1
#endif

#ifndef CONNECT_NONE
#define CONNECT_NONE 0
#endif

#ifndef CONNECT_NONBLOCK
#define CONNECT_NONBLOCK 1
#endif

#ifndef log_error
#define log_error(errorCode,...)	do {          \
    	struct tm now;                            \
    	struct timespec pTimeSpec;                           \
    	clock_gettime(CLOCK_REALTIME, &pTimeSpec);    \
		localtime_r(&pTimeSpec.tv_sec, &now);                        \
		fprintf(stdout,"%04d-%02d-%02d %02d:%02d:%02d:%06ld [%lld] %s %d log [error] ",  \
				now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, \
				now.tm_hour, now.tm_min, now.tm_sec, pTimeSpec.tv_nsec/1000,  \
				(long long)pthread_self(), __FILE__,__LINE__); \
		fprintf(stdout,"error code %d error msg :", errorCode); \
		fprintf(stdout, __VA_ARGS__); \
		fprintf(stdout, "\n");        \
		fflush(stdout);               \
	} while (0)
#endif

#ifndef log_info
#define log_info(...)	do {          \
		struct tm  now;                            \
    	struct timespec pTimeSpec;                           \
    	clock_gettime(CLOCK_REALTIME, &pTimeSpec);    \
		localtime_r(&(pTimeSpec.tv_sec), &now);                        \
		fprintf(stdout,"%04d-%02d-%02d %02d:%02d:%02d:%06ld [%lld] %s %d log [info] ",  \
				now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, \
				now.tm_hour, now.tm_min, now.tm_sec, pTimeSpec.tv_nsec/1000,  \
				(long long)pthread_self(), __FILE__,__LINE__); \
		fprintf(stdout, __VA_ARGS__); \
		fprintf(stdout, "\n");        \
		fflush(stdout);               \
	} while (0)
#endif



#endif /* SOCKET_DEFINE_H_ */
