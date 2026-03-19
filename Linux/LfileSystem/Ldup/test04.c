#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    FILE*fp=fopen("222.txt","w");
    ERROR_CHECK(fp,NULL,"fopen failed.");

    fputs("hello\n",fp);
    fflush(fp);
    write(3,"world",5);
    fclose(fp);
    return 0;
}

