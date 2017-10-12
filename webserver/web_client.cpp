#include "web_client.h"

namespace webserver
{
    int CWebClient::web_client_create(int iListenFd)
    {
        m_iFd = m_sBaseSocket.accept(iListenFd,m_sIp.m_szBuffer,IP_CHAR_LENGTH,&m_iPort);
        
        m_sBaseSocket.set_reuseAddr(m_iFd);
        log_info(" a new client conncted ip %s, port %d",m_sIp.m_szBuffer,m_iPort);

        return 0;
    }

    int CWebClient::web_client_receive()
    {
        m_sRequest.data.reserve(WEB_REQUEST_LENGTH);
        ssize_t nBytes = m_sBaseSocket.read(m_iFd,m_sRequest.data.m_szBuffer,WEB_REQUEST_LENGTH);

        if(nBytes > 0)
        {
            m_sRequest.data.set_len(m_sRequest.data.get_len() + nBytes);
            log_info("recive from client size : %zd",nBytes);
            log_info("recive from client : %s",m_sRequest.data.m_szBuffer);
        }
        else if(nBytes == 0)
        {
            log_info("client may be closed ip %s, port %d",m_sIp.m_szBuffer,m_iPort);
        }
        else
        {
            log_info("recive data fail! from client : %s",m_sIp.m_szBuffer);
        }

        return nBytes;
    }

    int CWebClient::web_client_process()
    {
        log_info(" begin web client process ");

        if(strncmp(m_sRequest.data.m_szBuffer,"GET ",4))
        {
            m_iAction = WEB_CLIENT_PREDICATION_GET;
            
        }
        else if(strncmp(m_sRequest.data.m_szBuffer,"OPTIONS ",8))
        {
            m_iAction = WEB_CLIENT_PREDICATION_OPTION;
        }

        return 0;
    }

}