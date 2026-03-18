#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0654);
    ERROR_CHECK(fd,-1,"open file failed.");

    ssize_t ret=write(fd,"hello",4);
    printf("ret=%ld\n",ret);
    
    close(fd);
    return 0;
}

