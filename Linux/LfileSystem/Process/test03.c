#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("fork before\n");
    pid_t ret=fork();
    printf("fork after.\n");
    return 0;
}

