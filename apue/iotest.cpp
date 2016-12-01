#include "iotest.h"

void file_io_test()
{
    //1 open a file
    int fd = open("/mnt/d/work/source/git/practise/apue/Readme.txt",/*O_RDONLY*//*O_WRONLY*/O_RDWR,O_APPEND);

    // 定位到距离开始位置50的位置
    off_t pos_set = lseek(fd,50,SEEK_SET) ;

    // 定位到距离当前位置10的位置 实际上距离开始位置60
    off_t pos_cur = lseek(fd,10,SEEK_CUR) ;

    // 定位到距离结尾距离-50的位置 实际距离开始位置为13，文件总共大小63
    off_t pos_end = lseek(fd,-50,SEEK_END) ;

    // test read
    char buf[100];
    ssize_t size = read(fd,buf,100);

    printf("buf = %s\n",buf);
    printf("size = %d\n",(int)size);

    int fd1 = open("/mnt/d/work/source/git/practise/apue/1.txt",O_CREAT|O_EXCL|O_RDWR,S_IRWXU);//第二个参数要加上O_RDWR才能写入数据

    if(-1 == fd1)
    {
        printf("create file fail \n");
        return;
    }

    ssize_t size_write = write(fd1,buf,size);

    printf("fd1 = %d\n",fd1);

    int fd3 = dup(fd1);
    printf("fd3 = %d\n",fd3);

    int fd2 = open("/mnt/d/work/source/git/practise/apue/1.txt",O_CREAT|O_EXCL,S_IRWXU); // 如果文件已经存在，这里会创建失败
    
    if(-1 == fd2)
    {
        printf("create file fail \n");
        return;
    }

    printf("fd2 = %d\n",fd2);

    // test write
    // ssize_t size_write = write(fd,buf,size);
    printf("size_write = %d\n",(int)size_write);

    close(fd);
}
