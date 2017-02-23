#include <sys/epoll.h>
#include "web_server.h"

namespace webserver
{
    #define OPEN_MAX 100
    int CWebServer::waitfor_clients()
    {
        struct epoll_event ev,events[20];
        int epfd = epoll_create(OPEN_MAX);

        ev.data.fd = m_iListenFd;
        ev.events = EPOLLIN;
        epoll_ctl(epfd,EPOLL_CTL_ADD,m_iListenFd,&ev);

        int nReady ;
        while(1)
        {
            nReady =  epoll_wait(epfd, events, 20, -1);
            if(nReady == FAIL)
            {
                log_error(-1," epoll_wait fail ...");
                break;
            }

            for(int i = 0;i < nReady; ++i)
            {
                if(events[i].data.fd==m_iListenFd)
                {
                    CWebClient * pClient = new CWebClient();
                    pClient->web_client_create(m_iListenFd);

                    ev.data.fd=pClient->m_iFd;
                    ev.events=EPOLLIN;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,pClient->m_iFd,&ev);

                    m_mapClient.insert(std::make_pair(pClient->m_iFd,pClient));
                }
                else if(events[i].events&EPOLLIN)
                {
                    if(events[i].data.fd < 0)
                        continue;
                    CWebClientMap::iterator itMap = m_mapClient.find(events[i].data.fd);
                    if(itMap != m_mapClient.end())
                    {
                        int result = itMap->second->web_client_receive();
                        if(!result)
                            itMap->second->web_client_process();
                    }
                    else
                    {
                        log_error(-1,"can not find this fd = %d,please check!",events[i].data.fd);
                        continue;
                    }
                }
            }
        }

        close(m_iListenFd);
    }

}