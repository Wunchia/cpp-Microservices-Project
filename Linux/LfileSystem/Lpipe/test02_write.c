#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("open befor.\n");
    int fd=open("1.pipe",O_WRONLY);
    printf("open after.\n");
    return 0;
}

