#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int ret=unlink(argv[1]);
    printf("ret=%d\n",ret);
    ERROR_CHECK(ret,-1,"unlinke failed");
    return 0;
}

