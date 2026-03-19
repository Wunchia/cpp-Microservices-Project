#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    //向stdout输出4个数据项 每个1字节
    fwrite("111\n",1,4,stdout);

    return 0;
}

