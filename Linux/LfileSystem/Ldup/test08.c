#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    int fd=open("1.txt",O_WRONLY|O_TRUNC|O_CREAT,0666);
    write(fd,"999",3);
    int new_fd=dup(fd);//用一个新的文件描述符指向1.txt

    write(fd,"3333",4);
    write(new_fd,"4444",4);

    printf("fd=%d\n",fd);
    printf("new_fd=%d\n",new_fd);

    close(fd);
    close(new_fd);

    return 0;
}

