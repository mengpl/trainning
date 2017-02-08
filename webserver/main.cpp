#include "main.h"

using namespace webserver;
int main(int argc, char** argv )
{
    //init config
    CReadConfig cConfig("webserver.conf");
    string strPort = cConfig.read_config("port");
    int iPort = atoi(strPort.c_str());
    char localaddr[40] = "127.0.0.1";
    int backlog = 10;
    //listen
    CWebServer cWebServer;
    cWebServer.m_iListenFd = cWebServer.create_server(iPort,localaddr,backlog);

    int iRet = cWebServer.waitfor_clients();

    
}