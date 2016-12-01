/*
 * thread_test.cpp
 *
 *  Created on: 2014年10月31日
 *      Author: mengpl
 */
#include <iostream>

#include "CThreadPool.h"

using namespace socket_pra;

class CMyTask : public CTask
{
private:
    int  m_i;
public:
    CMyTask() : CTask(0), m_i(0)
    {}

    void set(int i) { m_i = i; }

    int factorial(int i)
    {
        return i;
 /*       int iRet=1;
        for(;i>1;i--)
        {
            iRet *= i;
        }
        return iRet;
 */
    }
    void run()
    {
        int i = factorial(m_i);
    	log_info(" a new thread i =%d",i);
        if ((i %10000) == 0)
            log_info("=%d\n", m_i);
    }

    void timeout()
    {
        log_info(" task time out");
    }
};

void test_threadPool()
{
    try
    {
        CThreadPool threadpool(3, //最大线程
                               3, //最小空闲线程
                               3, //最大空闲线程
                               10, //队列任务超时时间（秒）
                               100, //队列最大size
                               10); //线程回收时间间隔（秒)
        threadpool.start();
        char c;
        while(true)
        {
            int iStart,iEnd;

            log_info("pls input start and end number: ");
            std::cin >> iStart >> iEnd;
            log_info("########## total=%d, busy=%d istart = %d, iend = %d", threadpool.get_totalThreadCount(),
                       threadpool.get_busiThreadCount(),iStart,iEnd);
            if (iStart == 0)
                break;
            for (int i= iStart; i<=iEnd; i++)
            {
                CMyTask * pTask = new CMyTask;
                if (pTask == NULL)
                {
                	log_error(-1," create task fail ");
                	return ;
                }
                pTask->set (i);
                threadpool.push_task(pTask);
                log_info("%d end\n",i);
            }
        }

        log_info("@@@@@@@@@@@@@@\n");
            threadpool.stop();
        log_info("@@@@@@@@@@@@@@\n");
    }
    catch(std::exception &e)
    {
    	log_info("exception\n");
        log_info("%s", e.what());
    }
}

int main(int argc, char* argv[])
{
	char ch;
	try
	{
		test_threadPool();
	}
	catch(std::exception &e)
	{
		log_info("exception\n");
		log_info("%s", e.what());
	}
    return 0;
}
