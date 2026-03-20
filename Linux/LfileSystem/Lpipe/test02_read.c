#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("open before.\n");
    int fd=open("1.pipe",O_RDONLY);
    printf("open after.\n");
    return 0;
}

