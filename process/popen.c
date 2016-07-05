// �߼��ܵ�����  pipe ������
// USE:
// :!./JD.out
// read pipe...
//
// The file list is:
// total 64
// drwxr-xr-x 2 coder352 coder352 4096 6��  28 12:42 1_fork
// drwxr-xr-x 2 coder352 coder352 4096 6��  28 09:52 2_signal
// drwxr-xr-x 2 coder352 coder352 4096 6��  28 09:52 3_pipe
// drwxr-xr-x 2 coder352 coder352 4096 6��  28 09:52 4_popen
// drwxr-xr-x 2 coder352 coder352 4096 6��  28 09:52 5_fifo
// -rwxr-xr-x 1 coder352 coder352  513 6��  28 12:50 fifo1.c
// -rwxr-xr-x 1 coder352 coder352  960 6��  28 12:50 fifo2.c
// -rwxr-xr-x 1 coder352 coder352 2046 6��  28 13:15 fork.c
// -rwxrwxr-x 1 coder352
//
// write into binary file...
//
//  read binary file.
//
//   write into pipe...
//   drwxr-xr-x 2 coder352 coder352 4096 6��  28 09:52 4_popen
//   -rwxr-xr-x 1 coder352 coder352 1573 6��  28 14:30 popen.c
#include <stdio.h>
#include <string.h>
int main()
{
    FILE *fp;
    char buf[501];
    int ch;

    /*step1:��ls��������ͨ�����ܵ�д��buf*/
    memset(buf, '\0', sizeof(buf));	//buf��ʼ�� Ϊ ȫ0
    printf("read pipe...\n");
    /*//����һ��fp��ʹ������ls -l��ʹ�ö��ܵ�*/
    fp = popen("ls -l", "r");
    // popen()������һ���ܵ���
    // popen() ����������гɹ����򷵻��ļ�ָ�룻����������󣬷���NULL
    // extern FILE *popen (__const char *__command, __const char *__modes) __THROW;
    // popen() ����command��ʾִ�еĽ������ƣ���modes��ʾΪr����w�����߲���ͬʱʹ�á����Ϊr����ʾΪ��ȡ�ܵ������Ϊw��ʾΪд��ܵ�
    if(fp != NULL)
    {
        /*��fp����д��buf*/
        ch = fread(buf, sizeof(char), 500, fp);
        if(ch > 0)
        {
            printf("\nThe file list is: \n");
            printf("%s\n",buf);	//��ʾbuf����
        }
        pclose(fp);
    }
    else
    {
        printf("cann't execut popen.\n");
        return 1;
    }

    /*step2:��buf����д��popen_test.bin*/
    printf("\nwrite into binary file...\n");
    /*�����ļ�popen_test.bin��Ȩ�޶����ƿ�д*/
    fp = fopen("popen_test.bin","wb");
    if(fp == NULL)
    {
        printf("cann't open file.\n");
        return 1;
    }
    /*��buf����д��popen_test.bin*/
    fwrite(buf, sizeof(char), 500, fp);
    fclose(fp);

    /*step3:��popen_test.bin���ݶ�����д��buf*/
    printf("\n read binary file.\n");
    memset(buf, '\0', sizeof(buf));	//buf��ʼ��
    //��popen_test.bin��Ȩ�޶�����ֻ��
    fp = fopen("popen_test.bin", "rb");
    if(fp == NULL)
    {
        printf("cann't open file.\n");
        return 1;
    }
    /*��fp���ݶ���buf*/
    fread(buf, sizeof(char), 500, fp);
    fclose(fp);

    /*��buf����ͨ��д��д�ܵ���ʾ*/
    printf("\n write into pipe...\n");
    /*����д�ܵ�*/
    fp = popen("ls -l|grep popen","w");
    // ls -l | grep �Ļ���ʲôʱ�������, ��̫����
    /*��bufд��ܵ���ʹ��grep������ʾpopen�����Ϣ*/
    fwrite(buf, sizeof(char), 500, fp);
    /*printf("%s", buf);*/
    pclose(fp);
    return 0;
}

