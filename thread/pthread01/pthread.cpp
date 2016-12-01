//============================================================================
// Name        : pthread.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "pthread.h"
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long long tmp;

extern "C" void* thread_mutex(void *arg)
{
	log_info("thread id is %lld...",(long long)pthread_self());

    pthread_mutex_lock(&mutex);
    sleep(5);
    tmp = (long long)pthread_self();
    log_info("Now a is %lld ...",tmp);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

extern "C" void* thread(void *arg)
{
	log_info("thread id is %lld...",(long long)pthread_self());

//	pthread_mutex_lock(&mutex);
	tmp = (long long)pthread_self();
	log_info("Now a is %lld ...",tmp);
//	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main()
{

	struct tm now;
	struct timespec pTimeSpec;
	clock_gettime(CLOCK_REALTIME, &pTimeSpec);
	localtime_r(&pTimeSpec.tv_sec, &now);
	fprintf(stdout,"%04d-%02d-%02d %02d:%02d:%02d:%06ld",
			now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
			now.tm_hour, now.tm_min, now.tm_sec, pTimeSpec.tv_nsec/1000);

    pthread_t id;
    pthread_t id2;
    log_info("main thread id is %lld ...",(long long)pthread_self());
    tmp = 3;
    log_info("In main func tmp = %lld", tmp);

    if (!pthread_create(&id, NULL, thread_mutex, NULL))
    {
    	log_info("Create thread id success!");
    }
    else
    {
        log_error(-1,"Create thread failed!");
    }

    if (!pthread_create(&id2, NULL, thread, NULL))
	{
		log_info("Create thread id2 success!");
	}
	else
	{
		log_error(-1,"Create thread failed!");
	}

    pthread_join(id, NULL);
    pthread_join(id2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;

}
