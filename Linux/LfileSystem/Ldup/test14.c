#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    close(STDIN_FILENO);
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDONLY);

    printf("fd=%d\n",fd);

    int num1=0;
    double d1=0.0;
    scanf("%d %lf",&num1,&d1);
    printf("num1=%d\n d1=%lf\n",num1,d1);
    return 0;
}

