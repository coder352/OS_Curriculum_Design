// 高级管道程序  pipe 升级版
// USE:
// :!./JD.out
// read pipe...
//
// The file list is:
// total 64
// drwxr-xr-x 2 coder352 coder352 4096 6月  28 12:42 1_fork
// drwxr-xr-x 2 coder352 coder352 4096 6月  28 09:52 2_signal
// drwxr-xr-x 2 coder352 coder352 4096 6月  28 09:52 3_pipe
// drwxr-xr-x 2 coder352 coder352 4096 6月  28 09:52 4_popen
// drwxr-xr-x 2 coder352 coder352 4096 6月  28 09:52 5_fifo
// -rwxr-xr-x 1 coder352 coder352  513 6月  28 12:50 fifo1.c
// -rwxr-xr-x 1 coder352 coder352  960 6月  28 12:50 fifo2.c
// -rwxr-xr-x 1 coder352 coder352 2046 6月  28 13:15 fork.c
// -rwxrwxr-x 1 coder352
//
// write into binary file...
//
//  read binary file.
//
//   write into pipe...
//   drwxr-xr-x 2 coder352 coder352 4096 6月  28 09:52 4_popen
//   -rwxr-xr-x 1 coder352 coder352 1573 6月  28 14:30 popen.c
#include <stdio.h>
#include <string.h>
int main()
{
    FILE *fp;
    char buf[501];
    int ch;

    /*step1:将ls命令内容通过读管道写入buf*/
    memset(buf, '\0', sizeof(buf));	//buf初始化 为 全0
    printf("read pipe...\n");
    /*//创建一个fp，使用命令ls -l，使用读管道*/
    fp = popen("ls -l", "r");
    // popen()：建立一个管道。
    // popen() 如果函数运行成功，则返回文件指针；如果发生错误，返回NULL
    // extern FILE *popen (__const char *__command, __const char *__modes) __THROW;
    // popen() 其中command表示执行的进程名称；而modes表示为r或者w，两者不能同时使用。如果为r，表示为读取管道；如果为w表示为写入管道
    if(fp != NULL)
    {
        /*将fp内容写入buf*/
        ch = fread(buf, sizeof(char), 500, fp);
        if(ch > 0)
        {
            printf("\nThe file list is: \n");
            printf("%s\n",buf);	//显示buf内容
        }
        pclose(fp);
    }
    else
    {
        printf("cann't execut popen.\n");
        return 1;
    }

    /*step2:将buf内容写入popen_test.bin*/
    printf("\nwrite into binary file...\n");
    /*创建文件popen_test.bin，权限二进制可写*/
    fp = fopen("popen_test.bin","wb");
    if(fp == NULL)
    {
        printf("cann't open file.\n");
        return 1;
    }
    /*将buf内容写入popen_test.bin*/
    fwrite(buf, sizeof(char), 500, fp);
    fclose(fp);

    /*step3:将popen_test.bin内容读出，写入buf*/
    printf("\n read binary file.\n");
    memset(buf, '\0', sizeof(buf));	//buf初始化
    //打开popen_test.bin，权限二进制只读
    fp = fopen("popen_test.bin", "rb");
    if(fp == NULL)
    {
        printf("cann't open file.\n");
        return 1;
    }
    /*将fp内容读入buf*/
    fread(buf, sizeof(char), 500, fp);
    fclose(fp);

    /*将buf内容通过写入写管道显示*/
    printf("\n write into pipe...\n");
    /*创建写管道*/
    fp = popen("ls -l|grep popen","w");
    // ls -l | grep 的回显什么时候出来的, 不太明白
    /*将buf写入管道，使用grep命令显示popen相关信息*/
    fwrite(buf, sizeof(char), 500, fp);
    /*printf("%s", buf);*/
    pclose(fp);
    return 0;
}

