/*
 * pthread.h
 *
 *  Created on: 2014Äê10ÔÂ27ÈÕ
 *      Author: mengpl
 */

#ifndef PTHREAD_H_
#define PTHREAD_H_


#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef OK
#define OK 0;
#endif

#ifndef FAIL
#define FAIL -1;
#endif

#ifndef LOG_ERROR
#define log_error(errorCode,...)	do {          \
    	struct tm now;                            \
    	struct timespec pTimeSpec;                           \
    	clock_gettime(CLOCK_REALTIME, &pTimeSpec);    \
		localtime_r(&pTimeSpec.tv_sec, &now);                        \
		fprintf(stdout,"%04d-%02d-%02d %02d:%02d:%02d:%06ld [%lld] %s %d log [info] ",  \
				now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, \
				now.tm_hour, now.tm_min, now.tm_sec, pTimeSpec.tv_nsec/1000,  \
				(long long)pthread_self(), __FILE__,__LINE__); \
		fprintf(stdout,"error code %d error msg :", errorCode); \
		fprintf(stdout, __VA_ARGS__); \
		fprintf(stdout, "\n");        \
		fflush(stdout);               \
	} while (0)
#endif

#ifndef LOG_INFO
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


#endif /* PTHREAD_H_ */
