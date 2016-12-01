
CC = g++
CPPFLAGS = -O2 -fpic -ftemplate-depth-64  -m64 -ggdb
CPPMICRO =
SUFFIX = 
USE_LIB =  -lrt 
BUILD_PATH = ./build
MAKE_DIR = mkdir -p 
LOC_LIB = $(HOME)/workspace/git_code/lib

objects = CThread.o CThreadPool.o CEvent.o
sharedLib = libthreadpoolD.so

.PHONY:all

all:$(sharedLib)

path_objects = 	$(addprefix $(BUILD_PATH)/,$(objects))

$(sharedLib):$(objects)
	$(CC) -shared $(path_objects) $(USE_LIB) -o $(BUILD_PATH)/$@
	$(MAKE_DIR) $(LOC_LIB)	
	cp -prf $(BUILD_PATH)/$(sharedLib) $(LOC_LIB)/
$(objects):%.o:%.cpp
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(CPPMICRO) -c $< $(USE_LIB) -o $(BUILD_PATH)/$@

.PHONY:install
install:all 
	$(MAKE_DIR) $(LOC_LIB)
	cp -rpf  $(BUILD_PATH)/$(sharedLib) $(LOC_LIB)/
	
.PHONY:clean
clean:
	 rm -rf $(path_objects) $(BUILD_PATH)/$(sharedLib)

test_target = thread_test.exe
path_sharedLib = $(addprefix $(LOC_LIB)/,$(sharedLib))

.PHONY:test

test:$(test_target)

$(test_target):%.exe:%.cpp
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(CPPMICRO) $< $(USE_LIB) ${path_sharedLib} -o $(BUILD_PATH)/$@
