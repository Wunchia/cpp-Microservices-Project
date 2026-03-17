#include <my_header.h>

/*Usage:
 * chdir切换工作路径
 * 每一个程序都有自己的工作路径
 * 工作路径一般是继承的
 * 工作路径，就是相对路径的起点*/
int main(int argc,char *argv[])
{
    FILE*fp1=fopen("1.txt","r");//
    ERROR_CHECK(fp1,NULL,"fopen 1.txt in fp1 failed");
    int ret=chdir("/");
    printf("ret=%d\n",ret);
    FILE*fp2=fopen("1.txt","r");
    ERROR_CHECK(fp2,NULL,"fopen 1.txt in fp2 failed");
    return 0;
}

