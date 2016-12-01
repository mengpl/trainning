#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define SERVPORT 6000    /*服务器监听端口号 */
#define BACKLOG 10    /* 最大同时连接请求数 */

using namespace std;

int main(int argc,char * argv[])
{
    cout << "this is for tcl client test " << endl;

    if(argc < 3)
    {
        cout << "please input hostname and port: " <<endl;
        return -1;
    }

    char * hostname = argv[1];
    char * port     = argv[2];

    int iPort = atoi(port);

    struct hostent *host;
    host = gethostbyname(hostname);

    if(host == NULL)
    {
        cout << "gethostbyname fail! hostname = " << hostname << endl;
        return -1; 
    }

    int sock_fd; 

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr; // 定义socket

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(iPort);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    memset(serv_addr.sin_zero,0x00,sizeof(serv_addr.sin_zero));

    int iRet = connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));

    if(iRet == -1)
    {
        cout << "connect fail!" << endl;
        return -1;
    }

    char buf[256];

    int recvbytes = recv(sock_fd,buf,256,0);

    if(recvbytes == -1)
    {
        cout << "recv fail!" << endl;
        return -1;
    }

    buf[recvbytes] = '\0';

    cout << buf << endl;
    close(sock_fd);
}