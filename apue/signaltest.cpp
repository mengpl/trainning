#include "signaltest.h"

void test_case1()
{
    if (signal(SIGUSR1,sig_usr) == SIG_ERR)
    {
        printf("can not catch SIGUSR1");
    }
    if (signal(SIGUSR2,sig_usr) == SIG_ERR)
    {
        printf("can not catch SIGUSR2");
    }

    while(true)
    {
        pause(); // this function use to wait for signal
    }
}

int32 process_signal()
{
	int32 iRet = 0;
	sigset_t setSig;
	sigemptyset(&setSig);

	for (int32 i = 1; i < 32; ++i) {
		switch (i) {
			case SIGHUP:
			case SIGINT:
			case SIGQUIT:
			case SIGTERM:
				iRet = set_signal(i, sig_term);
				if (iRet != 0) {
					printf("set signal func err, sig %d, errno %d\n", i, errno);
					return iRet;
				}
				break;
			case SIGCHLD:
				iRet = set_signal(i, sig_child);
				if (iRet != 0) {
					printf("set signal func err, sig %d, errno %d\n", i, errno);
					return iRet;
				}
				break;
			case SIGPIPE:
			case SIGIO:
			case SIGURG:
			case SIGXCPU:
			case SIGXFSZ:
			case SIGALRM:
			case SIGVTALRM:
			case SIGPROF:
			case SIGUSR1:
			case SIGUSR2:
				iRet = set_signal(i, sig_unprocess);
				if (iRet != 0) {
					printf("set signal func err, sig %d, errno %d\n", i, errno);
					return iRet;
				}
				break;
			case SIGTSTP:
			case SIGCONT:
			case SIGTTIN:
			case SIGTTOU:
			case SIGBUS:
			case SIGSEGV:
			case SIGABRT:
			case SIGFPE:
			case SIGTRAP:
			case SIGILL:
			case SIGSYS:
			case SIGWINCH:
				iRet = set_signal(i, SIG_DFL);
				if (iRet != 0) {
					printf("set signal func err, sig %d, errno %d\n", i, errno);
					return iRet;
				}
				break;
			case SIGKILL:
			case SIGSTOP:
				break;
			default:
				set_signal(i, sig_unprocess);
		}
	}

	for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
		sigaddset(&setSig, i);
	}
	iRet = sigprocmask(SIG_BLOCK, &setSig, NULL);
	if (iRet != 0) {
		printf("block signal err, errno %d\n", errno);
		return iRet;
	}
	return iRet;
}

void test_signal()
{
    // test_case1();
    process_signal();
} 