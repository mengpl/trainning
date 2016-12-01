/*
 * iotest.h
 *
 *  Created on: 2016/05/30
 *  V0.1使用open/creat/close/lseek/read/write 等函数
 *      Author: mengpl
 */

#ifndef __IO_TEST_H__
#define __IO_TEST_H__


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void file_io_test();

#endif /* __IO_TEST_H__ */
