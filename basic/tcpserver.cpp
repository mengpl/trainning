#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERVPORT 6000    /*服务器监听端口号 */
#define BACKLOG 10    /* 最大同时连接请求数 */

using namespace std;

/**
 * http://www.linuxidc.com/Linux/2011-06/37951.htm
 */
int main(int argc,char * argv[])
{
	cout << "this is for tcp server test " << endl;
		
	// 函数原型 
	// int socket(int domain, int type, int protocol);
	// domain指明所使用的协议族，通常为PF_INET，表示互联网协议族（TCP/IP协议族）；
	// type参数指定socket的类型：SOCK_STREAM 或SOCK_DGRAM，Socket接口还定义了原始Socket（SOCK_RAW），允许程序使用低层协议；
	// protocol通常赋值"0"。
	int sock_fd = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in my_addr;    /* 本机地址信息 */

	my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(SERVPORT);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* 填入本机IP地址 */
    // bzero(&(my_addr.sin_zero),8);
    memset(my_addr.sin_zero,0x00,sizeof(my_addr.sin_zero));

    /*
    	htonl()：把32位值从主机字节序转换成网络字节序
　　　　htons()：把16位值从主机字节序转换成网络字节序
　　　　ntohl()：把32位值从网络字节序转换成主机字节序
　　　　ntohs()：把16位值从网络字节序转换成主机字节序
    */

    // 绑定端口
    int iRet = bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

    if(iRet == -1)
    {
        std::cout << "bind fail！" << std::endl;
        return -1;
    }
    
    iRet = listen(sock_fd, BACKLOG);

    if(iRet == -1)
    {
        std::cout << "listen fail！" << std::endl;
        return -1;
    }    
    std::cout << "=====begin to listen on port... ..." << my_addr.sin_port << std::endl;

    int client_fd;
    struct sockaddr_in remote_addr;    /* 客户端地址信息 */
    int size_sock = sizeof(sockaddr_in);

    while(true)
    {
        client_fd = accept(sock_fd,(struct sockaddr *)&remote_addr,(socklen_t*)&size_sock);
        
        if(client_fd == -1)
        {
            std::cout << "=====accept fail ======" << std::endl;
            continue;
        }

        char *str = inet_ntoa(remote_addr.sin_addr);
        std::cout<<"connect from "<<str<<std::endl;  
        
        if(!fork())
        {
            iRet = send(client_fd, "Hello, you are connected!\n", 26, 0);
            cout << "send message to remote_addr " << endl;
            if(iRet == -1)
            {
                std::cout << "send fail！" << std::endl;
                close(client_fd);
            }
        }
        close(client_fd);
    }
}