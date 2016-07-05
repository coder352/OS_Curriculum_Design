//USE:
//:!./JD.out
//fifo2 executing...
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

int main()
{
    int fd, len;
    char buf[PIPE_BUF];
    time_t tp;
    //权限为666
    mode_t mode = 0666;
    /*删除fifo_test文件*/
    unlink("fifo_test");
    /*建立fifo_test的FIFO文件*/
// FIFO即有名管道。它可以在不相关的进程之间进行通信。因为它是通过系统中的文件进行通信，
// 其他的进程只要知道FIFO文件名称，即可加入通信；另外FIFO可以同时具有多个读取端和写入端，
// 多个进程可以同时写入同一个FIFO文件，多个进程也可以同时读取同一个FIFO文件
// FIFO即有名管道。它可以在不相关的进程之间进行通信。因为它是通过系统中的文件进行通信，其他的进程只要知道FIFO文件名称，即可加入通信；另外FIFO可以同时具有多个读取端和写入端，多个进程可以同时写入同一个FIFO文件，多个进程也可以同时读取同一个FIFO文件
// mkfifo建立一个名为path的FIFO文件，该文件必须不存在。权限模式则由mode决定，权限为mode值。mkfifo()如果成功运行则返回0，否则返回-1
    if((mkfifo("fifo_test", mode)) < 0)
    {
        perror("mkfifo error");
        exit(1);
    }
    printf("fifo2 executing...\n");
    /*打开fifo_test文件*/
    fd = open("fifo_test", O_WRONLY);
    if(fd < 0)
    {
        perror("open error");
        exit(1);
    }
    /*while(1)*/
    int i;
    for(i = 0; i <= 100; i++)
    {
        /*读出当前时间*/
        time(&tp); // time_t tp;
        len = sprintf(buf, "fifo2 return current time is: %s", ctime(&tp));
        /*将当前时间写入到FIFO文件之中*/
        if((write(fd, buf, len + 1)) < 0)
        {
            perror("write error");
            close(fd);
            exit(1);
        }
    }
    /*close(fd);*/
    exit(0);
}
