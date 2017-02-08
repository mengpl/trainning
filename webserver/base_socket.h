#ifndef __BASE_SOCKET_H__
#define __BASE_SOCKET_H__
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "log_define.h"

namespace webserver
{
    #define OK 0
    #define FAIL -1

    class CBaseSocket
    {
    public:
        CBaseSocket(){};
        ~CBaseSocket(){};
    public:
        int create_server(int port, char *bindaddr, int backlog);
        int connect(char *addr, int port);
        int accept(int serversock, char *ip, size_t ip_len, int *port);
        int write(int fd, char *buf, int count);
        int read(int fd, char *buf, int count);

        int set_reuseAddr(int fd);
    };

}

#endif // !__BASE_SOCKET_H__