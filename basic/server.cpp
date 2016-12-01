#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#define SERVPORT 6000    /*服务器监听端口号 */
#define BACKLOG 10    /* 最大同时连接请求数 */

main()
{
	std::cout << "======begin ... " << std::endl;
    int sock_fd,client_fd;    /*sock_fd：监听socket；client_fd：数据传输socket */
    int sin_size;
    struct sockaddr_in my_addr;    /* 本机地址信息 */
    struct sockaddr_in remote_addr;    /* 客户端地址信息 */
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    	  std::cout << "socket create fail ！" << std::endl;
        perror("socket create fail！");
        exit(1);
    }
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(SERVPORT);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(my_addr.sin_zero),8);
    
    std::cout << "AF :" << my_addr.sin_family << std::endl;
    std::cout << "address :" << my_addr.sin_addr.s_addr << std::endl;
    
    std::cout << "======bind ..." << std::endl;
    if(bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind fail！");
        std::cout << "bind fail " << std::endl;
        exit(1);
    }
    
    std::cout << "======listen ..." << std::endl;
    if(listen(sock_fd, BACKLOG) == -1) {
    	  std::cout << "listen fail！" << std::endl;
        perror("listen fail！");
        exit(1);
    }
    while(1)
    {
    	std::cout << "=====begin to listen on port... ..." << my_addr.sin_port << std::endl;

        sin_size = sizeof(struct sockaddr_in);
        std::cout << "sin_size " << sin_size << std::endl;
        if((client_fd = accept(sock_fd, (struct sockaddr *)&remote_addr, (socklen_t*)&sin_size)) == -1) {
        	  std::cout << "accept fail" << std::endl;
            perror("accept fail");
            continue;
        }
        
        std::cout << "received a connection from " << inet_ntoa(remote_addr.sin_addr) << std::endl;
        // printf("received a connection from %s\n", inet_ntoa(remote_addr.sin_addr));
        
        if(!fork()) {    /* 子进程代码段 */
            if(send(client_fd, "Hello, you are connected!\n", 26, 0) == -1) {
                std::cout << "send fail！" << std::endl;
                perror("send fail！");
            }
            close(client_fd);
            exit(0);
        }
        close(client_fd);
    }
 }