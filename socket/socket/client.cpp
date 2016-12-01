/*
 * client.cpp
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 */

#include "client.h"

int main(int argc,char * argv[])
{
	// 1、define socket
	int client_fd;
	if((client_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		log_error(-1,"socket create fail ...");
		return FAIL;
	}

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(SERVPORT);

	if((connect(client_fd,(sockaddr *)&serveraddr,sizeof(struct sockaddr))) == -1)
	{
		log_error(-1,"connect fail ...");
		return FAIL;
	}

	int nBytes;
	char buffer[1024];
	if((nBytes = read(client_fd,buffer,1024)) == -1)
	{
		log_error(-1,"read fail ...");
		return FAIL;
	}

//	buffer[nBytes]='/0';

	log_info(buffer);

	close(client_fd);

	return OK;
}


