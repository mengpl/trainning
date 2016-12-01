/*
 * CThreadPool.h
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#ifndef CTHREADPOOL_H_
#define CTHREADPOOL_H_


#include <exception>
#include <algorithm>
#include <unistd.h>
#include "CThread.h"
#include "CTaskQueue.h"


namespace socket_pra {

class CThreadPool;
class CTask;
class CWorkThread : public CRunable
{
public:
	explicit CWorkThread(CThreadPool* pThreadPool);
	~CWorkThread();

	CThread * get_thread() const
	{
		return m_pThread;
	}

	void set_task(CTask* pTask);
	void run();
	void stop();
	bool is_stop(){return m_bStop;}

private:
	CThread * m_pThread;
	CEvent m_cEvent;
	CThreadPool * m_pThreadPool;
	CTask * m_pTask;
	bool m_bStop;

	int m_nTotalThreads;
	int m_nBusiThreads;

};

class CQueueHandler : public CRunable
{
public:
	explicit CQueueHandler(CThreadPool* pThreadPool);
	~CQueueHandler();
	void run();
	void stop();
private:
	CThread* m_pThread;
	CThreadPool* m_pThreadPool;
	bool m_bStop;
};

class CHarvester : public CRunable
{
public:
	explicit CHarvester(CThreadPool* pThreadPool);
	~CHarvester();
	void run();
	void stop();
private:
	CThread* m_pThread;
	CThreadPool* m_pThreadPool;
	bool m_bStop;
};

class CWorkerList
{
public:
	CWorkThread * pop_worker()
	{
		CWorkThread * pWorker = 0;
		if(!m_lstWorkThread.empty())
		{
			pWorker = m_lstWorkThread.front();
			m_lstWorkThread.erase(m_lstWorkThread.begin());
		}
		else
			pWorker = 0;
		return pWorker;
	}

	void push_worker(CWorkThread * pWorker)
	{
		m_lstWorkThread.push_back(pWorker);
	}

	void erase_worker(CWorkThread* pWorker)
	{
		std::vector<CWorkThread*>::iterator it;

		it = std::find(m_lstWorkThread.begin(), m_lstWorkThread.end(), pWorker);
		if(it != m_lstWorkThread.end())
			m_lstWorkThread.erase(it);
	}

	void clear()
	{
		m_lstWorkThread.clear();
	}

	void wait()
	{
		m_cEvent.wait();
	}

	int wait(int nSecs)
	{
		return m_cEvent.wait(nSecs);
	}

	void notify()
	{
		m_cEvent.notify();
	}
private:
	std::vector<CWorkThread *> m_lstWorkThread;
	CEvent m_cEvent;
	CMutex m_cMutex;

};

#define  MAXTHREADS 200
#define MINIDLE    5
#define MAXIDLE    10
#define QUEUETIMEOUT  20
#define QUEUEMAXSIZE  100
#define HARVESTINTERVAL 60

class CThreadPool {
public:
	explicit CThreadPool(int nMaxThreads = MAXTHREADS,
            int nMinIdleThreads = MINIDLE,
            int nMaxIdleThreads = MAXIDLE,
            int nQueueTimeOut = QUEUETIMEOUT,
            int nQueueMaxSize = QUEUEMAXSIZE,
            int nHarvestInterval = HARVESTINTERVAL);
	~CThreadPool();

	void ret_toPool(CWorkThread * pWork);
	void run_task(PTask pTask);
	void push_task(PTask pTask)
	{
		if(m_cTaskQueue.size() >= m_nQueueMaxSize)
		{
			CAutoMutex cMutex(&m_cQueueSizeMutex);
			cMutex.lock();
			m_bTaskQueueFull = true;
			log_info(" task queue is full ");
			cMutex.unlock();

			m_cQueueSizeEvent.wait(20);
			m_cQueueSizeEvent.reset();

			if(m_bStop)
			{
				pTask->timeout();
				return;
			}
		}

		m_cTaskQueue.push_task(pTask);
	}

	CTask * pop_task()
	{
		CTask * pTask = m_cTaskQueue.pop_task();
		if(m_bTaskQueueFull)
		{
			CAutoMutex cMutex(&m_cQueueSizeMutex);
			cMutex.lock();
			m_bTaskQueueFull = false;
			cMutex.unlock();
			m_cQueueSizeEvent.notify();
		}
		return pTask;
	}

	void wait_task()
	{
//		log_info(" m_cTaskQueue wait_task");
		m_cTaskQueue.wait_task();
	}

	void notify_task()
	{
		m_cTaskQueue.notify_task();
	}

	void harvest_spare();
	void create_worker(int nWorkers);
	void start();
	void stop();
private:
	int m_nMaxThreads;
    int m_nMinIdleThreads;
    int m_nMaxIdleThreads;

    int m_nQueueTimeOut;
    int m_nQueueMaxSize;
    int m_nHarvestInterval;

    int m_nTotalThreads;
    int m_nBusiThreads;

    bool m_bStop;

    bool m_bTaskQueueFull;
    CMutex m_cQueueSizeMutex;
    CEvent m_cQueueSizeEvent;

    CMutex m_cMutex;
    CTaskQueue m_cTaskQueue;
	CWorkerList m_cIdleList;
	CWorkerList m_cWorkerList;

	CQueueHandler *m_pQueueHandler;
	CHarvester  *m_pHarvester;

	bool m_bNeedNotifyIdle;
public:
    int get_harvestInterval() const
    {
        return m_nHarvestInterval;
    }

    int get_busiThreadCount() const
    {
        return m_nBusiThreads;
    }

    int get_totalThreadCount() const
    {
        return m_nTotalThreads;
    }
};

} /* namespace socket */

#endif /* CTHREADPOOL_H_ */
