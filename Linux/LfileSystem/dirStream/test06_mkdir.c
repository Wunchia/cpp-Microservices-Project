#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    mode_t mode=0767;//设置权限
    int ret=mkdir("test06_md",mode);
    printf("ret=%d\n",ret);
    ERROR_CHECK(ret,-1,"mkdir failed");
    return 0;
}

