
CC = g++
CPPFLAGS = -O2 -fpic -ftemplate-depth-64  -m64 -ggdb
CPPMICRO =
SUFFIX = 
USE_LIB =  -lrt 
BUILD_PATH = ./build
MAKE_DIR = mkdir -p 
LOC_LIB = $(HOME)/workspace/git_code/lib

objects = CSocket.o
sharedLib = libsocketD.so

target = client.exe server.exe

.PHONY:all

all:$(sharedLib) $(target)

$(sharedLib):$(objects)
	$(CC) -shared $(BUILD_PATH)/*.o $(USE_LIB) -o $(BUILD_PATH)/$@
	$(MAKE_DIR) $(LOC_LIB)	
	cp -prf $(BUILD_PATH)/lib*D.so $(LOC_LIB)/

$(target):%.exe:%.cpp

	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(CPPMICRO) $< $(USE_LIB) $(LOC_LIB)/${sharedLib} -o $(BUILD_PATH)/$@

$(objects):%.o:%.cpp
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(CPPMICRO) -c $< $(USE_LIB) -o $(BUILD_PATH)/$@

#server.exe:server.cpp
#	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
#	$(CC) $(CPPFLAGS) $(CPPMICRO) $< $(USE_LIB) $LOC_LIB/$(sharedLib) -o $(BUILD_PATH)/$@

.PHONY:install
install:all 
	$(MAKE_DIR) $(LOC_LIB)
	cp -rpf  $(BUILD_PATH)/lib*D.so $(LOC_LIB)/
	
.PHONY:clean
clean:
	 rm -rf $(BUILD_PATH)
