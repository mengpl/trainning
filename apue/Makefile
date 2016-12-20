#define compile option
CC = g++
CPPFLAGS = -O2 -fpic -ftemplate-depth-64  -m64 -g
COMMON_MICRO = 
BUILD_PATH = ./build
MAKE_DIR = mkdir -p 


##需要用户填写的内容
DEST=test_apue
DEST_TYPE=BIN
DEST_SOURCES=iotest.cpp processtest.cpp main.cpp
USER_DEFS=
LINK_USER_LIB= 
LINK_SYS_LIB= 
INCLUDE_PATH = ./ 


##推导过程
LOGDEBUG = 1
DLLTAIL = so

ifeq "$(LOGDEBUG)" "1"
	BUILDTYPE = D
else
	BUILDTYPE =
endif	

ifeq "$(DEST_TYPE)" "BIN"
	TARGET = $(DEST)
else ifeq "$(DEST_TYPE)" "DLL"
	TARGET = $(DEST)$(BUILDTYPE).$(DLLTAIL)
endif

ALL_MICRO += $(USER_DEFS)
ALL_MICRO += $(COMMON_MICRO)

TOTAL_DEFS_MICRO = $(addprefix -D,$(ALL_MICRO))

ALL_DEPENDENCIES = $(patsubst %.cpp,%.o,$(DEST_SOURCES))
TOTAL_DEPENDENCIES = $(addprefix $(BUILD_PATH)/,$(ALL_DEPENDENCIES))

TOTAL_INCLUDE_PATH = $(addprefix -I ,$(INCLUDE_PATH))

ifneq ($(LINK_SYS_LIB),"")
	TOTAL_SHARE_LIB = $(LINK_SYS_LIB)
endif 

ifneq ($(LINK_USER_LIB),"")
	TOTAL_SHARE_LIB += $(addprefix $(NDB_HOME)/lib/,$(LINK_USER_LIB))
endif

.PHONY:all install clean
all:$(TARGET)
%.o:%.cpp
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(TOTAL_DEFS_MICRO) $(TOTAL_INCLUDE_PATH) -c $< -o $(BUILD_PATH)/$@

$(TARGET):$(ALL_DEPENDENCIES)
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(TOTAL_DEFS_MICRO) $(TOTAL_DEPENDENCIES) $(TOTAL_INCLUDE_PATH) $(TOTAL_SHARE_LIB) -o $(BUILD_PATH)/$@

install:
	$(MAKE_DIR) $(NDB_HOME)/lib
	cp -rpf  $(BUILD_PATH)/$(TARGET) $(NDB_HOME)/lib

clean:
	rm -rf $(BUILD_PATH)/*