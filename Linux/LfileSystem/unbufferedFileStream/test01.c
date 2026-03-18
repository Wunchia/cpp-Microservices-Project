#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    FILE*fp1=fopen("1.txt","r");
    ERROR_CHECK(fp1,NULL,"fopen failed.");
    
    char buf[120]={0};
    int ret=fread(buf,sizeof(char),100,fp1);
    ERROR_CHECK(ret,-1,"get buf from fread failed.");
    printf("fread=%s\n",buf);

    fclose(fp1);
    
    //理解用户态缓冲区
    FILE *fp2;
    fp2->_IO_read_base;
    //FILE中存在大量指针，
    //指向用户空间，不是内核
    
    fclose(fp2);
    return 0;
}

