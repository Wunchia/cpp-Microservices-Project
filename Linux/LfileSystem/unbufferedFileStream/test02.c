#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    //无缓冲区文件流：
    //指的是在用户空间没有缓冲区
    //数据都是直接从内核中读取
    //这时候只提供了按照数组读取
    //返回值：有缓冲文件流返回 FILE* 含有大量地址
    //        无缓冲文件流返回 int 是文件描述符
    //（无缓冲文件流不能把内核空间地址暴露出来）
    //系统内核知道int（文件描述符）的对应关系
    // FILE* 不是文件描述符 但包含文件描述符

    //打开有缓冲文件流用 fopen
    //打开无缓冲文件流用 open

    printf("%o\n",O_RDONLY);
    printf("%o\n",O_WRONLY);
    printf("%o\n",O_RDWR);
    printf("%o\n",O_APPEND);
    printf("%o\n",O_CREAT);
    printf("%o\n",O_EXCL);

    //错误写法，要加权限
    //int fd=open("1.txt",O_WRONLY|O_CREAT);
    //正确写法如下：
    int fd=open("1.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fd,-1,"open fd failed.");

    close(fd);
    return 0;
}

