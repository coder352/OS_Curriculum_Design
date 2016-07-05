// USE:
// 先执行 fifo2.c, 后执行 fifo1.c
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// fifo2 return current time is: Tue Jun 28 14:59:34 2016
// 会一直这样下去
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
int main(void)
{
    int fd;
    int len;
    char buf[PIPE_BUF];
    /*打开fifo_test文件，权限只读*/
    fd = open("fifo_test",O_RDONLY);
    if(fd < 0)
    {
        perror("open error");
        exit(1);
    }
    /*读文件fifo_test，并保存到buf*/
    while((len = read(fd, buf, PIPE_BUF-1)) > 0)
        printf("%s",buf);	//显示buf内容
    close(fd);
    exit(0);
}

