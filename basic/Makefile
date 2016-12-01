objects = stlstringtest
objects += server
objects += client
objects += templateFunction
objects += testset
objects += testmap
objects += epoll_server
objects += epoll_client
objects += select_server
objects += select_client
objects += tcpclient
objects += tcpserver

CC = g++
CPPFLAGS = -O2 -fpic -ftemplate-depth-64  -m64 -ggdb
CPPMICRO =
SUFFIX = 
USE_LIB = -pthread

.PHONY:all
	
all:$(objects) lock

$(objects):%$(SUFFIX):%.cpp 
	$(CC) $(CPPFLAGS) $(CPPMICRO) $< -o $@

lock:lock.cpp
	$(CC) $(CPPFLAGS) $(CPPMICRO) $< $(USE_LIB) -o $@

.PHONY:clean
clean:
	rm -rf $(objects) lock

