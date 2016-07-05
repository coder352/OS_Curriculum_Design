// USE:
// :!./JD.out
// Parent start...
// Parent over...
// Child process read 95 bytes...
// A:Hello, I'm glad to see you! How are you?
// B:Fine! Thank you. And you?
// A:Very well, thank you!
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

int main()
{
    int fd[2]; //定义两个文件描述符
// 当进程建立一个管道之后，系统就会为这个进程建立2个文件描述符fd[0]和fd[1]。
// fd[0]用来进行read操作， fd[1]用来进行write操作
    int fdin; //文件指针
    char buf[PIPE_BUF];	//缓冲区
    // 迷, 不知道这个 PIPE_BUF 是多少
    int pid, len;
// pipe() 该函数运行之后会打开两个文件描述符。其中fd[0]用来读取，fd[1]用来写入。
// 如果pipe()函数运行成功，则返回0；如果发生错误，返回-1
// 它用来连接一个进程的输入和另一个进程的输出，是一种单向的通信方式
// 所以下面的 子进程 会等待 父进程
    if(pipe(fd) < 0) //定义管道
    {
        perror("pipe error");
        exit(1);
    }
    pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    if(pid == 0)
    {
        close(fd[1]); //对于子进程，关闭写管道
        printf("Child process ");
        //信息从fd[0]中读出到buf之中，长度为len
        // fd[0] 是一个阻塞式 pipe() 函数生成的, 会等待 父进程 write
        while((len = read(fd[0], buf, PIPE_BUF)) > 0)
        {
            buf[len] = '\0'; //最后一个字符标识终止
            printf("read %d bytes...\n", len);
            printf("%s\n", buf); //显示缓冲区内容
        }
        close(fd[0]); //关闭读管道
    }
    if(pid > 0) //父进程
    {
        close(fd[0]); //关闭读管道
        printf("Parent start...\n");
        //使用只读方式打开文件hello
        fdin = open("pipe_hello", O_RDONLY);
        if(fdin < 0)
        {
            perror("open hello file error\n");
            exit(1);
        }
        //信息从文件fdin读入buf，长度为len
        while((len = read(fdin, buf, PIPE_BUF)) > 0)
            write(fd[1], buf, len); //信息从buf写入fd[1]中
        close(fdin);	//关闭文件指针
        printf("Parent over...\n");
        close(fd[1]);	//关闭写管道
    }
    waitpid(pid, NULL, 0);	//等待子进程结束
//	waitpid(): 该函数能够暂停当前进程的运行，使其等待子进程
//  waitpid(): 当子进程运行完毕之后，等待中的父进程将会重新运行。waitpid()函数运行成功之后返回子进程PID，如果失败则返回-1
    exit(0);
}
