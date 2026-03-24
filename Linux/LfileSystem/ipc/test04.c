#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    // 匿名管道：就是匿名的管道，就是不需要写名字。 
    // 仅限于 有血缘关系的 进程间。 

    // 匿名管道，需要使用一个函数。 这个函数 pipe  
    // 调用一次 pipe，会创建一根管子。 它会告诉你，打开的文件描述符是多少。 
    // 并且会开两个文件描述符，一个文件描述符写，一个读。 

    // 传参，必须是一个数组，长度最少为2. 它会将文件描述符存储在这个数组中
    // 这也是一个传入传出参数。 将信息带回
    int pipe_fd[2]={0};
    int ret=pipe(pipe_fd);
    printf("ret=%d\n",ret);
    printf("arr[0]=%d,arr[1]=%d\n",pipe_fd[0],pipe_fd[1]);

    //两个文件描述符，一个用于读，一个用于写。是对同一个匿名管道的操作
    //0号下标用于读，1号下标的文件描述符用于写。
    char msg[]="hello fffffrom test04";
    write(pipe_fd[1],msg,sizeof(msg));

    char buf[100]={0};
    read(pipe_fd[0],buf,sizeof(buf));
    printf("read msg from pipe:%s\n",buf);

    return 0;
}

