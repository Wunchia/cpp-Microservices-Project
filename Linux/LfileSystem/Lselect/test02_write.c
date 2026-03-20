#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int fd=open("1.pipe",O_WRONLY);
    ERROR_CHECK(fd,-1,"1.pipe open failed.");
    printf("open after.\n");

    sleep(30);

    char content[]="hello from test02_write";
    write(fd,content,sizeof(content));
    return 0;
}

