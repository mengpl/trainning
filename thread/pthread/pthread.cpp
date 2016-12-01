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


extern "C" void* thread_func(void * agrc)
{
	fprintf(stdout," this is a thread\n");
	sleep(5);
	return NULL;
}

int main(void) {

	fprintf(stdout," begin ...\n");

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t llThreadId;

	fprintf(stdout," begin create thread ...\n");
	pthread_create(&llThreadId,&attr,thread_func,NULL);
	fprintf(stdout," create thread end ...\n");

	fprintf(stdout," begin join thread ...\n");
	pthread_join(llThreadId,NULL);
	fprintf(stdout," join thread end...\n");

	return 0;
}


