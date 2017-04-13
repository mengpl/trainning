#ifdef __LINUX__
#include <sys/epoll.h>
#else
#include <sys/poll.h>
#endif

#include "web_server.h"

namespace webserver
{
    #define OPEN_MAX 100
    int CWebServer::waitfor_clients()
    {
#ifdef __LINUX__
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
#else
        struct pollfd clientfds[OPEN_MAX];
        clientfds[0].fd = m_iListenFd;
        clientfds[0].events = POLLIN;

        for (int i = 1; i < OPEN_MAX; i++)
        {
            clientfds[i].fd= -1;
        }

        int nReady ;
        int max_fd = 0;
        bool bFull = false;
        int i ;
        while(1)
        {
            nReady =  poll(clientfds,max_fd+1,-1);
            if(nReady == FAIL)
            {
                log_error(-1," poll fail ...");
                break;
            }

            if(clientfds[0].revents & POLLIN)
            {
                for (i = 1; i < OPEN_MAX; i++)
                {
                    if(clientfds[i].fd < 0)
                    {
                        CWebClient * pClient = new CWebClient();
                        pClient->web_client_create(m_iListenFd);

                        clientfds[i].fd = pClient->m_iFd;
                        clientfds[i].events = POLLIN;
                        m_mapClient.insert(std::make_pair(pClient->m_iFd,pClient));
                        bFull = false;
                        break;
                    }
                }

                if(bFull)
                {
                    log_error(-1," too many clients task is full!");
                    continue;
                }
                
                max_fd = i > max_fd ? i : max_fd;

                if(--nReady < 0)
                    continue;
            }

            for (int i = 1; i <= max_fd; i++)
            {
                if(clientfds[i].fd < 0)
                    continue;
                if(clientfds[i].revents & POLLIN)
                {
                    CWebClientMap::iterator itMap = m_mapClient.find(clientfds[i].fd);
                    if(itMap != m_mapClient.end())
                    {
                        int result = itMap->second->web_client_receive();
                        if(result > 0)
                        {
                            itMap->second->web_client_process();
                        }
                        else
                        {
                            close(clientfds[i].fd);
                            clientfds[i].fd = -1;
                            m_mapClient.erase(itMap);
                        }ß
                    }
                    else
                    {
                        log_error(-1,"can not find this fd = %d,please check!",clientfds[i].fd);
                        continue;
                    }
                }
            }
        }
        close(m_iListenFd);
#endif
    return 0;
    }

}