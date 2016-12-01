/*
 * CThread.cpp
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#include "CThread.h"

namespace socket_pra {

extern "C" void * thread_func(void * arg)
{
	CThread * pThread = (CThread *)arg;
	try
	{
		if(pThread->is_createSuppended())
			pThread->wait();

		pThread->execute();
	}
	catch(std::exception & e)
	{
	}
	catch(...)
	{
	}

	pThread->finish();
	return 0;
}

void CRunable::wait()
{
	if(m_pThread)
		m_pThread->wait();
}

void CRunable::wait(int nSecs)
{
	if(m_pThread)
		m_pThread->wait(nSecs);
}

void CRunable::terminate()
{
	if(m_pThread)
		m_pThread->terminate();
}

CThread::CThread(CRunable* pRunable) {

	m_pRunable = pRunable;
	m_pRunable->set_owner(this);
	m_threadId = 0;
	m_etsStatus = etsThreadInitial;

	m_bCreateSuspended = false;
	m_bInitialSuspendDone = false;
	m_bTerminated = false;

}

CThread::~CThread() {
	if( m_threadId != 0 &&m_etsStatus != etsThreadRunning )
	{
		terminate();

		if(m_etsStatus == etsThreadSuspended)
		{
			resume();
		}
		if(m_etsStatus == etsThreadTimeWaiting ||
				m_etsStatus == etsThreadWaiting)
		{
			m_cEvent.notify();
		}

		join();
	}

	if(m_threadId != 0)
		pthread_detach(m_threadId);
}

void CThread::execute()
{
	if(m_pRunable)
		m_pRunable->run();
}

void CThread::start(bool bCreateSuspended)
{
	m_bCreateSuspended = bCreateSuspended;

	int iRet = pthread_create(&m_threadId,0,thread_func,this);

	if(iRet != 0)
	{
		log_error(iRet,"create thread fail ...");
		return;
	}

	m_etsStatus = bCreateSuspended ? etsThreadSuspended : etsThreadRunning;
}

void CThread::join()
{
	int iRet = pthread_join(m_threadId,0);
	if(iRet != 0)
	{
		log_error(iRet,"join thread fail ...");
		return;
	}
	m_threadId = 0;
}

void CThread::resume()
{
	if(m_bCreateSuspended && !m_bInitialSuspendDone)
	{
		m_cEvent.notify();
		m_bInitialSuspendDone = true;
		m_etsStatus = etsThreadRunning;
	}

	if(m_etsStatus == etsThreadSuspended)
		return;

	int iRet = pthread_kill(m_threadId,SIGCONT);

	if(iRet != 0)
	{
		log_error(iRet," kill thread fail ...");
		return;
	}

	m_etsStatus = etsThreadRunning;
}

void CThread::suspend()
{
	if(m_etsStatus == etsThreadSuspended)
		return;
	int iRet = pthread_kill(m_threadId,SIGCONT);

	if(iRet != 0)
	{
		log_error(iRet," kill thread fail ...");
		return;
	}

	m_etsStatus = etsThreadSuspended;

}

void CThread::wait()
{
	m_etsStatus = etsThreadWaiting;
	m_cEvent.wait();
	m_etsStatus == etsThreadRunning;
}

int CThread::wait(int nSecs)
{
	int iRet;
	if(nSecs == 0)
		return 0;
	m_etsStatus = etsThreadTimeWaiting;
	iRet = m_cEvent.wait(nSecs);
	m_etsStatus = etsThreadRunning;

	return iRet;
}

void CThread::notify(CThread * pThread)
{
	pThread->m_cEvent.notify();
}

EPriority CThread::get_priority()
{
	int nP;
	sched_param spJ;
	pthread_getschedparam(m_threadId,&nP,&spJ);
	return static_cast<EPriority>(spJ.sched_priority);
}

void CThread::set_priority(EPriority ePriority)
{
	sched_param sp;
	int nP;
	pthread_getschedparam(m_threadId,&nP, &sp);

	if(ePriority != get_priority())
	{
		sp.sched_priority = ePriority;
		pthread_setschedparam(m_threadId,nP,&sp);
	}
}

} /* namespace socket */
