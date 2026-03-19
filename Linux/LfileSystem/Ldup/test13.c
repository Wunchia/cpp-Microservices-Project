#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0664);
    ERROR_CHECK(fd,-1,"open file failed.");

    int temp=dup(STDOUT_FILENO);
    dup2(fd,STDOUT_FILENO);
    printf("how are you\n");//指向文件 满缓冲区 有\n也暂时没有输出
    dup2(temp,STDOUT_FILENO);
    printf("i'm ok\n");//指向终端 行缓冲区 遇到\n就输出
    dup2(fd,STDOUT_FILENO);
    printf("me too\n");

    close(fd);
    return 0;
}

