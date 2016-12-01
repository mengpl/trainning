/*
 * client.h
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SERVPORT 6000

#ifndef OK
#define OK 0;
#endif

#ifndef FAIL
#define FAIL -1;
#endif

#ifndef LOG_ERROR
#define log_error(errorCode,...)	do {          \
		fprintf(stdout,"%s %s [%lld] %s %d log [info] ",  \
			__DATE__,__TIME__, pthread_self(), __FILE__,__LINE__); \
		fprintf(stdout,"error code %d error msg :", errorCode); \
		fprintf(stdout, __VA_ARGS__); \
		fprintf(stdout, "\n");        \
		fflush(stdout);               \
	} while (0)
#endif

#ifndef LOG_INFO
#define log_info(...)	do {          \
		fprintf(stdout,"%s %s [%d] %s %d log [info] ",  \
			__DATE__,__TIME__, pthread_self(), __FILE__,__LINE__); \
		fprintf(stdout, __VA_ARGS__); \
		fprintf(stdout, "\n");        \
		fflush(stdout);               \
	} while (0)
#endif

#endif /* CLIENT_H_ */
