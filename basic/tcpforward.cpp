#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


static int forward_port;

#undef max
#define max(x,y) ((x) > (y) ? (x) : (y))

/*************************关于本文档************************************
*filename: tcpforwardport.c
*purpose: 演示了select的用法，这是一个极好的代理软件核心，专门作端口映射用
*tidied by: zhoulifa(zhoulifa@163.com) 周立发(http://zhoulifa.bokee.com)
Linux爱好者 Linux知识传播者 SOHO族 开发者 最擅长C语言
*date time:2006-07-05 19:00:00
*Note: 任何人可以任意复制代码并运用这些文档，当然包括你的商业用途
* 但请遵循GPL
*Thanks to: Paul Sheer 感谢Paul Sheer在select_tut的man手册里提供了这份源代码
*Hope:希望越来越多的人贡献自己的力量，为科学技术发展出力
*********************************************************************/

static int listen_socket (int listen_port) 
{
    struct sockaddr_in a;
    int s;
    int yes;
    if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("socket");
        return -1;
    }
    yes = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &yes, sizeof (yes)) <0) 
    {
        perror ("setsockopt");
        close (s);
        return -1;
    }
    memset (&a, 0, sizeof (a));
    a.sin_port = htons (listen_port);
    a.sin_family = AF_INET;
    if (bind(s, (struct sockaddr *) &a, sizeof (a)) < 0) 
    {
        perror ("bind");
        close (s);
        return -1;
    }
    printf ("accepting connections on port %d\n", (int) listen_port);
    listen (s, 10);
    return s;
}

static int connect_socket (int connect_port, char *address) 
{
    struct sockaddr_in a;
    int s;
    if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror ("socket");
        close (s);
        return -1;
    }

    memset (&a, 0, sizeof (a));
    a.sin_port = htons (connect_port);
    a.sin_family = AF_INET;

    if (!inet_aton(address, (struct in_addr *) &a.sin_addr.s_addr)) 
    {
        perror ("bad IP address format");
        close (s);
        return -1;
    }

    if (connect(s, (struct sockaddr *) &a, sizeof (a)) < 0) 
    {
        perror ("connect()");
        shutdown (s, SHUT_RDWR);
        close (s);
        return -1;
    }
    return s;
}

#define SHUT_FD1 { \
    if (fd1 >= 0) {   \
        shutdown (fd1, SHUT_RDWR);  \
        close (fd1);  \
        fd1 = -1;     \
    }   \
}

#define SHUT_FD2 { \
    if (fd2 >= 0) {   \
        shutdown (fd2, SHUT_RDWR);  \
        close (fd2);  \
        fd2 = -1;     \
    }   \
}

#define BUF_SIZE 1024

int main (int argc, char **argv) 
{
    int h;
    int fd1 = -1, fd2 = -1;
    char buf1[BUF_SIZE], buf2[BUF_SIZE];
    int buf1_avail, buf1_written;
    int buf2_avail, buf2_written;

    if (argc != 4) 
    {
        fprintf (stderr, "Usage\n\tfwd   \n");
        exit (1);
    }

    signal(SIGPIPE, SIG_IGN);

    forward_port = atoi (argv[2]);

    /*建立监听socket*/
    h = listen_socket (atoi (argv[1]));
    if (h < 0) 
        exit (1);

    while(1)
    {
        int r, nfds = 0;
        fd_set rd, wr, er;
        FD_ZERO (&rd);
        FD_ZERO (&wr);
        FD_ZERO (&er);
        FD_SET (h, &rd);

        /*把监听socket和可读socket三个一起放入select的可读句柄列表里*/
        nfds = max (nfds, h);
        if (fd1 > 0 && buf1_avail < BUF_SIZE) 
        {
            FD_SET (fd1, &rd);
            nfds = max (nfds, fd1);
        }
        if (fd2 > 0 && buf2_avail < BUF_SIZE) 
        {
            FD_SET (fd2, &rd);
            nfds = max (nfds, fd2);
        }

        /*把可写socket两个一起放入select的可写句柄列表里*/
        if (fd1 > 0 && buf2_avail - buf2_written > 0) 
        {
            FD_SET (fd1, &wr);
            nfds = max (nfds, fd1);
        }
        if (fd2 > 0 && buf1_avail - buf1_written > 0) 
        {
            FD_SET (fd2, &wr);
            nfds = max (nfds, fd2);
        }

        /*把有异常数据的socket两个一起放入select的异常句柄列表里*/
        if (fd1 > 0) 
        {
            FD_SET (fd1, &er);
            nfds = max (nfds, fd1);
        }
        if (fd2 > 0) 
        {
            FD_SET (fd2, &er);
            nfds = max (nfds, fd2);
        }

        /*开始select*/
        r = select (nfds + 1, &rd, &wr, &er, NULL);

        if (r == -1 && errno == EINTR) continue;
        if (r < 0) 
        {
            perror ("select()");
            exit (1);
        }

        /*处理新连接*/
        if (FD_ISSET (h, &rd)) 
        {
            unsigned int l;
            struct sockaddr_in client_address;
            memset (&client_address, 0, l = sizeof (client_address));
            r = accept (h, (struct sockaddr *)&client_address, &l);
            if (r < 0) 
            {
                perror ("accept()");
            } 
            else 
            {
                /*关闭原有连接，把新连接作为fd1，同时连接新的目标fd2*/
                SHUT_FD1;
                SHUT_FD2;
                buf1_avail = buf1_written = 0;
                buf2_avail = buf2_written = 0;
                fd1 = r;
                fd2 = connect_socket (forward_port, argv[3]);
                if (fd2 < 0) 
                {
                    SHUT_FD1;
                } else
                    printf ("connect from %s\n", inet_ntoa(client_address.sin_addr));
            }
        }

        /* NB: read oob data before normal reads */
        if (fd1 > 0)
        if (FD_ISSET (fd1, &er)) 
        {
            char c;
            errno = 0;
            r = recv (fd1, &c, 1, MSG_OOB);
            if (r < 1) 
            {
                SHUT_FD1;
            } else
                send (fd2, &c, 1, MSG_OOB);
        }

        if (fd2 > 0)
        if (FD_ISSET (fd2, &er)) 
        {
            char c;
            errno = 0;
            r = recv (fd2, &c, 1, MSG_OOB);
            if (r < 1) 
            {
                SHUT_FD1;
            } else
                send (fd1, &c, 1, MSG_OOB);
        }

        /* NB: read data from fd1 */
        if (fd1 > 0)
        if (FD_ISSET (fd1, &rd)) 
        {
            r = read (fd1, buf1 + buf1_avail, BUF_SIZE - buf1_avail);
            if (r < 1) 
            {
                SHUT_FD1;
            } else
                buf1_avail += r;
        }

        /* NB: read data from fd2 */
        if (fd2 > 0)
        if (FD_ISSET (fd2, &rd)) 
        {
            r = read (fd2, buf2 + buf2_avail, BUF_SIZE - buf2_avail);
            if (r < 1) 
            {
                SHUT_FD2;
            } else
                buf2_avail += r;
        }

        /* NB: write data to fd1 */
        if (fd1 > 0)
        if (FD_ISSET (fd1, &wr)) 
        {
            r = write (fd1, buf2 + buf2_written, buf2_avail - buf2_written);
            if (r < 1) 
            {
                SHUT_FD1;
            } else
                buf2_written += r;
        }

        /* NB: write data to fd1 */
        if (fd2 > 0)
        if (FD_ISSET (fd2, &wr)) 
        {
            r = write (fd2, buf1 + buf1_written, buf1_avail - buf1_written);
            if (r < 1) 
            {
                SHUT_FD2;
            } else
                buf1_written += r;
        }

        /* check if write data has caught read data */
        if (buf1_written == buf1_avail) buf1_written = buf1_avail = 0;
        if (buf2_written == buf2_avail) buf2_written = buf2_avail = 0;

        /* one side has closed the connection, keep writing to the other side until empty */
        if (fd1 < 0 && buf1_avail - buf1_written == 0) 
        {
            SHUT_FD2;
        }
        if (fd2 < 0 && buf2_avail - buf2_written == 0) 
        {
            SHUT_FD1;
        }
    }
    return 0;
}
