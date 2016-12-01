/*
 * CMutex.h
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#ifndef CMUTEX_H_
#define CMUTEX_H_

#include <pthread.h>
#include "thread_define.h"

namespace socket_pra {

class CMutex {
public:
	CMutex();
	virtual ~CMutex();

	void lock();
	bool try_lock();
	void unlock();

	pthread_mutex_t * get_realMutex();

private:
	pthread_mutex_t m_mutex;
};

class CAutoMutex
{
public:
	explicit CAutoMutex(CMutex * pMutex):m_bLocked(true),m_pMutex(pMutex)
	{
		m_pMutex->lock();
	};
	~CAutoMutex()
	{
		unlock();
	};

	void unlock()
	{
		if(m_bLocked)
		{
			m_pMutex->unlock();
		}
	}

	void lock()
	{
		if(!m_bLocked)
		{
			m_bLocked = true;
			m_pMutex->lock();
		}
	}

private:
	bool m_bLocked;
	CMutex * m_pMutex;
};

inline CMutex::CMutex()
{
	int iRet = pthread_mutex_init(&m_mutex,0);
	if(iRet != 0)
	{
		log_error(iRet,"can not initialize the mutex.");
	}
}

inline void CMutex::lock()
{
	int iRet = pthread_mutex_lock(&m_mutex);
	if(iRet != 0)
	{
		log_error(iRet,"can not lock the mutex.");
	}
}

inline bool CMutex::try_lock()
{
	int iRet = pthread_mutex_trylock(&m_mutex);
	if(iRet != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline void CMutex::unlock()
{
	int iRet = pthread_mutex_unlock(&m_mutex);
	if(iRet != 0)
	{
		log_error(iRet,"can not unlock the mutex.");
		return;
	}
}

inline CMutex::~CMutex()
{
	int iRet = pthread_mutex_destroy(&m_mutex);
}

inline pthread_mutex_t * CMutex::get_realMutex()
{
	return &m_mutex;
}

} /* namespace socket_pra */

#endif /* CMUTEX_H_ */
