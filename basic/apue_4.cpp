#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 5

static void sig_int(int); /* our signal-catching function */

int main(void)
{
    char  buf[MAXLINE]; /* from apue.h */
    pid_t  pid;
    int  status;

    if(signal(SIGINT, sig_int) == SIG_ERR)
    {
        printf("signal error");
        exit(-1);    
    }

    printf("%% "); /* print prompt (printf requires %% to print %) */

    while (fgets(buf, MAXLINE, stdin) != NULL) 
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; /* replace newline with null */
        if ((pid = fork()) < 0) 
        {
            printf("fork error");
            exit(-1);
        }
        else if (pid == 0) 
        { /* child */
            execlp(buf, buf, (char *)0);
            printf("couldn't execute: %s", buf);
            exit(127);
        }
        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            printf("waitpid error");
            exit(-1);
        }
        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("interrupt\n%% ");
}