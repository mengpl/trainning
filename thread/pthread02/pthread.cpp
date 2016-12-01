//============================================================================
// Name        : pthread.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "pthread.h"

pthread_mutex_t mutex;
pthread_cond_t cond;

void hander(void *arg)
{
    free(arg);
    (void)pthread_mutex_unlock(&mutex);
}

void *thread1(void *arg)
{
     pthread_cleanup_push(hander, &mutex);
     while(1)
     {
         log_info("thread1 is runningn");
         pthread_mutex_lock(&mutex);
         pthread_cond_wait(&cond,&mutex);
         log_info("thread1 applied the conditionn");
         pthread_mutex_unlock(&mutex);
         sleep(4);
     }

     pthread_cleanup_pop(0);
     return NULL;
};

void *thread2(void *arg)
{
    while(1)
    {
        log_info("thread2 is runningn");
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        log_info("thread2 applied the conditionn");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
};

int main()
{
     pthread_t thid1,thid2;

     log_info("condition variable study!n");

     pthread_mutex_init(&mutex,NULL);

     pthread_cond_init(&cond,NULL);

     pthread_create(&thid1,NULL,thread1,NULL);

     pthread_create(&thid2,NULL,thread2,NULL);

     sleep(1);

     do
     {
         pthread_cond_signal(&cond);
     }while(1);

     sleep(20);

     pthread_exit(0);

     return 0;

}
