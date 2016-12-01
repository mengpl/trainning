/*
 * server.cpp
 *
 *  Created on: 2014/10/30
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

	// define socket
	int listen_fd , client_fd;

	CSocket cSocket;
	char iplocal[IP_CHAR_LENGTH] = "127.0.0.1" ;

	listen_fd = cSocket.create_tcpServer(myport,iplocal,10);

	if(listen_fd == -1)
	{
		return FAIL;
	}
	char ipChar[IP_CHAR_LENGTH];
	int clientPort;
	struct pollfd clientfds[OPEN_MAX];
	clientfds[0].fd = listen_fd;
	clientfds[0].events = POLLIN;

	for (int i = 1; i < OPEN_MAX; i++)
	{
		clientfds[i].fd= -1;
	}

	char buf[1024];
	int length ;

	int nReady ;
	int max_fd = 0;

	int i ;
	while(1)
	{
		nReady =  poll(clientfds,max_fd+1,-1);
		if(nReady == FAIL)
		{
			log_error(-1," select fail ...");
			break;
		}

		if(clientfds[0].revents & POLLIN)
		{
			client_fd = cSocket.tcp_accept(listen_fd,ipChar,IP_CHAR_LENGTH,&clientPort);
			cSocket.set_reuseAddr(client_fd);

			log_info(" a new client conncted ip %s, port %d",ipChar,clientPort);
			char hello[] = "you are connected !";
			CSocket cSocket;
			if((cSocket.write(client_fd,hello,strlen(hello))) == -1)
			{
				log_error(-1,"write fail ...");
				return FAIL;
			}
			bool bFull = true;
			for(i = 1; i< OPEN_MAX;i++)
			{
				if(clientfds[i].fd < 0)
				{
					clientfds[i].fd = client_fd;
					clientfds[i].events = POLLIN;
					bFull = false;
					break;
				}
			}

			if(bFull)
			{
				log_info(" too many clients ...");
				close(client_fd);
				continue;
			}
			max_fd = i > max_fd ? i : max_fd;

			if(--nReady < 0)
				continue;
		}

		for(i = 1; i <= max_fd; i++)
		{
			if(clientfds[i].fd < 0)
				continue;

			if(clientfds[i].revents & POLLIN)
			{
				bzero(buf, 1024);
				/* recive from client */
				length = recv(clientfds[i].fd, buf, 1024, 0);
				if (length > 0)
					log_info("recv message success %s", buf);
				else
				{
					if(length < 0)
						log_info("recv message failed! error code is %d,error message is '%s'\n",
							 errno, strerror(errno));
					else
						//log_info("one client closed addr is %s, port %d...",client[i].ip,client[i].port);
						log_info("one client closed addr quit...");

						close(clientfds[i].fd);
						clientfds[i].fd = -1;
				}
			}
		}
	}

	close(listen_fd);
	return OK;
}



