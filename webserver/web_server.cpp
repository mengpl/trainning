#include "web_server.h"

void client_callback(void* callback_data, uint8_t msg, uint32_t handle, void* pParam)
{
    if (msg == NETLIB_MSG_CONNECT)
    {
        // CLoginConn* pConn = new CLoginConn();
        // pConn->OnConnect2(handle, LOGIN_CONN_TYPE_CLIENT);
    }
    else
    {
        // log("!!!error msg: %d ", msg);
    }
}

int main(int argc, char** argv )
{
    LOG_INIT;
    
    // 信号处理
    signal(SIGPIPE, SIG_IGN);

    // 初始化netlib
    int ret = netlib_init();

    //读取配置文件
    CReadConfig cConfig("webserver.conf");

    //获取监听端口
    string strPort = cConfig.read_config("port");
    int iPort = atoi(strPort.c_str());

    //本机IP监听
    char localaddr[40] = "127.0.0.1";

    //listen
    ret = netlib_listen(localaddr, iPort, client_callback, NULL);
    if (ret == NETLIB_ERROR)
        return ret;
    
    log_info("now enter the event loop...");
    
    writePid();

    netlib_eventloop();
}