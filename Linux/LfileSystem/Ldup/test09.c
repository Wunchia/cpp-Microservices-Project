#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    int fd=open("1.txt",O_WRONLY|O_TRUNC|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open fd failed.");
    printf("11111\n");

    int stdout_backup_fd=dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup(fd);//重定向 让fd=1分给1.txt
    printf("22222\n");

    close(STDOUT_FILENO);//STDOUT_FILENO其实就是fd=1
    dup(stdout_backup_fd);//让fd=1指回标准输出流
    printf("33333\n");

    close(STDOUT_FILENO);
    dup(fd);
    printf("44444\n");
    close(STDOUT_FILENO);
    dup(stdout_backup_fd);
    printf("55555\n");

    close(fd);
    close(stdout_backup_fd);
    close(STDOUT_FILENO);

    //预期屏幕打印11111 33333 55555
    //预期1.txt里写入22222 44444

    return 0;
}

