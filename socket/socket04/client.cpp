/*
 * client.cpp
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 *  V01 增加处理命令参数的逻辑
 *  V02 增加支持多参数命令行支持
 */

#include "client.h"

int main(int argc,char * argv[])
{
	if(argc < 3)
	{
		log_error(-1," usage : client ip/hostname port");
		return FAIL;
	}

	char * ip = argv[1];
	int port = atoi(argv[2]);

	int sock_fd;
	CSocket cSocket;
	sock_fd = cSocket.tcp_connect(ip,port);

	cSocket.set_keepAlive(sock_fd);
	int nBytes;
	char buffer[1024];
	if((nBytes = cSocket.read(sock_fd,buffer,1024)) == -1)
	{
		log_error(-1,"read fail ...");
		return FAIL;
	}
	//	buffer[nBytes]='/0';
	log_info("%s",buffer);

	log_info("please input:");
	char input[1024];
	while(fgets(input, 1024, stdin))
	{
		if("exit\n" == std::string(input))
		{
			break;
		}

		log_info("send to server: %s" , input);
		if((cSocket.write(sock_fd,input,strlen(input))) == -1)
		{
			log_error(-1,"write fail ...");
			return FAIL;
		}
		log_info("please input:");
		memset((void *)buffer,0,1024);
	}

	close(sock_fd);

	return OK;
}


