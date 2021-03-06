#define compile option
CC = g++
CPPFLAGS = -O2 -fpic -ftemplate-depth-64  -m64 -g
COMMON_MICRO = 
BUILD_PATH = ./build
MAKE_DIR = mkdir -p 


##需要用户填写的内容
DEST=config_unittest
DEST_TYPE=BIN
DEST_SOURCES= config_unittest.cpp ../config.cpp
USER_DEFS= 
LINK_USER_LIB= libcurl.so liblog4cpp.so
LINK_SYS_LIB= -lgtest -lgtest_main
LIB_PATH = $(NDB_HOME)/lib 
INCLUDE_PATH = ./ ../ \
		$(NDB_HOME)/include \
		$(ORACLE_HOME)/rdbms/public \


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

# COMPILE_OPTION = -shared -mt -m64 

ALL_MICRO += $(USER_DEFS)
ALL_MICRO += $(COMMON_MICRO)

TOTAL_DEFS_MICRO = $(addprefix -D,$(ALL_MICRO))

ALL_DEPENDENCIES = $(patsubst %.cpp,%.o,$(DEST_SOURCES))
TOTAL_DEPENDENCIES = $(addprefix $(BUILD_PATH)/,$(ALL_DEPENDENCIES))

ifneq ($(INCLUDE_PATH),"")
	TOTAL_INCLUDE_PATH = $(addprefix -I ,$(INCLUDE_PATH))
endif

ifneq ($(LIB_PATH),"")
	TOTAL_SHARE_LIB = $(addprefix -L ,$(LIB_PATH))
endif

ifneq ($(LINK_SYS_LIB),"")
	TOTAL_SHARE_LIB += $(LINK_SYS_LIB)
endif 

ifneq ($(LINK_USER_LIB),"")
	TOTAL_SHARE_LIB += $(addprefix $(NDB_HOME)/lib/,$(LINK_USER_LIB))
endif

.PHONY:all install clean install_header
all:$(TARGET)
%.o:%.cpp
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(TOTAL_DEFS_MICRO) $(TOTAL_INCLUDE_PATH) -c $< -o $(BUILD_PATH)/$@

$(TARGET):$(ALL_DEPENDENCIES)
	$(MAKE_DIR) $(BUILD_PATH) $(dir $<)
	$(CC) $(CPPFLAGS) $(TOTAL_DEFS_MICRO) $(TOTAL_DEPENDENCIES) $(TOTAL_INCLUDE_PATH) $(COMPILE_OPTION) $(TOTAL_SHARE_LIB) -o $(BUILD_PATH)/$@

install:install_header
	$(MAKE_DIR) $(NDB_HOME)/lib
	cp -rpf  $(BUILD_PATH)/$(TARGET) $(NDB_HOME)/lib

install_header:
	$(MAKE_DIR) $(NDB_HOME)/include/tinyxml
	cp -rpf  *.h $(NDB_HOME)/include/tinyxml

clean:
	rm -rf $(BUILD_PATH)/*