#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    //文件的缓冲区是满缓冲区
    FILE*fp=fopen("1.txt","w");
    ERROR_CHECK(fp,NULL,"fp open failed.");

    fputc('a',fp);
    fputc('b',fp);

    fflush(fp);

    //文件标识符从小到大分配 0 stdin 1 stdout 2 stderr
    close(3);

    return 0;
}

