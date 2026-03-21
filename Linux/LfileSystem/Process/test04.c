#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    pid_t ret=fork();

    printf("ret=%d\n",ret);

    return 0;
}

