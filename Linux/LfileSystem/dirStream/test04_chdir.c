#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    FILE*fp1=fopen("1.txt","r");
    ERROR_CHECK(fp1,NULL,"fp1 in . open failed");
    chdir("..");
    FILE*fp2=fopen("1.txt","r");
    ERROR_CHECK(fp2,NULL,"fp2 in .. open failed");
    return 0;
}

