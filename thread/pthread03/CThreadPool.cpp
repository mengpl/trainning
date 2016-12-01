/*
 * CThreadPool.cpp
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#include "CThreadPool.h"

namespace socket_pra {

CWorkThread::CWorkThread(CThreadPool* pThreadPool)
{
	m_nTotalThreads = 0;
	m_nBusiThreads = 0;
	m_pTask = 0;
	m_pThreadPool = pThreadPool;
	m_bStop = true;
	m_pThread = new CThread(this);
	m_pThread->start();

}

CWorkThread::~CWorkThread()
{
	if(m_pThread)
		delete m_pThread;
	m_pThread = 0;
}

void CWorkThread::set_task(CTask* pTask)
{
	m_pTask = pTask;
	pTask->set_threadId(get_thread()->get_threadId());
	m_cEvent.notify();
//	log_info(" CWorkThread::set_task m_cEvent.notify");
}

void CWorkThread::run()
{
	m_bStop = false;
	while(true)
	{
//		log_info(" CWorkThread::run m_cEvent.wait");
		m_cEvent.wait();
		if(m_bStop)
			break;
		try
		{
			if(m_pTask)
				m_pTask->run();
		}
		catch(std::exception & e)
		{
		}
		catch(...)
		{
		}

		if(m_pTask)
		{
			delete m_pTask;
			m_pTask = 0;
		}

		m_pThreadPool->ret_toPool(this);
	}
}

void CWorkThread::stop()
{
	m_bStop = true;
	m_cEvent.notify();
}

CQueueHandler::CQueueHandler(CThreadPool* pThreadPool)
{
	m_pThreadPool = pThreadPool;
	m_bStop = false;
	m_pThread = new CThread(this);
	m_pThread->start();
}

CQueueHandler::~CQueueHandler()
{
    if (m_pThread)
        delete m_pThread;
    m_pThread = 0;
}

void CQueueHandler::run()
{
	while(true)
	{
		try
		{
			CTask * pTask = m_pThreadPool->pop_task();
			if(pTask)
			{
				m_pThreadPool->run_task(pTask);
			}
			else
			{
				m_pThreadPool->wait_task();
			}

			if(m_bStop)
				break;
		}
		catch(std::exception & e)
		{}
		catch(...)
		{}
	}
}

void CQueueHandler::stop()
{
    m_bStop = true;
    m_pThreadPool->notify_task();
}

CHarvester::CHarvester(CThreadPool* pThreadPool)
{
	m_pThreadPool = pThreadPool;
	m_bStop = false;
	m_pThread = new CThread(this);
	m_pThread->start();
}

CHarvester::~CHarvester()
{
    if (m_pThread)
        delete m_pThread;
    m_pThread = 0;
}

void CHarvester::run()
{
	while(true)
	{
		try
		{
			wait(m_pThreadPool->get_harvestInterval());

			if(m_bStop)
				break;

			m_pThreadPool->harvest_spare();
		}
		catch(std::exception & e)
		{}
		catch(...)
		{}
	}
}

void CHarvester::stop()
{
    m_bStop = true;
    CThread::notify(get_thread());
}

CThreadPool::CThreadPool(int nMaxThreads,
							int nMinIdleThreads,
							int nMaxIdleThreads,
							int nQueueTimeOut,
							int nQueueMaxSize,
							int nHarvestInterval)
{
	m_nMaxThreads = nMaxThreads;
	m_nMinIdleThreads = nMinIdleThreads;
	m_nMaxIdleThreads = nMaxIdleThreads;
	m_nQueueTimeOut = nQueueTimeOut;
	m_nQueueMaxSize = nQueueMaxSize;
	m_nHarvestInterval = nHarvestInterval;

	m_pQueueHandler = 0;
	m_pHarvester = 0;

	m_nTotalThreads = 0;
	m_nBusiThreads = 0;
	m_bStop = true;
	m_bTaskQueueFull = false;

	m_bNeedNotifyIdle = false;
}

CThreadPool::~CThreadPool() {
	stop();
}

void CThreadPool::ret_toPool(CWorkThread* pWork)
{
	log_info("ret_toPool");
	CAutoMutex cMutex(&m_cMutex);
	cMutex.lock();
	m_cIdleList.push_worker(pWork);
	m_nBusiThreads--;
	cMutex.unlock();
}

void CThreadPool::run_task(PTask pTask)
{
	if(0 == m_nTotalThreads)
	{
		delete pTask;
		log_error(-1,"thread pool not start.");
		return;
	}

	int iRet = 0;
	CAutoMutex cMutex(&m_cMutex);
	cMutex.lock();
	if(m_nBusiThreads == m_nTotalThreads)
	{
		if(m_nTotalThreads < m_nMaxThreads)
		{
			int nLeft = m_nMaxThreads - m_nTotalThreads;
			int nWorker = m_nMinIdleThreads <= nLeft ? m_nMinIdleThreads : nLeft;
			create_worker(nWorker);
		}
		else
		{
			m_bNeedNotifyIdle = true;
			cMutex.unlock();
			iRet = m_cIdleList.wait(m_nQueueTimeOut);
			cMutex.lock();
		}
	}

	CWorkThread * pWorker;

	if(iRet == 0)
	{
		pWorker = m_cIdleList.pop_worker();
		if(0 == pWorker)
		{
			push_task(pTask);
			return;
		}
		m_nBusiThreads++;
		pWorker->set_task(pTask);
	}
	else
	{
		pTask->timeout();
		delete pTask;
	}
	cMutex.unlock();

}


void CThreadPool::harvest_spare()
{
	if((m_nTotalThreads - m_nBusiThreads) <= m_nMaxIdleThreads)
		return;

	CAutoMutex cMutex(&m_cMutex);
	int nTotalFree = m_nTotalThreads - m_nBusiThreads - m_nMaxIdleThreads;
	CWorkThread * pWorker;
	for(int i = 0; i < nTotalFree; i++)
	{
		pWorker = m_cIdleList.pop_worker();
		if(pWorker)
		{
			pWorker->stop();
			m_cWorkerList.erase_worker(pWorker);
			delete pWorker;
			m_nTotalThreads--;
		}
	}
}

void CThreadPool::create_worker(int nWorkers)
{
	log_info("create %d workers",nWorkers);
	if(nWorkers > m_nMaxThreads)
		nWorkers = m_nMaxThreads;

	CWorkThread * pWork;
	for(int i = 0 ;i < nWorkers; i++)
	{
		pWork = new CWorkThread(this);
		m_cIdleList.push_worker(pWork);
		m_cWorkerList.push_worker(pWork);
		m_nTotalThreads++;
	}
}

void CThreadPool::start()
{
	log_info("begin to start thread pool ...");
	m_nTotalThreads = m_nBusiThreads = 0;
	create_worker(m_nMinIdleThreads);

	m_pHarvester = new CHarvester(this);
	m_pQueueHandler = new CQueueHandler(this);
	m_bStop = false;
	log_info(" thread pool start success totalthreads = %d",m_nTotalThreads);
}

void CThreadPool::stop()
{
	if(!m_bStop)
	{
		m_bStop = true;
		m_cQueueSizeEvent.notify();

		m_pHarvester->stop();
		m_pQueueHandler->stop();

		if (m_pHarvester)
			delete m_pHarvester;
		if (m_pQueueHandler)
			delete m_pQueueHandler;

		m_pHarvester = 0;
		m_pQueueHandler = 0;

		CAutoMutex cMutex(&m_cMutex);
		CWorkThread * pWorker ;
		while(true)
		{
			cMutex.lock();
				pWorker = m_cWorkerList.pop_worker();
			cMutex.unlock();

			if (!pWorker)
					break;
			pWorker->stop();
				delete pWorker;
		}

		cMutex.lock();
		m_cIdleList.clear();
		cMutex.unlock();

		m_nTotalThreads = m_nBusiThreads = 0;

		PTask pTask;
		while ( (pTask = m_cTaskQueue.pop_task()) !=0 )
		{
			pTask->timeout();
			delete pTask;
		}
	}
}

} /* namespace socket_pra */
