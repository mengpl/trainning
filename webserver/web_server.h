#ifndef __WEB_SERVER_H__
#define __WEB_SERVER_H__
#include <map>
#include "base_socket.h"
#include "web_client.h"

namespace webserver
{
    #define IP_CHAR_LENGTH 40

    // class CWebClient;
    typedef std::map<int,CWebClient *> CWebClientMap;

    class CWebServer : public CBaseSocket
    {
    public:
        CWebServer():m_iListenFd(-1){};
        ~CWebServer(){};
    public:
        int waitfor_clients();
    public:
        int m_iListenFd;
        CWebClientMap m_mapClient;
    };
};

#endif //__WEB_SERVER_H__