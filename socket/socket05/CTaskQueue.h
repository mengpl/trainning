/*
 * CTaskQueue.h
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#ifndef CTASKQUEUE_H_
#define CTASKQUEUE_H_

#include <pthread.h>
#include <queue>
#include "CMutex.h"
#include "CEvent.h"

namespace socket_pra {

static int g_nSequence = 0;

template <class T> struct task_less;

/**
 * every task need extend this class,and implement run and timeout function
 */
class CTask
{
friend class CWorkThread;
friend class CTaskQueue;
friend struct task_less<CTask *>;
public:
	CTask(int nPriority = 0):m_nPriority(nPriority),m_threadId(0)
	{m_nSequence = 0;};

	CTask():m_nPriority(0),m_threadId(0){m_nSequence = 0;};

	virtual ~CTask(){};

	virtual void run() = 0;
	virtual void timeout(){};
	int get_priority() const
	{
		return m_nPriority;
	}

	void set_priority(int nPriority)
	{
		m_nPriority = nPriority;
	}

	pthread_t get_threadId() const
	{
		return m_threadId;
	}
private:
	int m_nPriority;
	int m_nSequence;

	pthread_t m_threadId;

	void set_threadId(pthread_t threadId)
	{
		m_threadId = threadId;
	}

	int get_sequence()
	{
		m_nSequence = g_nSequence++;
		return m_nSequence;
	}

};

typedef CTask * PTask;
/**
 * sort struct ,sort by priority asc,if priority is equal ,sort by sequence desc.
 */
template <class T>
struct task_less
{
	bool operator() (const T & t1,const T & t2) const
	{
		if(t1->get_priority() < t2->get_priority())
			return true;
		else if(t1->m_nSequence > t2->m_nSequence)
			return true;
		else
			return false;
	}
};

class CTaskQueue {

private:
	CMutex m_cMutex;
	CEvent m_cEvent;
	std::priority_queue<PTask,
						std::vector<PTask>,
						task_less<PTask>
						> m_cTaskQueue;

public:
	void wait_task()
	{
		m_cEvent.wait();
	}

	void notify_task()
	{
		m_cEvent.notify();
	}

	PTask pop_task()
	{
		PTask pTask;
		CAutoMutex cMutex(&m_cMutex);
		cMutex.lock();
		if(!m_cTaskQueue.empty())
		{
			pTask = dynamic_cast<PTask>(m_cTaskQueue.top());
			m_cTaskQueue.pop();
		}
		else
			pTask = 0;
		cMutex.unlock();
		return pTask;
	}

	void push_task(PTask pTask)
	{
		CAutoMutex cMutex(&m_cMutex);
		cMutex.lock();
		pTask->get_sequence();
		m_cTaskQueue.push(pTask);
		cMutex.unlock();
//		log_info("CTaskQueue  push_task notify_task");
		notify_task();
	}

	int size()
	{
		return m_cTaskQueue.size();
	}

	bool empty()
	{
		CAutoMutex cMutex(&m_cMutex);
		cMutex.lock();
		bool bEmpty = m_cTaskQueue.empty();
		cMutex.unlock();
		return bEmpty;
	}
};

} /* namespace socket */

#endif /* CTASKQUEUE_H_ */
