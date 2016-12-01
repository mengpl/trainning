/*
 * server.cpp
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 *  add input param : port
 */

#include "server.h"

int main(int argc,char* argv[])
{
	if(argc < 2)
	{
		log_error(-1," usage : server port");
		return FAIL;
	}

	int myport;
	if (argv[1])
	        myport = atoi(argv[1]);

	// 1、define socket
	int sock_fd , client_fd;

	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		log_error(-1,"socket create fail ...");
		return FAIL;
	}

	struct sockaddr_in my_addr;
	my_addr.sin_family = PF_INET;
	my_addr.sin_port = htons(myport);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//2、bind socket
	if((bind(sock_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))) == -1)
	{
		log_error(-1,"bind server fail ...");
		return FAIL;
	}

	//3、listen
	if((listen(sock_fd,5)) == -1)
	{
		log_error(-1,"listen fail ...");
		return FAIL;
	}
	log_info("listenning on port " <<  myport <<  " ...");

	//4、wait connect
	struct sockaddr_in client_addr;
	int sin_size;
	char hello[] = "you are connected !";
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if((client_fd = accept(sock_fd,(sockaddr *)&client_addr,&sin_size)) == -1)
		{
			log_error(-1,"accept fail ...");
			return FAIL;
		}

		// change addr
		inet_ntoa(client_addr.sin_addr);
		log_info("one client connected client addr is " << inet_ntoa(client_addr.sin_addr) << " ...");

		if((write(client_fd,hello,strlen(hello))) == -1)
		{
			log_error(-1,"write fail ...");
			return FAIL;
		}

		int nBytes;
		char buffer[1024];
		while(1)
		{
			if((nBytes = read(client_fd,buffer,1024)) == 0)
			{
				log_info("one client closed addr is " << inet_ntoa(client_addr.sin_addr) << " ...");
				break;
			}

			log_info("recive from client :" << buffer);
			memset((void *)buffer,0,1024);
		}

		close(client_fd);
	}

	close(sock_fd);
	return OK;
}



