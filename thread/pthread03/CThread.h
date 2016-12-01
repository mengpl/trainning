/*
 * CThread.h
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#ifndef CTHREAD_H_
#define CTHREAD_H_

#include "CEvent.h"
#include <signal.h>
#include <exception>

namespace socket_pra {

enum EThreadStatus
{
    etsThreadSuspended   = 0,  //挂起
    etsThreadRunning     = 1,  //运行
    etsThreadWaiting     = 2,  //等待
    etsThreadTimeWaiting = 3,  //限时等待
    etsThreadInitial     = 4,  //初始化
    etsThreadCreated     = 5,  //创建
    etsThreadFinished    = 6   //结束
};

enum EPriority
{
    tpLow,
    tpMedium = tpLow + 1,
    tpHigh   = tpLow + 2

} ;
class CThread;
class CRunable {

friend class CThread;
public:
	CRunable():m_pThread(0){};
	virtual ~CRunable(){};

	void wait();
	void wait(int nSecs);
	void terminate();
	CThread * get_thread(void) const
	{
		return m_pThread;
	}
public:
	virtual void run() = 0;
private:
	CThread * m_pThread;

	void set_owner(CThread* pThread)
	{
		m_pThread = pThread;
	}
};

extern "C" void * thread_func(void * arg);

class CThread {

friend void * thread_func(void * arg);

public:
	explicit CThread(CRunable * pRunable);
	virtual ~CThread();

protected:
	EThreadStatus m_etsStatus;

private:
	pthread_t m_threadId;
	CRunable * m_pRunable;
	CEvent m_cEvent;

	bool m_bCreateSuspended;
	bool m_bInitialSuspendDone;
	bool m_bTerminated;

	void finish(void)
	{
		m_etsStatus = etsThreadFinished;
	}

public:
	inline pthread_t get_threadId() const
	{
		return m_threadId;
	}

	EThreadStatus get_threadState() const
	{
		return m_etsStatus;
	}

	bool is_createSuppended() const
	{
		return m_bCreateSuspended;
	}

	bool is_terminated() const
	{
		return m_bTerminated;
	}

	EPriority get_priority();
	void set_priority(EPriority ePriority);

public:
	void execute(void);
	void start(bool bCreateSuspended = false);
	void terminate()
	{
		m_bTerminated = true;
	}

	void join();
	void resume();
	void suspend();
	void wait();
	int wait(int nSecs);
	static void notify(CThread * pThread);
	void boardcast(CThread * pThread);
};

} /* namespace socket */

#endif /* CTHREAD_H_ */
