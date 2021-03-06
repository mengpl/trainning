#ifndef __LOG_DEFINE_H__
#define __LOG_DEFINE_H__
#include "log4z.h"


#define LOG_INIT zsummer::log4z::ILog4zManager::getInstance()->start()

#define log(fmt,...) log_info(fmt, ##__VA_ARGS__) 
#define log_trace(fmt,...) LOGFMTT(fmt, ##__VA_ARGS__)
#define log_debug(fmt,...) LOGFMTD(fmt, ##__VA_ARGS__)
#define log_info(fmt,...) LOGFMTI(fmt, ##__VA_ARGS__)
#define log_warn(fmt,...) LOGFMTW(fmt, ##__VA_ARGS__)
#define log_error(fmt,...) LOGFMTE(fmt, errno, ##__VA_ARGS__)
#define log_fatal(fmt,...) LOGFMTF(fmt, ##__VA_ARGS__)


// #include <stdio.h>
// #include <pthread.h>
// #include <time.h>

// #ifndef log_error
// #define log_error(errorCode,...)	do {          \
//     	struct tm now;                            \
//     	struct timespec pTimeSpec;                           \
//     	clock_gettime(CLOCK_REALTIME, &pTimeSpec);    \
// 		localtime_r(&pTimeSpec.tv_sec, &now);                        \
// 		fprintf(stdout,"%04d-%02d-%02d %02d:%02d:%02d:%06ld [%lld] %s %d log [error] ",  \
// 				now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, \
// 				now.tm_hour, now.tm_min, now.tm_sec, pTimeSpec.tv_nsec/1000,  \
// 				(long long)pthread_self(), __FILE__,__LINE__); \
// 		fprintf(stdout,"error code %d error msg :", errorCode); \
// 		fprintf(stdout, __VA_ARGS__); \
// 		fprintf(stdout, "\n");        \
// 		fflush(stdout);               \
// 	} while (0)
// #endif

// #ifndef log_info
// #define log_info(...)	do {          \
// 		struct tm  now;                            \
//     	struct timespec pTimeSpec;                           \
//     	clock_gettime(CLOCK_REALTIME, &pTimeSpec);    \
// 		localtime_r(&(pTimeSpec.tv_sec), &now);                        \
// 		fprintf(stdout,"%04d-%02d-%02d %02d:%02d:%02d:%06ld [%lld] %s %d log [info] ",  \
// 				now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, \
// 				now.tm_hour, now.tm_min, now.tm_sec, pTimeSpec.tv_nsec/1000,  \
// 				(long long)pthread_self(), __FILE__,__LINE__); \
// 		fprintf(stdout, __VA_ARGS__); \
// 		fprintf(stdout, "\n");        \
// 		fflush(stdout);               \
// 	} while (0)
// #endif

#endif // !__LOG_DEFINE_H__