#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
//  open a file in $HOME/ named netstat.txt
//  read from mengpltest.txt 

// int open (const char *name, int flags, mode_t mode);
// flags : O_RDONLY(read only) O_WRONLY(write only) O_RDWR(read and write)

#define LOG_INTO(s) std::cout << s << std::endl
#define FAIL -1
#define OK    0

int main(int argc,char * argv[])
{
    LOG_INTO(" ============begin ===============");
    int fd;
    fd = open("/home/mengpl/1.txt", O_RDONLY);
    if (fd == -1)
    {
        /* error */
        LOG_INTO(" this is error ");
        return FAIL;
    }

    // unsigned long word;
    // ssize_t nr;
    // /* read a couple bytes into ’word’ from ’fd’ */
    // nr = read (fd, &word, sizeof (unsigned long));
    // if (nr == -1)
    // {
    //     /* error */
    //     LOG_INTO(" this error")
    //     return FAIL;
    // }
    int buf;
    int len = sizeof(int);

    ssize_t ret;
    while (len != 0 && (ret = read (fd, &buf, len)) != 0) 
    {
        if (ret == -1) 
        {
            if (errno == EINTR)
            continue;
            perror("read");
            break;
        }
        len -= ret;
        buf += ret;
        LOG_INTO(buf);

    }
    LOG_INTO(buf);
    return OK;
}
