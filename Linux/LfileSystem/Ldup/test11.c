#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    int ret=dup2(STDOUT_FILENO,9);//许愿函数，把fd=9给old_fd指向的文件 失败返回-1
    printf("fd=%d\n",ret);
    write(9,"hello again\n",12);
    return 0;
}

