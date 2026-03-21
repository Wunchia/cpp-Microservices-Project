#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("pid=%d\n",getpid());
    printf("ppid=%d\n",getppid());

    sleep(60);

    return 0;
}

