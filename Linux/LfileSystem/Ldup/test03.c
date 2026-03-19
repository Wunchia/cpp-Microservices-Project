#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    FILE *fp=fopen("222.txt","w");
    ERROR_CHECK(fp,NULL,"fopen failed.");

    fputs("hello\n",fp);
    write(3,"world",5);//fp的文件描述符为3，传入5字节
    //write直接写入内核缓冲区 
    fclose(fp);//fclose时会刷新缓冲区
               //用户缓冲区的hello\n才会写入内核缓冲区
    //所以程序输出worldhello\n

    return 0;
}

