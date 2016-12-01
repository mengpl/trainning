/*
 * CEvent.cpp
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#include "CEvent.h"

namespace socket_pra {

CEvent::CEvent(EventType eventType)
{
	m_nNotifyCount = 0;
	m_eType = eventType;

	int iRet = pthread_cond_init(&m_cond,0);
	if(iRet != 0)
	{
		log_error(iRet,"m_cond init fail");
		return;
	}
	iRet = pthread_cond_init(&m_notifyCond,0);
	if(iRet != 0)
	{
		log_error(iRet,"m_notifyCond init fail");
		return;
	}
}

void CEvent::reset(void)
{
	m_cMutex.lock();
	m_nNotifyCount = 0;  //重置时，应把m_nNoitifyCount清0
	m_cMutex.unlock();
}

void CEvent::wait(void)
{
	int iRet = 0;
	CAutoMutex cMutex(&m_cMutex);
//	log_info("wait m_nNotifyCount = %lu",m_nNotifyCount);
	while(m_nNotifyCount <= 0)
	{
		iRet = pthread_cond_wait(&m_cond,m_cMutex.get_realMutex());
		if(iRet != 0)
		{
			log_error(iRet,"m_cond wait fail!");
			return;
		}
	}

	m_nNotifyCount--;
	iRet = pthread_cond_signal(&m_notifyCond);
	if(iRet != 0)
	{
		log_error(iRet,"m_notifyCond signal fail!");
		return;
	}
}

int CEvent::wait(unsigned long nSecs)
{
	int iRet = 0;
	struct timespec ts;
	ts.tv_sec = time(0) + nSecs;
	ts.tv_nsec = 0;

	CAutoMutex cMutex(&m_cMutex);

	if(m_nNotifyCount <= 0)
	{
		iRet = pthread_cond_timedwait(&m_cond,m_cMutex.get_realMutex(),&ts);
		return iRet;
	}

	if(iRet != 0 && iRet != ETIMEDOUT)
	{
		log_error(iRet," pthread_cond_timedwait fail");
		return iRet;
	}

	if(m_nNotifyCount > 0)
	{
		m_nNotifyCount--;
		iRet = pthread_cond_signal(&m_notifyCond);
		return iRet;
	}

	return iRet;
}

void CEvent::notify(void)
{
	int iRet = 0;
	CAutoMutex cMutex(&m_cMutex);
	while(m_nNotifyCount > 0)
	{
		iRet = pthread_cond_wait(&m_notifyCond,m_cMutex.get_realMutex());
		if(iRet != 0)
		{
			log_error(iRet,"m_cond wait fail!");
			return;
		}
	}

	m_nNotifyCount++;
	switch(m_eType)
	{

	case EVENT_SINGLE:
		iRet = pthread_cond_signal(&m_cond);
		break;
	case EVENT_BORADCAST:
		iRet = pthread_cond_broadcast(&m_cond);
		break;
	default:
		assert(0);
	}

	if(iRet != 0)
	{
		log_error(iRet,"m_cond notify fail!");
		return;
	}
}

CEvent::~CEvent() {
	int iRet = 0;
	while((iRet = pthread_cond_destroy(&m_cond)) == EBUSY)
	{
		notify();
	}

	if(iRet != 0)
	{
		fprintf(stderr, "CEvent: CEvent being destroyed is BUSY\n");
		return;
	}
}

} /* namespace socket_par */
