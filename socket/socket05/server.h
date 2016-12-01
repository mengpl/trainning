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
#include <syslog.h>
#include "socket_define.h"
#include "CThreadPool.h"
#include "CSocket.h"

using namespace socket_pra;

#define IP_CHAR_LENGTH 100

struct client_struct
{
	int client_fd;
	char * ip;
	int port;
};

class CSocketTask : public CTask
{
public:
	CSocketTask() : CTask(0),m_ifd(-1){};
	~CSocketTask(){};

	void run();
	void timeout();

	void set_fd(int fd){m_ifd = fd;};
private:
	int m_ifd ;
};

#endif /* SERVER_H_ */
