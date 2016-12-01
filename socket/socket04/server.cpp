/*
 * server.cpp
 *
 *  Created on: 2014/10/30
 *      Author: Mengpl
 *  add input param : port
 */

#include "server.h"

extern "C" void * deal_client(void* args)
{
	client_struct * cs = (client_struct *)args;
	client_struct csv = (*cs);
	char hello[] = "you are connected !";
	CSocket cSocket;
	if((cSocket.write(csv.client_fd,hello,strlen(hello))) == -1)
	{
		log_error(-1,"write fail ...");
		return NULL;
	}

	int nBytes;
	char buffer[1024];
	while(1)
	{
		if((nBytes = cSocket.read(csv.client_fd,buffer,1024)) == 0)
		{
			log_info("one client closed addr is %s, port %d...",csv.ip,csv.port);
			break;
//			pthread_join(pthread_self(),NULL);
		}
		if(nBytes == -1)
		{
			break;
		}
		log_info("recive from client : %s",buffer);
		memset((void *)buffer,0,1024);
	}

	close(csv.client_fd);
	pthread_exit(NULL);
	return NULL;
}

void start_thread(client_struct client)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t llThreadId;
	pthread_create(&llThreadId,&attr,deal_client,&client);
}

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

	// 1��define socket
	int sock_fd , client_fd;

	CSocket cSocket;
	char iplocal[IP_CHAR_LENGTH] = "127.0.0.1" ;

	sock_fd = cSocket.create_tcpServer(myport,iplocal,10);

	if(sock_fd == -1)
	{
		return FAIL;
	}
	char ipChar[IP_CHAR_LENGTH];
	int clientPort;
	while(1)
	{
		client_fd = cSocket.tcp_accept(sock_fd,ipChar,IP_CHAR_LENGTH,&clientPort);
		cSocket.set_reuseAddr(client_fd);

		client_struct cs;
		cs.client_fd = client_fd;
		cs.ip = ipChar;
		cs.port = clientPort;

		log_info(" a new client conncted ip %s, port %d",ipChar,clientPort);
		start_thread(cs);
	}

	close(sock_fd);
	return OK;
}



