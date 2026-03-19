#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("111\n");
    int fd=open("1.txt",O_RDONLY);
    printf("fd=%d\n",fd);
    return 0;
}

