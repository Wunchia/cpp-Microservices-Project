#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"open fd failed.");

    char buf[10]={0};
    ssize_t ret=read(fd,buf,sizeof(buf));
    printf("ret=%ld\n",ret);
    printf("%s---\n",buf);
    close(fd);
    return 0;
}

