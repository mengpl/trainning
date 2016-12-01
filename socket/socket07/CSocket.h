/*
 * CSocket.h
 *
 *  Created on: 2014年10月30日
 *      Author: mengpl
 */

#ifndef CSOCKET_H_
#define CSOCKET_H_

#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "socket_define.h"

namespace socket_pra {

class CSocket {
public:
	CSocket(){};
	virtual ~CSocket(){};

public:
	int create_tcpServer(int port, char *bindaddr, int backlog);
//	int create_unixServer(char *path, mode_t perm, int backlog);

	int tcp_accept(int serversock, char *ip, size_t ip_len, int *port);
//	int unix_accept(int serversock);

	int write(int fd, char *buf, int count);
	int read(int fd, char *buf, int count);

	int tcp_connect(char *addr, int port);

	int set_reuseAddr(int fd);
	int set_keepAlive(int fd);
//	int unix_connect(char *path);

//	int set_socketOption(int fd,char* option,char* value);
//	int get_socketOption(int fd,char* option,char* value);
//	int get_peerName();

private:
	int listen(int s, struct sockaddr *sa, socklen_t len, int backlog);
	int create_socket(int domain,int type);

	int set_nonBlock(int fd);
	int tcp_generalConnect(char *addr, int port, char *source_addr, int flags);
	int general_accept(int s, struct sockaddr *sa, socklen_t *len);
};

} /* namespace socket_pra */

#endif /* CSOCKET_H_ */
