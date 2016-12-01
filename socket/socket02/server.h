/*
 * server.h
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVPORT 6000    /*服务器监听端口号 */

#ifndef OK
#define OK 0;
#endif

#ifndef FAIL
#define FAIL -1;
#endif

#ifndef LOG_ERROR
#define log_error(error_no, error_msg) std::cout << "log [error] error no is : " << error_no << "  error msg is : " << error_msg << std::endl;
#endif

#ifndef LOG_INFO
#define log_info(error_msg) std::cout << "log [info] : " << error_msg << std::endl;
#endif

#endif /* SERVER_H_ */
