#ifndef __WEB_CLIENT_H__
#define __WEB_CLIENT_H__
#include "base_socket.h"

namespace webserver
{
    #define IP_CHAR_LENGTH 40
    #define WEB_REQUEST_LENGTH 16384
    class CWebClient : public CBaseSocket
    {
    public:
        CWebClient():m_iPort(0),m_iFd(-1)
        {
        };
        ~CWebClient(){};
    public:
        int web_client_create(int iListenFd);
        int web_client_receive();

    public:
        char m_szIp[IP_CHAR_LENGTH];
        int m_iPort;
        int m_iFd;
        char m_szRequest[WEB_REQUEST_LENGTH];

    private:
        CBaseSocket m_sBaseSocket;
    };
}

#endif //__WEB_CLIENT_H__