#ifndef __SIGNAL_TEST_H__
#define __SIGNAL_TEST_H__
#include <signal.h>
#include <stdio.h>

static void sig_usr(int signo)
{
    if(SIGUSR1 == signo)
        printf("receive SIGUSR1 \n");
    else if(SIGUSR2 == signo)
        printf("receive SIGUSR2 \n");
    else
        printf("receive signal %d\n",signo);
}

extern "C" void sig_term(int iSigNo)
{
    if(SIGTERM == signo)
        printf("receive SIGTERM \n");
}

void test_signal();




#endif // !__SIGNAL_TEST_H__