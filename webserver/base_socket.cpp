#include "base_socket.h"

namespace webserver
{
    int CBaseSocket::create_server(int port, char *bindaddr, int backlog)
    {
        int sock_fd = -1;
        if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
        {
            log_error(errno,"socket create fail ...");
            return FAIL;
        }

        struct addrinfo hints, *servinfo, *p;
        memset(&hints,0,sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_flags = AI_PASSIVE;     //	Intend socket address for bind.
        hints.ai_socktype = SOCK_STREAM; // TCP

        char cport[6];;
        snprintf(cport, 6,"%d",port);

        int rv = getaddrinfo(bindaddr,cport,&hints, &servinfo);

        if(rv != 0)
        {
            log_error(rv,"%s",gai_strerror(rv));
            return FAIL;
        }

        for(p = servinfo; p != NULL; p = p->ai_next)
        {
            sock_fd = ::socket(p->ai_family,p->ai_socktype,p->ai_protocol);
            if(sock_fd == -1)
                continue;
            int iRet = set_reuseAddr(sock_fd);
            if(iRet != OK)
            {
                sock_fd = -1;
                return FAIL;
            }

            if(::bind(sock_fd,p->ai_addr,p->ai_addrlen) == -1)
            {
                log_error(-1," bind error %s ",strerror(errno));
                close(sock_fd);
                return FAIL;
            }

            if(::listen(sock_fd,backlog) == -1)
            {
                log_error(-1," listen error %s ",strerror(errno));
                close(sock_fd);
                return FAIL;
            }

            log_info(" listenning on port %d ...",port);
        }

        freeaddrinfo(servinfo);
        return sock_fd;
    }

    int CBaseSocket::connect(char *addr, int port)
    {
        int sock_fd = -1;

        struct addrinfo hints, *servinfo,*bservinfo, *p,*b;
        memset(&hints,0,sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_flags = AI_PASSIVE;     //	Intend socket address for bind.
        hints.ai_socktype = SOCK_STREAM; // TCP

        char cport[6];;
        snprintf(cport, 6,"%d",port);

        int rv = getaddrinfo(addr,cport,&hints, &servinfo);

        if(rv != 0)
        {
            log_error(rv,"%s",gai_strerror(rv));
            return FAIL;
        }

        for(p = servinfo; p != NULL; p = p->ai_next)
        {
            sock_fd = ::socket(p->ai_family,p->ai_socktype,0);
            if(sock_fd == -1)
                continue;
            int iRet = set_reuseAddr(sock_fd);
            if(iRet != OK)
                return FAIL;

            iRet = ::connect(sock_fd,p->ai_addr,p->ai_addrlen);
            if( iRet == -1)
            {
                /*Connection already in progress*/
                if(errno == EINPROGRESS)
                {
                    freeaddrinfo(servinfo);
                    return FAIL;
                }
                close(sock_fd);
                sock_fd = -1;
                continue;
            }

            freeaddrinfo(servinfo);
            return sock_fd;
        }

        if (p == NULL)
            log_error(-1,"creating socket: %s", strerror(errno));

        return sock_fd;
    }

    int CBaseSocket::set_reuseAddr(int fd)
    {
        int yes = 1;
        int iRet = setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
        if(iRet != OK)
        {
            log_error(errno,"setsockopt : %s SO_REUSEADDR",strerror(errno));
            return FAIL;
        }

        return OK;
    }

    int CBaseSocket::accept(int sock_fd,char* ip,size_t ip_len,int * port)
    {
        int fd;
        struct sockaddr_storage sa;
        socklen_t salen = sizeof(sa);

        while(1)
        {
            fd = ::accept(sock_fd,(struct sockaddr*)&sa,&salen);
            if (fd == -1)
            {
                if (errno == EINTR)
                    continue;
                else
                {
                    log_error(-1, "accept: %s", strerror(errno));
                    return FAIL;
                }
            }
            break;
        }

        // get ip and port
        if (sa.ss_family == AF_INET)
        {
            struct sockaddr_in *s = (struct sockaddr_in *)&sa;
            if(ip) inet_ntop(AF_INET,(void *)&(s->sin_addr),ip,ip_len);
            if(port) *port = ntohs(s->sin_port);
        }

        return fd;
    }

    int CBaseSocket::write(int fd,char* buf,int count)
    {
        int nwritten, totlen = 0;
        while(totlen != count)
        {
            nwritten = ::write(fd,buf,count-totlen);
            if (nwritten == 0) return totlen;
            if (nwritten == -1) return -1;
            totlen += nwritten;
            buf += nwritten;
        }
        return totlen;
    }

    /* Like read(2) but make sure 'count' is read before to return
    * (unless error or EOF condition is encountered) */
    int CBaseSocket::read(int fd, char *buf, int count)
    {
        int nread, totlen = 0;
        while(totlen != count)
        {
            nread = ::read(fd,buf,count-totlen);
            if (nread == 0) return totlen;
            if (nread == -1) return -1;
            totlen += nread;
            buf += nread;
            break;
        }
        return totlen;
    }
};