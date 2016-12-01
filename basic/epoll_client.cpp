#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/epoll.h> 
#include <errno.h> 
#include <string.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
#define BUFSIZE 512  
#define RET_ERR -1
#define RET_OK 0
#define Debug_UserLog printf
#define Debug_SysLog printf
 
void SetNonBlock(int fd) 
{ 
    int flag = fcntl ( fd, F_GETFL, 0 ); 
    fcntl ( fd, F_SETFL, flag | O_NONBLOCK ); 
} 
 
int main(int argc, char** argv) 
{ 
    int iRet = RET_OK; 
 
    if(4 != argc) 
    { 
        Debug_UserLog("Parameter: ServerIP Message ServerPort\n", RET_ERR); 
        return RET_ERR; 
    } 
 
    in_port_t i16_port = atoi(argv[3]); 
    if(0 >= i16_port) 
    { 
        Debug_UserLog("port number is wrong\n", RET_ERR); 
        return RET_ERR; 
    } 
 
    int sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    if(-1 == sk) 
    { 
        Debug_SysLog("open socket failed!\n"); 
        return RET_ERR; 
    } 
 
 
    struct sockaddr_in sa = {0}; 
    sa.sin_family = AF_INET; 
    sa.sin_port = htons(i16_port); 
 
    struct sockaddr_in *psa = &sa; 
 
    iRet = inet_pton(AF_INET, argv[1], &psa->sin_addr.s_addr); 
    if(0 == iRet) 
    { 
        Debug_UserLog("inet_pton failed, invalid address!\n", RET_ERR); 
        close(sk); 
        return RET_ERR; 
    } 
    else if(iRet < 0) 
    { 
        Debug_SysLog("inet_pton failed\n"); 
        close(sk); 
        return RET_ERR; 
    } 
 
    if(connect(sk, (struct sockaddr*)&sa, sizeof(sa)) < 0) 
    { 
        Debug_SysLog("connect failed!\n"); 
        close(sk); 
        return RET_ERR; 
    } 
 
    SetNonBlock(sk); 
 
    int efd;  
    efd = epoll_create(10);  
    if(efd == -1) 
    { 
        perror("epoll_create error!\n"); 
        exit(1); 
    } 
 
    struct epoll_event event; 
    struct epoll_event events[10]; 
 
    event.events = EPOLLOUT | EPOLLIN | EPOLLET; 
    event.data.fd = sk; 
 
    epoll_ctl(efd, EPOLL_CTL_ADD, sk, &event); 
 
 
    getchar(); 
    int loop = 0; 
    while(1) 
    { 
        ssize_t numBytesRcvd = 0; 
        char buffer[BUFSIZE] = {0}; 
        int n = 0; 
        int i = 0; 
 
        if(loop == 10) 
        { 
            break; 
        } 
  
        n = epoll_wait(efd, events, 10, -1); 
 
        printf("%d\n", n); 
 
        for(i = 0; i < n; i++) 
        { 
            if(events[i].events & EPOLLOUT) 
            { 
                printf("EPOLLOUT...............\n"); 
                snprintf(buffer, BUFSIZE, "i am process %d, just say: %s\n", getpid(), argv[2]); 
 
                int n = strlen(buffer); 
                int nsend = 0; 
 
                while(n > 0) 
                { 
                    //nsend = send(events[i].data.fd, buffer + nsend, n, 0); 
                    nsend = write(events[i].data.fd, buffer + nsend, n); 
                    if(nsend < 0 && errno != EAGAIN) 
                    { 
 
                        Debug_SysLog("send failed"); 
                        close(events[i].data.fd); 
                        return RET_ERR; 
                    } 
                    n -= nsend; 
                } 
            } 
 
            if(events[i].events & EPOLLIN) 
            { 
                printf("EPOLLIN...............\n"); 
                memset(buffer, 0, BUFSIZE); 
 
                int len = strlen(buffer); 
                int n = 0; 
                int nrecv = 0; 


                while(1){ 
                    nrecv = read(events[i].data.fd, buffer + n, BUFSIZE - 1) ; 
                    if(nrecv == -1 && errno != EAGAIN) 
                    { 
                        perror("read error!"); 
                    } 
                    if((nrecv == -1 && errno == EAGAIN) || nrecv == 0) 
                    { 
                        break; 
                    } 
                    n += nrecv; 
                } 
                loop = 1; 
                printf("%s\n", buffer); 
            } 
        } 
    } 
    close(sk); 
    close(efd); 
    return RET_OK; 
} 