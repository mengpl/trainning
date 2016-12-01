/*
 * client.cpp
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 *  增加处理命令参数的逻辑
 */

#include "client.h"

int main(int argc,char * argv[])
{
	if(argc < 3)
	{
		log_error(-1," usage : client ip/hostname port");
		return FAIL;
	}

	struct hostent *host;
	host=gethostbyname(argv[1]);
	if(host == NULL)
	{
		log_info(" get host by name fail ,try to get host by addr ");
		char * paddr = argv[1];
		struct in_addr *hipaddr;
		if(!inet_aton(paddr,hipaddr))
		{
			log_error(-1,"inet_aton fail ...");
			return FAIL;
		}
		host = gethostbyaddr((char*)hipaddr,4,AF_INET);
		if(host == NULL)
		{
			log_error(-1,"get host fail ...");
			return FAIL;
		}
	}

	// 1、define socket
	int client_fd;
	if((client_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		log_error(-1,"socket create fail ...");
		return FAIL;
	}

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr = *((struct in_addr *)host->h_addr);
	serveraddr.sin_port = htons(atoi(argv[2]));

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

	std::string strInput;
	while(1)
	{
		std::cout << "please input :" << std::endl;
		std::cin >> strInput;

		if("exit" == strInput)
		{
			break;
		}

		log_info("send to server: " << strInput);
		if((write(client_fd,strInput.c_str(),strlen(strInput.c_str()))) == -1)
		{
			log_error(-1,"write fail ...");
			return FAIL;
		}
		strInput.clear();
	}



	close(client_fd);

	return OK;
}


