/*
 * server.h
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define SERVPORT 6000    /*服务器监听端口号 */

#ifndef OK
#define OK 0;
#endif

#ifndef FAIL
#define FAIL -1;
#endif

#ifndef LOG_ERROR
#define log_error(errorCode,...)	do {          \
		fprintf(stdout,"%s %s [%d] %s %d log [info] ",  \
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

struct client_struct
{
	int client_fd;
	struct sockaddr_in client_addr;
};

#endif /* SERVER_H_ */
