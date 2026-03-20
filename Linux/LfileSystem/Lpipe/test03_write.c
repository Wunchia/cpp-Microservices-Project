#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_WRONLY);
    ERROR_CHECK(fd,-1,"open pipe failed.");
    char *msg="msg from test03_write.";
    write(fd,msg,strlen(msg));
    close(fd);
    return 0;
}

