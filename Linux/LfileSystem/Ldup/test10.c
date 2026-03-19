#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    int fd=open("1.txt",O_WRONLY|O_TRUNC);
    ERROR_CHECK(fd,-1,"open failed.");
    printf("11111\n");

    int stdout_backup_fd=dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup(fd);
    printf("22222\n");

    close(STDOUT_FILENO);
    printf("33333\n");//此时fd=1为空 数据33333会丢失

    close(fd);
    close(stdout_backup_fd);
    close(STDOUT_FILENO);

    return 0;
}

