
CC = g++
CPPFLAGS = -O2 -fpic -ftemplate-depth-64  -m64 -ggdb
CPPMICRO =
SUFFIX = 
USE_LIB =
BUILD_PATH = ./build

target = client.exe server.exe

.PHONY:all

all:$(target)

$(target):%.exe:%.cpp
	$(CC) $(CPPFLAGS) $(CPPMICRO) $< $(USE_LIB) -o $(BUILD_PATH)/$@

#server.exe:server.cpp
#	$(CC) $(CPPFLAGS) $(CPPMICRO) $< $(USE_LIB) -o $(BUILD_PATH)/$@
	
.PHONY:clean
clean:
	 rm -rf $(BUILD_PATH)