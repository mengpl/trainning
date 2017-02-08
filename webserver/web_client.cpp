#include "web_client.h"

namespace webserver
{
    int CWebClient::web_client_create(int iListenFd)
    {
        m_iFd = m_sBaseSocket.accept(iListenFd,m_szIp,IP_CHAR_LENGTH,&m_iPort);
        
        m_sBaseSocket.set_reuseAddr(m_iFd);
        log_info(" a new client conncted ip %s, port %d",m_szIp,m_iPort);

    }

    int CWebClient::web_client_receive()
    {
        int nBytes;
        
        while(1)
        {
            if((nBytes = m_sBaseSocket.read(m_iFd,m_szRequest,WEB_REQUEST_LENGTH)) == 0)
            {
                break;
            }
            else if(-1 == nByte)
            {
                break;
            }
            log_info("recive from client : %s",m_szRequest);
        }

        close(m_iFd);
    }
}