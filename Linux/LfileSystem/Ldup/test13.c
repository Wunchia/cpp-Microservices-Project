#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    //下面的printf会将程序的缓冲模式定为行缓冲 之后dup2再printf也不会改变
    printf("Hello world\n");
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open file failed.");

    int temp=dup(STDOUT_FILENO);
 
    dup2(fd,STDOUT_FILENO);
    //如果注释掉开头的hello world 会在这里将程序的缓冲模式定为满缓冲
    printf("how are you\n");//指向文件 满缓冲区 有\n也暂时没有输出 但不变
    dup2(temp,STDOUT_FILENO);
    printf("i'm ok\n");//指向终端 行缓冲区 遇到\n就输出 但不变
    dup2(fd,STDOUT_FILENO);
    printf("me too\n");

    close(fd);
    return 0;
}
