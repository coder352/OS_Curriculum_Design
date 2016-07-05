# include <unistd.h>	//符号常量，包含了许多系统服务的函数原型
# include <sys/types.h>	//基本系统数据类型，包含各类系统定义的数据类型
# include <sys/wait.h>	//进程控制
# include <stdlib.h>	//标准程序库函数
# include <sys/stat.h>	//文件状态头文件
# include <fcntl.h>		//文件控制头文件
// 2．	打印提示符，并获取用户输入的指令
int BUFFERSIZE = 100;
char * path;
char lc_char;
char buffer[BUFFERSIZE];
char * input;
char *arg[BUFFERSIZE];
int main(){
while(1)
{
    path = get_current_dir_name();
    printf("%s>$", path); //返回值是一个指向当前目录绝对路径的字符串指
    /* 开始获取输入 */
    int count = 0;
    for(count = 0; count < 10; count++)
        li_inputlen[count] = 0;
    lc_char = getchar();

    while(lc_char != '\n' && count < BUFFERSIZE)
    {
        if(lc_char != ';')
            BUFFER[num][li_inputlen[num]++] = lc_char;
        else num + +;
        lc_char = getchar();
        count++; // 获取用户输入的指令要考虑用户输入的字符串长度问题，如果超过了长度范围则会报错。因此要定义一个变量count用来统计字符串长度
        // 其中BUFFERSIZE为整型常量，表示buffer的处理范围。lc_char是一个字符串，用来记录用户输入的指令
    }
    // 当用户输入的命令超长时，便会显示警告信息。之后在串尾加上结束符号形成字符串，等待处理
    /*命令超长处理*/
    if(count > BUFFERSIZE)
    {
        printf("Your command too long ! Please reenter your command !\n");
        count = 0;        /* Reset */
        continue;
    }
    else
    {
        for(count = 0; count <= num; count++)
            BUFFER[count][li_inputlen[count]] = '\0'; /*加上串结束符，形成字符串*/
    }
    // 之后将命令从缓存拷贝到input中
    for(count = 0; count <= num; count++)
    {
        input[count] = (char *)malloc(sizeof(char) * (li_inputlen[count] + 1));
        strcpy(input[count], BUFFER[count]);
        // 其中input是字符串型指针数组，长度是(sizeof(char)*(li_inputlen+1))；而malloc是一个动态分配内存的函数。之后通过strcpy是将buffer数组中的命令保存在input数组中。至此，打印提示符以及获取用户输入的指令阶段结束
    }
    // 3. 解析指令
    // 完成了指令输入获取后则需要解析该指令，从而获取命令和参数。在这个过程中需要区分命令和参数，同时还要识别&，>，<，|等字符，从而选择是否需要后台运行、通道、重定向等操作
    /*解析命令， 获取命令和参数并保存在arg中*/
    for(count = 0; count <= num; count++)
    {
        strcpy(buffer, BUFFER[count]);
        for(i = 0, j = 0, k = 0; i <= li_inputlen[count]; i++)
        {

            /*管道和重定向单独处理*/
            if(input[count][i] == '<' || input[count][i] == '>' || input[count][i] == '|')
            {
                if(input[count][i] == '|')
                    pipel(input[count], li_inputlen[count]);
                else
                    redirect(input[count], li_inputlen[count]);
                is_bj = 1;
                break;
            }
            // 首先识别>，<，|。如果(input[count][i]='|')，则调用piple管道函数。如果(input[i]=='>' || input[i]=='<')，则调用redirect重定向函数并做好标识。之后处理空格、TAB等内容。
            /*处理空格、TAB和结束符。不用处理 '\n'*/
            if (input[count][i] == ' ' || input[count][i] == '\t' || input[count][i] == '\0')
            {
                if (j == 0) /*这个条件可以略去连在一起的多个空格或者tab*/
                    continue;
                else
                {
                    buffer[j++] = '\0';
                    arg[k] = (char *) malloc(sizeof(char) * j);
                    /*将指令或参数从缓存拷贝到arg中*/
                    strcpy(arg[k], buffer);
                    j = 0; /*准备取下一个参数*/
                    k++;
                }
            }
            // 在处理空格、TAB和结束符时，满足条件下将指令或参数从缓存拷贝到arg中。之后则识别&字符，完成后台处理。如果后台处理，则标识一下
            else
            {
                /*如果字串最后是'&'，则置后台运行标记为1*/
                if (input[count][i] == '&' && input[count][i+1] == '\0')
                {
                    is_back = 1;
                    continue;
                }
                buffer[j++] = input[count][i];
            }
        }
        free(input[count]);/*释放空间*/

        /*如果输入的指令是bye或exit，则退出while，即退出程序*/
        if (strcmp(arg[0], "bye") == 0 || strcmp(arg[0], "exit") == 0)
        {
            printf("See later. Lucky!\n");
            break;
        }
        // 至此，解析命令过程完成。命令和参数被保存在arg[]中，arg是指向字符数组的指针，其中命令保存在arg[0]中，而参数从arg[1]依次排列保存。

        // 4. 寻找命令文件
        // Shell为每个用户提供了一组环境变量，这些变量定义在用户的.login文件中。其中路径变量是一组绝对路径列表，标明Shell将如何搜索命令文件。因此只要获取路径变量，然后依次搜索各路径就可以确定用户输入的命令文件的位置。
        if (is_bj == 0)
        {
            /*非管道、重定向指令,在使用xxec执行命令的时候，最后的参数必须是NULL指针，所以将最后一个参数置成空值*/
            arg[k] = (char *) 0;
            /*判断指令arg[0]是否存在*/
            if (is_fileexist(arg[0]) == -1 )
            {
                printf("This command is not found !\n");
                for(i = 0; i < k; i++)
                    free(arg[i]);
                continue;
            }
            // 其中函数is_fileexist用来判断输入的指令是否存在。返回0，并将指令的路径保存在buffer中，否则返回-1。is_fileexist函数用来判断输入指令是否存在，存在返回0，并将指令路径保存在buffer中，否则返回- 1。函数如下所示。
            int is_fileexist(char *comm)
            {
                char * path, * p;
                int i;
                i = 0;
                /*使用getenv函数来获取系统环境变量，用参数PATH表示获取路径*/
                path = getenv("PATH");
                p = path;
                while (*p != '\0')
                {
                    /*路径列表使用':'来分隔路径*/
                    if (*p != ':')
                        buffer[i++] = *p;
                    else
                    {
                        buffer[i++] = '/';
                        buffer[i] = '\0';
                        /*将指令和路径合成，形成pathname，并使用access函数来判断该文件是否存在*/
                        strcat(buffer,comm);
                        if (access(buffer,F_OK) == 0) /*文件被找到*/
                            return 0;
                        else
                            /*继续寻找其它路径*/
                            i = 0;
                    }
                    p++;
                }
                /*搜索完所有路径，依然没有找到则返回-1*/
                return -1;
            }
            // getenv函数功能是从环境中取字符串，而stract函数的功能是把src所指字符串添加到dest结尾处(覆盖dest结尾处的'\0')并添加'\0'。accsess函数用来判断文件是否存在，F_OK是buffer长度，存在返回0，否则返回-1。

            //  5． 执行指令
            // 得到命令路径即可执行命令。通过调用fork()创建一个子进程，在程中执行命令。fork()会创建一个新的子进程，其子进程会复制父进程的数据与堆栈空间并继承父进程的用户代码、组代码、环境变量、已打开的文件代码、工作目录和资源闲置等。如果fork成功，则父进程会返回新建自子进程的ID(PID)，而在新建子进程中返回0。如果失败则返回-1。
            // 执行指令通过调用exec函数来实现。exec有一系列的变形函数：execl，execle，execlp，execv，execve，execvp。其中execv有两个参数，分别是指向;命令路径的字符串指针和存放参数的数组指针。execv如果成功则不返回，失败则返回-1。
            /* fork a sub-process to run the execution file */
            if ((pid = fork()) ==0)   /*子进程*/
                execv(buffer,arg);
            else /*父进程*/
                if (is_back == 0)  /*并非后台执行指令*/
                    waitpid(pid,&status,0);

            /*释放申请的空间*/
            for (i=0;i<k;i++)  free(arg[i]);
        }

        // 6． 管道设置
        //   直接使用标准输入/输出文件存在某些问题，因此Linux系统为输入、输出的传送引入了另外两种机制，即管道和输入/输出重定向。
        //  管道用来连接一个进程的输入和另一个进程的输出，是一种单向的通信方式。当进程建立一个管道之后，系统就会为这个进程建立2个文件描述符fd[0]和fd[1]。fd[0]用来进行read操作， fd[1]用来进行write操作。Shell用|在两个命令之间创建管道，操作代码如下。
        int pipel(char * input, int len)
        {
            char * argv[2][30];
            int I, j, k, count, is_back = 0;
            int li_comm = 0, fd[2], fpip[2];
            char lc_char, lc_end[1];
            pid_t child1, child2;

            /* 管道的命令解析过程*/
            for(I = 0, j = 0, k = 0; I<=len; I++)
            {
                if(input[I]==' ' || input[I]=='\t' || input[I]=='\0' || input[I]=='|')
                {
                    if(input[I] == '|')
                    {
                        /* 管道符号*/
                        if(j > 0)
                        {
                            buffer[j++] = '\0';
                            /* 因为管道时连接的是两个指令，所以用二维数组指针来存放命令和参数， li_comm是表示的几个指令*/
                            argv[li_comm][k] = (char *) malloc(sizeof(char) * j);
                            strcpy(argv[li_comm][k++], buffer);
                        }
                        argv[li_comm][k++] = (char *)0;
                        /* 遇到管道符，第一个指令完毕，开始准备第二个指令*/
                        li_comm ++;
                        count = k;
                        k = 0; j = 0;
                    }
                    if(j == 0)  continue;
                    else
                    {
                        buffer[j++] = '\0';
                        argv[li_comm][k] = (char *)malloc(sizeof(char) * j);
                        strcpy(argv[li_comm][k], buffer);
                        k ++;
                    }
                    j = 0; /* Initiate */
                }
                else
                {
                    if(input[I] == '&' && input[I + 1] == '\0')
                    {
                        is_back = 1;
                        continue;
                    }
                    buffer[j ++] = input[I];
                }
            }
            argv[li_comm][k ++] = (char *)0;
            if(is_fileexist(argv[0][0]) == -1)
            {
                printf("This first command is not found !\n");
                for(I = 0; I < count; I ++) free(argv[0][I]);
                return 0;
            }
            /* 指令解析结束*/
            /* 建立管道*/
            if(pipe(fd) == -1)
            {
                printf("Open pipe error !\n");
                return -1;
            }

            /*创建的一个子进程执行管道符前的命令，并将输出写道管道*/
            if((child1 = fork()) == 0)
            {
                /*关闭读端*/
                close(fd[0]);
                if(fd[1] != STDOUT_FILENO)
                {
                    /* 将标准的输出重定向到管道的写入端，这样该子进程的输出就写入了管道*/
                    if(dup2(fd[1], STDOUT_FILENO) == -1)
                    {
                        printf("Redirect Standard Out error !\n");
                        return -1;
                    }
                    /*关闭写入端*/
                    close(fd[1]);
                }
                execv(buffer, argv[0]);
            }
            else
            {
                /*父进程*/
                /* 先要等待写入管道的进程结束*/
                waitpid(child1, &li_comm, 0);
                /* 然后必须写入一个结束标记，告诉读管道进程的数据到这里就完了*/
                lc_end[0] = 0x1a;
                write(fd[1], lc_end, 1);
                close(fd[1]);
                if(is_fileexist(argv[1][0]) == -1)
                {
                    printf("This command is not found!\n");
                    for(I = 0; I < k; I ++) free(argv[1][I]);
                    return 0;
                }

                /* 创建第二个进程执行管道符后的命令，并从管道读输入流*/
                if((child2 = fork()) == 0)
                {
                    if(fd[0] != STDIN_FILENO)
                    {
                        /* 将标准的输入重定向到管道的读入端*/
                        if(dup2(fd[0], STDIN_FILENO) == -1)
                        {
                            printf("Redirect Standard In Error !\n");
                            return -1;
                        }
                        close(fd[0]);
                    }
                    execv(buffer, argv[1]);
                }
                else      /*父进程*/
                    if(is_back == 0)  waitpid(child2, NULL, 0);
            }
            for(I = 0; I < count; I ++)   free(argv[0][I]);
            for(I = 0; I < k; I ++)   free(argv[1][I]);
            return 0;
        }

        // 7． 重定向设置
        //  Linux重定向是指修改原来默认的一些东西，对原来系统命令的默认执行方式进行改变。输入重定向是指把命令( 或可执行程序) 的标准输入重定向到指定的文件中；反之，输出重定向输出重定向是指把命令(或可执行程序)的标准输出重新定向到指定文件中。输入输出重定向函数代码如下:
        int redirect(char *in, int len)
        {
            char *argv[30], *filename[2];
            pid_t pid;
            int i, j, k, fd_in, fd_out, is_in = -1, is_out = -1, num = 0;
            int is_back = 0, status = 0;

            /*这里是重定向的命令解析过程，其中filename用于存放重定向文件，is_in, is_out分别是输入重定向标记和输出重定向标记*/
            for (i = 0, j = 0, k = 0; i <= len; i++){
                if (in[i] == ' ' || in[i] == '\t' || in[i] == '\0' || in[i] == '<' || in[i] == '>'){
                    if (in[i] == '>' || in[i] == '<'){
                        /*重定向指令最多'<'，'>'各出现一次，因此num最大为2，否则认为命令输入错误*/
                        if (num < 3){
                            num ++;
                            if (in[i] == '<')
                                is_in = num - 1;
                            else
                                is_out = num - 1;

                            /*处理命令和重定向符号相连的情况，比如ls>a*/
                            if (j > 0 && num == 1) {
                                buffer[j++] = '\0';
                                argv[k] = (char *) malloc(sizeof(char) * j);
                                strcpy(argv[k], buffer);
                                k++;
                                j = 0;}
                        }
                        else{
                            printf("The format is error!\n");
                            return -1;
                        }
                    }
                    if (j == 0)
                        continue;
                    else{
                        buffer[j++] = '\0';
                        /*尚未遇到重定向符号，字符串是命令或参数*/
                        if (num == 0){
                            argv[k] = (char *) malloc(sizeof(char)*j);
                            strcpy(argv[k],buffer);
                            k++;
                        }
                        /*是重定向后符号的字符串，是文件名*/
                        else{
                            filename[status] = (char *) malloc(sizeof(char)*j);
                            strcpy(filename[status++],buffer);
                        }
                        j = 0; /*initate*/
                    }
                }
                else{
                    if (in[i] == '&' && in[i+1] == '\0'){
                        is_back = 1;
                        continue;
                    }
                    buffer[j++] = in[i];
                }
            }
            argv[k] = (char *) 0;
            if (is_fileexist(argv[0]) == -1 ){
                printf("This command is not found!\n");
                for(i = 0; i < k; i++)
                    free(argv[i]);
                return 0;
            }

            if ((pid = fork()) == 0){
                /*存在输出重定向*/
                if (is_out != -1)
                    if((fd_out = open(filename[is_out], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) == -1){
                        printf("Open out %s Error\n",filename[is_out]);
                        return -1;
                    }
                /*存在输入重定向*/
                if (is_in != -1)
                    if((fd_in = open(filename[is_in], O_RDONLY, S_IRUSR|S_IWUSR)) == -1){
                        printf("Open in %s Error\n", filename[is_out]);
                        return -1;
                    }

                if (is_out != -1)
                    /*使用dup2函数将标准输出重定向到fd_out上，dup2(int oldfd,int newfd)实现的
                     *是把oldfd所指的文件描述符复制到newfd。若newfd为一已打开的文件描述词，
                     *则newfd所指的文件会先被关闭，dup2复制的文件描述词与原来的文件描述词
                     *共享各种文件状态*/

                    if(dup2(fd_out, STDOUT_FILENO) == -1){
                        printf("Redirect Standard Out Error\n");
                        exit(1);
                    }

                if (is_in != -1)
                    if(dup2(fd_in,STDIN_FILENO) == -1){
                        printf("Redirect Standard Out Error\n");
                        exit(1);
                    }
                execv(buffer,argv);
            }
            else
                if (is_back == 0)  /*run on the TOP*/
                    waitpid(pid,&status,0);

            for (i = 0; i < k; i++)
                free(argv[i]);

            if (is_in != -1){
                free(filename[is_in]);
                close(fd_in);
            }
            if (is_out != -1){
                free(filename[is_out]);
                close(fd_out);
            }
            return 0;
        }
    }
}
return 0;
}
