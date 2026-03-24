#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int ret=mkfifo("2.pipe",0666);
    printf("ret=%d\n",ret);
    ERROR_CHECK(ret,-1,"mkfifo failed");
    return 0;
}

