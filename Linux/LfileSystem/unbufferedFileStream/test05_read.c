#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,NULL,"fild open failed.");

    char buf[10]={0};
    ssize_t ret1=read(fd,buf,sizeof(buf)-1);
    printf("ret1=%ld\n",ret1);
    printf("%s-----\n",buf);

    ssize_t ret2=read(fd,buf,sizeof(buf)-1);
    printf("ret2=%ld\n",ret2);
    printf("%s-----\n",buf);

    close(fd);
    return 0;
}

