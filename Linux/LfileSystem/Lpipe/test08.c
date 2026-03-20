#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("open before.\n");
    int fd=open("1.pipe",O_RDWR);
    printf("open after.\n");


    char msg[]="msg from test8.";
    write(fd,msg,sizeof(msg));

    char buf[100]={0};
    ssize_t ret=read(fd,buf,sizeof(buf));
    printf("read msg from pipe=%s\n",buf);
    printf("ret=%ld\n",ret);
    close(fd);
    return 0;
}

