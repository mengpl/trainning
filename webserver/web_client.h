#ifndef __WEB_CLIENT_H__
#define __WEB_CLIENT_H__
#include <stdint.h>
#include "base_socket.h"
#include "web_buffer.h"

namespace webserver
{
    #define WEB_REQUEST_LENGTH 16384
    #define URL_MAX 8192
    #define ZLIB_CHUNK  16384
    #define HTTP_RESPONSE_HEADER_SIZE 4096
    #define COOKIE_MAX 1024
    #define ORIGIN_MAX 1024
    #define IP_CHAR_LENGTH 40

    enum web_client_mode
    {
        WEB_CLIENT_MODE_NORMAL      = 0 ,
        WEB_CLIENT_MODE_FILECOPY    = 1 ,
        WEB_CLIENT_MODE_OPTIONS     = 2
    };

    class CInfo {
    public:
        CInfo():code(0){};
        ~CInfo(){};

    public:
        CBuffer header;                 // our response header
        CBuffer data;                   // our response data buffer
        int code;                       // the HTTP response code
    };

    class CWebClient
    {
    public:
        CWebClient():m_iPort(0),m_iFd(-1),m_sIp(CBuffer(IP_CHAR_LENGTH)),m_iMode(0)
        {
        };
        ~CWebClient(){};
    public:
        int web_client_create(int iListenFd);
        int web_client_receive();
        int web_client_process();

    private:
        int _process_request();
    public:
        int m_iFd;   
        int m_iPort; 
        int m_iMode; //模式
        CBuffer m_sIp; // 客户的ip

        CInfo m_sRequest; // 收到的客户的请求
        CInfo m_sResponse; // 发给客户端的返回包
    private:
        CBaseSocket  m_sBaseSocket;
    };
}

#endif //__WEB_CLIENT_H__