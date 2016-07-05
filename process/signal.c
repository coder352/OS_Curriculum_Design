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
    pid_t pid;	//�����½��� // typedef int pid_t
    pid = fork();	//�����½���pid
    // fork() ����������
    // fork() �ú������������µ��ӽ��̣�������fork�����Ľ������Ϊ�����̡��ӽ��̻Ḵ�Ƹ����̵����ݣ����Ҽ̳и����̵ĸ��ֲ��������������ӽ��̺͸����̲���ʹ����ͬ���ڴ�ռ䣬���Բ���ͬ��
    // fork() ��, �����̵ĵõ��� pid Ϊ�ӽ��̵� id, �ӽ��̵õ��� pid Ϊ 0(�ɹ�) �� -1(ʧ��)
    switch(pid)
    { // ֻ�� �ӽ��� ��ִ������Ĵ���
        case -1:
            perror("fork error");
            exit(1);
        case 0:  	//���̴����ɹ����ȴ�3��
            // alarm()����������SIGALRM�ź��ھ�������ָ��������֮�󣬴��͸���ǰ�Ľ���
            // ��֪��Ϊʲô�����õ��� sleep
            sleep(3);//�������̴���ָ����SIGALRM�ź�
            kill(getppid(), SIGALRM); // ��ʱ����ʱ����ź�
            // kill(pid, sig) ��������sig������ָ�����źŸ�pid������ָ���Ľ���
            exit(0);
    }
    printf("wait alarm signal for 3 seconds....\n");//����SIGALRM�źţ���ת�Ƶ�ָ������alarmessage
// void (*signal (int sig, void (*func)(int)))(int);
// ���������sigָ�����źŽ��д���������źŵ���֮�󣬾ͻ��Զ���ת��funcָ���ĺ��������С����н�����᷵�ص��źŴ������ĺ���ָ�룬����д��������򷵻�-1
    (void) signal(SIGALRM, alarmessage);//�����ź�֮�󣬸ý�����ͣ��ֱ���յ�flag�ź�
    pause(); // û����仰,������ ����ȴ� �ӽ��̵� �ź�, singal ����� pause ���ʹ��
// pause()���ú������õ�ǰ�Ľ�����ͣ��ֱ�����յ��ź�֮��Ż�������С��ú�������֮��ֻ�ܷ���-1
    if(flag)
        printf("System receive alarm signal\n");
    exit(0);
}
