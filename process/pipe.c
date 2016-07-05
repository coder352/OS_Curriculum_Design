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
    int fd[2]; //���������ļ�������
// �����̽���һ���ܵ�֮��ϵͳ�ͻ�Ϊ������̽���2���ļ�������fd[0]��fd[1]��
// fd[0]��������read������ fd[1]��������write����
    int fdin; //�ļ�ָ��
    char buf[PIPE_BUF];	//������
    // ��, ��֪����� PIPE_BUF �Ƕ���
    int pid, len;
// pipe() �ú�������֮���������ļ�������������fd[0]������ȡ��fd[1]����д�롣
// ���pipe()�������гɹ����򷵻�0������������󣬷���-1
// ����������һ�����̵��������һ�����̵��������һ�ֵ����ͨ�ŷ�ʽ
// ��������� �ӽ��� ��ȴ� ������
    if(pipe(fd) < 0) //����ܵ�
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
        close(fd[1]); //�����ӽ��̣��ر�д�ܵ�
        printf("Child process ");
        //��Ϣ��fd[0]�ж�����buf֮�У�����Ϊlen
        // fd[0] ��һ������ʽ pipe() �������ɵ�, ��ȴ� ������ write
        while((len = read(fd[0], buf, PIPE_BUF)) > 0)
        {
            buf[len] = '\0'; //���һ���ַ���ʶ��ֹ
            printf("read %d bytes...\n", len);
            printf("%s\n", buf); //��ʾ����������
        }
        close(fd[0]); //�رն��ܵ�
    }
    if(pid > 0) //������
    {
        close(fd[0]); //�رն��ܵ�
        printf("Parent start...\n");
        //ʹ��ֻ����ʽ���ļ�hello
        fdin = open("pipe_hello", O_RDONLY);
        if(fdin < 0)
        {
            perror("open hello file error\n");
            exit(1);
        }
        //��Ϣ���ļ�fdin����buf������Ϊlen
        while((len = read(fdin, buf, PIPE_BUF)) > 0)
            write(fd[1], buf, len); //��Ϣ��bufд��fd[1]��
        close(fdin);	//�ر��ļ�ָ��
        printf("Parent over...\n");
        close(fd[1]);	//�ر�д�ܵ�
    }
    waitpid(pid, NULL, 0);	//�ȴ��ӽ��̽���
//	waitpid(): �ú����ܹ���ͣ��ǰ���̵����У�ʹ��ȴ��ӽ���
//  waitpid(): ���ӽ����������֮�󣬵ȴ��еĸ����̽����������С�waitpid()�������гɹ�֮�󷵻��ӽ���PID�����ʧ���򷵻�-1
    exit(0);
}
