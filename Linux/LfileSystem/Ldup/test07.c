#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    close(1);
    int fd=open("1.txt",O_WRONLY);//会把文件标识符1分配给1.txt
    printf("fd=%d\n",fd);
    close(fd);
    return 0;
}

