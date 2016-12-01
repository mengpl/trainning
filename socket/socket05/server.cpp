/*
 * server.cpp
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 *  add input param : port
 */

#include "server.h"

void CSocketTask::run()
{

	log_info("begin to deal task ");
	char hello[] = "you are connected!";
	CSocket cSocket;
	if((cSocket.write(m_ifd,hello,strlen(hello))) == -1)
	{
		log_error(-1,"write fail ...");
		return;
	}

	int nBytes;
	char buffer[1024];
	while(1)
	{
		if((nBytes = cSocket.read(m_ifd,buffer,1024)) == 0)
		{
//			log_info("one client closed addr is %s, port %d...",m_cClientStruct.ip,m_cClientStruct.port);
			break;
		}
		if(nBytes == -1)
		{
			break;
		}
		log_info("recive from client : %s",buffer);
		memset((void *)buffer,0,1024);
	}

	close(m_ifd);
}

void CSocketTask::timeout()
{
	log_error(-1," task time out ...");
}

void start_thread(
		CThreadPool * pThreadPool,
		client_struct client)
{
	CSocketTask * pSockTask = new CSocketTask();
	pSockTask->set_fd(client.client_fd);

	pThreadPool->push_task(pSockTask);

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

	// 1、define socket
	int sock_fd , client_fd;

	CSocket cSocket;
	char iplocal[IP_CHAR_LENGTH] = "127.0.0.1" ;

	sock_fd = cSocket.create_tcpServer(myport,iplocal,10);

	if(sock_fd == -1)
	{
		return FAIL;
	}

	CThreadPool cThreadPool(3, //最大线程
	            1, //最小空闲线程
	            1, //最大空闲线程
	            10, //队列任务超时时间（秒）
	            1, //队列最大size
	            10); // 空闲线程回收时间

	cThreadPool.start();

	char ipChar[IP_CHAR_LENGTH];
	int clientPort;
	while(1)
	{
		client_fd = cSocket.tcp_accept(sock_fd,ipChar,IP_CHAR_LENGTH,&clientPort);

		if(client_fd > 0)
		{
			client_struct cs;
			cs.client_fd = client_fd;
			cs.ip = ipChar;
			cs.port = clientPort;

			log_info(" a new client conncted ip %s, port %d",ipChar,clientPort);
			start_thread(&cThreadPool, cs);
		}
		else
		{
			log_info("tcp_accept fail");
			return FAIL;
		}

	}

	close(sock_fd);
	cThreadPool.stop();
	return OK;
}



