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

#include "socket_define.h"
#include "CSocket.h"
using namespace socket_pra;

#define IP_CHAR_LENGTH 40
struct client_struct
{
	int client_fd;
	char * ip;
	int port;
};

#endif /* SERVER_H_ */
