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

	struct epoll_event ev,events[20];
	int epfd = epoll_create(OPEN_MAX);

	CSocket cSocket;
	char iplocal[IP_CHAR_LENGTH] = "127.0.0.1" ;

	listen_fd = cSocket.create_tcpServer(myport,iplocal,10);

	if(listen_fd == -1)
	{
		return FAIL;
	}

	cSocket.set_nonBlock(listen_fd);

	ev.data.fd = listen_fd;
	ev.events = EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,listen_fd,&ev);

	char buf[1024];
	int length ;

	int nReady ;
	int max_fd = 0;
	char ipChar[IP_CHAR_LENGTH];
	int clientPort;

	int i ;
	while(1)
	{
		nReady =  epoll_wait(epfd, events, 20, -1);
		if(nReady == FAIL)
		{
			log_error(-1," select fail ...");
			break;
		}

		for(int i = 0;i < nReady; i++)
		{
			if(events[i].data.fd==listen_fd)
			{
				client_fd = cSocket.tcp_accept(listen_fd,ipChar,IP_CHAR_LENGTH,&clientPort);
				
				cSocket.set_reuseAddr(client_fd);
				cSocket.set_nonBlock(client_fd);

				log_info(" a new client conncted ip %s, port %d",ipChar,clientPort);
				char hello[] = "you are connected !";
				CSocket cSocket;
				if((cSocket.write(client_fd,hello,strlen(hello))) == -1)
				{
					log_error(-1,"write fail ...");
					return FAIL;
				}

				ev.data.fd=client_fd;
				ev.events=EPOLLIN;
				epoll_ctl(epfd,EPOLL_CTL_ADD,client_fd,&ev);
				
			}
			else if(events[i].events&EPOLLIN)
			{
				if(events[i].data.fd < 0)
					continue;

				bzero(buf, 1024);
				/* recive from client */
				length = recv(events[i].data.fd, buf, 1024, 0);
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

						close(events[i].data.fd);
						events[i].data.fd = -1;
				}
			}
		}
	}

	close(listen_fd);
	return OK;
}



