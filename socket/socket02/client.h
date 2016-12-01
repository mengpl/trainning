/*
 * client.h
 *
 *  Created on: 2014年10月20日
 *      Author: Mengpl
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SERVPORT 6000

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

#endif /* CLIENT_H_ */
