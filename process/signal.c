// USE: <F9>
// wait alarm signal for 3 seconds....
// This is alarm message.
// Wait for 3 seconds.
// System receive alarm signal
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static int flag = 0;

void alarmessage(int sig)
{
    printf("This is alarm message.\n\r");
    printf("Wait for 3 seconds.\n\r");
    sleep(3);
    flag = 1;
}

int main()
{
    pid_t pid;	//定义新进程 // typedef int pid_t
    pid = fork();	//创建新进程pid
    // fork() 这里是亮点
    // fork() 该函数用来产生新的子进程，而调用fork函数的进程则称为父进程。子进程会复制父进程的数据，并且继承父进程的各种参数，但是由于子进程和父进程并不使用相同的内存空间，所以并不同步
    // fork() 后, 父进程的得到的 pid 为子进程的 id, 子进程得到的 pid 为 0(成功) 或 -1(失败)
    switch(pid)
    { // 只有 子进程 会执行这里的代码
        case -1:
            perror("fork error");
            exit(1);
        case 0:  	//进程创建成功，等待3秒
            // alarm()：用来设置SIGALRM信号在经过参数指定的秒数之后，传送给当前的进程
            // 不知道为什么这里用的是 sleep
            sleep(3);//给父进程传送指定的SIGALRM信号
            kill(getppid(), SIGALRM); // 定时器计时完成信号
            // kill(pid, sig) 用来传送sig参数所指定的信号给pid参数所指定的进程
            exit(0);
    }
    printf("wait alarm signal for 3 seconds....\n");//发送SIGALRM信号，即转移到指定函数alarmessage
// void (*signal (int sig, void (*func)(int)))(int);
// 函数会根据sig指定的信号进行处理。当相关信号到达之后，就会自动调转到func指定的函数中运行。运行结束后会返回到信号处理函数的函数指针，如果有错误发生，则返回-1
    (void) signal(SIGALRM, alarmessage);//发送信号之后，该进程暂停，直到收到flag信号
    pause(); // 没有这句话,父进程 不会等待 子进程的 信号, singal 必须和 pause 配合使用
// pause()：该函数会让当前的进程暂停，直到接收到信号之后才会继续运行。该函数运行之后，只能返回-1
    if(flag)
        printf("System receive alarm signal\n");
    exit(0);
}
