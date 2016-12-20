#include <stdlib.h>
#include <string>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "processtest.h"


void test_system()
{
    std::string strCmd("./build/test");
    
    int status = system(strCmd.c_str());
    
    if (status < 0)
    {
        printf("cmd: %s\t error: %s", strCmd.c_str(), strerror(errno));
        return;
    }

}