#include <my_header.h>

/*Usage:想确认工作路径的位置，可以用getcwd */
int main(int argc,char *argv[])
{
    char buf[100]={0};
    char *ret=getcwd(buf,sizeof(buf));

    printf("buf=%s\n",buf);

    chdir("..");

    char *ret2=getcwd(buf,sizeof(buf));
    printf("buf2=%s\n",buf);
    return 0;
}

