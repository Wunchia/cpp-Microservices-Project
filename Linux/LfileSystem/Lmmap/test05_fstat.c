#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int fd=open(argv[1],O_RDONLY);
    struct stat stat_buf;//定义一个stat结构体
    fstat(fd,&stat_buf);//用fstat取fd的信息
    //stat 需要的传入参数是路径文件名 const char*path
    //fstat 需要的传入参数是文件标识符 int
    printf("%ld\n",stat_buf.st_size);

    return 0;
}

