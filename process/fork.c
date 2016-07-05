// USE:
// Do you want to create a new child process?(1:yes,2:no)1
// This is child process...
// child process pid = 30667
// child process ppid = 30666
// This is parent process...
// parent process pid = 30666
// parent process ppid = 29027
// child process leaving status: 1
//
// Do you want to create a new child process?(1:yes,2:no)2
// This is parent process...
// parent process pid = 30687
// parent process ppid = 29027
// child process leaving status: 1
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
int main()
{
    pid_t child; // typedef int pid_t
    int status, a;	//status表示子进程状态，a表示是否创建子进程
    printf("Do you want to create a new child process?(1:yes,2:no)");
    scanf("%d",&a);
    if(a == 1)
    {
        child = fork();	//创建child进程
// fork() 该函数用来产生新的子进程，而调用fork函数的进程则称为父进程。子进程会复制父进程的数据，并且继承父进程的各种参数，但是由于子进程和父进程并不使用相同的内存空间，所以并不同步。
// fork() 如果创建成功，则在父进程中会返回新建立的子进程代码（PID），子进程中成功返回0，失败则返回-1
        if(child == -1)	//创建失败
        {
            perror("fork error");
            exit(1);
        }
    }
    if(child == 0)	//创建成功
    {
        puts("This is child process...");
        printf("child process pid = %d\n", getpid());	//显示子进程PID
        printf("child process ppid = %d\n", getppid());	//显示父进程PID
        exit(0);
    }
    else	//父进程
    {
        waitpid(child, &status, 0);	//等待child进程结束
        puts("This is parent process...");
        printf("parent process pid = %d\n", getpid());	//显示子进程PID
        printf("parent process ppid = %d\n", getppid());	//显示父进程PID
        printf("child process leaving status: %d\n", WIFEXITED(status));
        exit(0);
    }
}
