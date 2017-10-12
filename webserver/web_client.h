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

    enum web_client_predication
    {
        WEB_CLIENT_PREDICATION_GET    = 0,
        WEB_CLIENT_PREDICATION_POST   = 1,
        WEB_CLIENT_PREDICATION_OPTION = 2,
        WEB_CLIENT_PREDICATION_PUT    = 3,
        WEB_CLIENT_PREDICATION_HEAD    = 4
    };

    // content-types
    #define CT_APPLICATION_JSON             1
    #define CT_TEXT_PLAIN                   2
    #define CT_TEXT_HTML                    3
    #define CT_APPLICATION_X_JAVASCRIPT     4
    #define CT_TEXT_CSS                     5
    #define CT_TEXT_XML                     6
    #define CT_APPLICATION_XML              7
    #define CT_TEXT_XSL                     8
    #define CT_APPLICATION_OCTET_STREAM     9
    #define CT_APPLICATION_X_FONT_TRUETYPE  10
    #define CT_APPLICATION_X_FONT_OPENTYPE  11
    #define CT_APPLICATION_FONT_WOFF        12
    #define CT_APPLICATION_FONT_WOFF2       13
    #define CT_APPLICATION_VND_MS_FONTOBJ   14
    #define CT_IMAGE_SVG_XML                15
    #define CT_IMAGE_PNG                    16
    #define CT_IMAGE_JPG                    17
    #define CT_IMAGE_GIF                    18
    #define CT_IMAGE_XICON                  19
    #define CT_IMAGE_ICNS                   20
    #define CT_IMAGE_BMP                    21
    #define CT_PROMETHEUS                   22

    class CInfo {
    public:
        CInfo():code(0){};
        ~CInfo(){};

    public:
        CBuffer header;                 // header
        CBuffer data;                   // data buffer
        int contenttype;                // contenttype
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
        int _check_request();

    public:
        int m_iFd;   
        int m_iPort; 
        int m_iMode; //模式
        int m_iAction; //谓词类型 
        CBuffer m_sIp; // 客户的ip

        CInfo m_sRequest; // 收到的客户的请求
        CInfo m_sResponse; // 发给客户端的返回包
    private:
        CBaseSocket  m_sBaseSocket;
    };
}

#endif //__WEB_CLIENT_H__