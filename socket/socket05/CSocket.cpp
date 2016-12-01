/*
 * CSocket.cpp
 *
 *  Created on: 2014��10��30��
 *      Author: mengpl
 */

#include "CSocket.h"

namespace socket_pra {

int CSocket::listen(int sock_fd,sockaddr* sa,socklen_t len,int backlog)
{
	if(bind(sock_fd,sa,len) == -1)
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

	return OK;
}

int CSocket::create_socket(int domain,int type)
{
	int sock_fd = ::socket(domain,type,0);
	if(sock_fd == -1)
	{
		log_error(-1,"create socket fail ,errno= %s",strerror(errno));
		return FAIL;
	}

	int iRet = set_reuseAddr(sock_fd);
	if(iRet != OK)
	{
		return FAIL;
	}

	return sock_fd;
}

int CSocket::set_reuseAddr(int fd)
{
	int yes = 1;
	int iRet = setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
	if(iRet != OK)
	{
		log_error(-1,"setsockopt : %s SO_REUSEADDR",strerror(errno));
		return FAIL;
	}

	return OK;
}

int CSocket::set_nonBlock(int fd)
{
	int flags;

	/* Set the socket non-blocking.
	 * Note that fcntl(2) for F_GETFL and F_SETFL can't be
	 * interrupted by a signal. */
	if ((flags = fcntl(fd, F_GETFL)) == -1)
	{
		log_error(-1, "fcntl(F_GETFL): %s", strerror(errno));
		return FAIL;
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		log_error(-1, "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno));
		return FAIL;
	}

	return OK;
}

int CSocket::set_keepAlive(int fd)
{
    int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(yes)) == -1)
    {
        log_error(-1, "setsockopt SO_KEEPALIVE: %s", strerror(errno));
        return FAIL;
    }
    return OK;
}

int CSocket::tcp_generalConnect(char *addr,int port,char* source_addr,int flags)
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
		sock_fd = ::socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		if(sock_fd == -1)
			continue;
		int iRet = set_reuseAddr(sock_fd);
		if(iRet != OK)
			return FAIL;

		if(flags & CONNECT_NONBLOCK )
		{
			iRet = set_nonBlock(sock_fd);
			if(iRet != OK)
				return FAIL;
		}

		// bind client port if necessuary
		if(source_addr)
		{
			int bound = 0;
			/* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
			if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0)
			{
				log_error(-1, "%s", gai_strerror(rv));
				freeaddrinfo(servinfo);
				return FAIL;
			}
			for (b = bservinfo; b != NULL; b = b->ai_next)
			{
				if (bind(sock_fd,b->ai_addr,b->ai_addrlen) != -1)
				{
					bound = 1;
					break;
				}
			}
			if (!bound)
			{
				log_error(-1, "bind: %s", strerror(errno));
				freeaddrinfo(servinfo);
				return FAIL;
			}
		}

		iRet = connect(sock_fd,p->ai_addr,p->ai_addrlen);
		if( iRet == -1)
		{
			/*Connection already in progress*/
			if(errno == EINPROGRESS && flags && CONNECT_NONBLOCK)
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

int CSocket::general_accept(int s, struct sockaddr *sa, socklen_t *len)
{
    int fd;
    while(1)
    {
        fd = accept(s,sa,len);
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
    return fd;
}

int CSocket::create_tcpServer(int port,char* bindaddr,int backlog)
{
	int sock_fd = -1;
	if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		log_error(-1,"socket create fail ...");
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

		iRet = listen(sock_fd,p->ai_addr,p->ai_addrlen,backlog);
		if(iRet != OK)
		{
			return iRet;
		}
		log_info(" listenning on port %d ...",port);
	}

	freeaddrinfo(servinfo);
	return sock_fd;
}

int CSocket::tcp_connect(char* addr,int port)
{
	return tcp_generalConnect(addr,port,NULL,CONNECT_NONE);

}

int CSocket::tcp_accept(int sock_fd,char* ip,size_t ip_len,int * port)
{
	int fd;
	struct sockaddr_storage sa;
	socklen_t salen = sizeof(sa);

	if ((fd = general_accept(sock_fd,(struct sockaddr*)&sa,&salen)) == -1)
		return FAIL;

	if (sa.ss_family == AF_INET)
	{
		struct sockaddr_in *s = (struct sockaddr_in *)&sa;
		if(ip) inet_ntop(AF_INET,(void *)&(s->sin_addr),ip,ip_len);
		if(port) *port = ntohs(s->sin_port);
	}

	return fd;
}


int CSocket::write(int fd,char* buf,int count)
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
int CSocket::read(int fd, char *buf, int count)
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

} /* namespace socket_pra */
