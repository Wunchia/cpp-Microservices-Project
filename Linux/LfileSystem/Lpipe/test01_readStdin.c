#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char buf[100]={0};
    ssize_t ret=read(0,buf,sizeof(buf));

    printf("read_count=%d\n",ret);
    printf("input_msg=%s\n",buf);

    return 0;
}

