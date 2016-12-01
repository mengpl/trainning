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
	client_struct client[FD_SETSIZE];

	for (int i = 0; i < FD_SETSIZE; i++)
	{
		client[i].client_fd= -1;
	}

	
	fd_set rfds,allfds;
	FD_ZERO(&allfds);
	struct timeval tv;

	tv.tv_sec = 5;
	tv.tv_usec = 0;

	char buf[1024];
	int length ;

	int nReady ;
	// 1 watch listen_fd
	FD_SET(listen_fd,&allfds);
	int max_fd = listen_fd;
	while(1)
	{
		rfds = allfds;
		nReady = select(max_fd+1,&rfds,NULL,NULL,&tv);
		if(nReady == FAIL)
		{
			log_error(-1," select fail ...");
			break;
		}

		if(FD_ISSET(listen_fd,&rfds))
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
			for(int i = 0; i< FD_SETSIZE;i++)
			{
				if(client[i].client_fd < 0)
				{
					client[i].client_fd = client_fd;
					client[i].ip = ipChar;
					client[i].port = clientPort;
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

			FD_SET(client_fd,&allfds);

			if(client_fd > max_fd)
				max_fd = client_fd;

			if(--nReady < 0)
				continue;
		}

		for(int i = 0; i < FD_SETSIZE; i++)
		{
			if(client[i].client_fd < 0)
				continue;

			if(FD_ISSET(client[i].client_fd,&rfds))
			{
				bzero(buf, 1024);
				/* recive from client */
				length = recv(client[i].client_fd, buf, 1024, 0);
				if (length > 0)
					log_info("recv message success %s", buf);
				else
				{
					if(length < 0)
						log_info("recv message failed! error code is %d,error message is '%s'\n",
							 errno, strerror(errno));
					else
						log_info("one client closed addr is %s, port %d...",client[i].ip,client[i].port);
					close(client[i].client_fd);
					FD_CLR(client[i].client_fd,&allfds);
				}
			}
		}
	}

	close(listen_fd);
	return OK;
}



