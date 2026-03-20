#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"open pipe failed.");

    char buf[1024]={0};
    ssize_t ret=read(fd,buf,sizeof(buf));
    printf("ret=%d\n",ret);
    printf("msg=%s\n",buf);
    close(fd);
    return 0;
}

