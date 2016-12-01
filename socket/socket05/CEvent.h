/*
 * CEvent.h
 *
 *  Created on: 2014年10月28日
 *      Author: mengpl
 */

#ifndef CEVENT_H_
#define CEVENT_H_

#include <errno.h>
#include <assert.h>
#include "socket_define.h"
#include "CMutex.h"


namespace socket_pra {

class CEvent {

public:
	enum EventType
	{
		EVENT_SINGLE = 1,  //
		EVENT_BORADCAST = 2
	};

public:
	explicit CEvent(EventType eventType = EVENT_SINGLE);
	virtual ~CEvent();

	void reset();
	void wait();
	int wait(unsigned long sec);
	void notify();

private:
	EventType m_eType;

	pthread_cond_t m_cond;
	pthread_cond_t m_notifyCond;
	CMutex m_cMutex;
	unsigned long m_nNotifyCount;

};

} /* namespace socket_pra */

#endif /* CEVENT_H_ */
