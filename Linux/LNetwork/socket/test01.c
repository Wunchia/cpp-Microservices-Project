#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    int num=0x75767778;
    //0x78=7*16+8=112+8=120-->ASCII x
    //0x75=7*16+5=112+5=117-->ASCII u
    char*ptmp=(char*)&num;
    printf("ptmp:%c\n",*ptmp);

    int a=htonl(num);
    char*pa=(char*)&a;
    printf("pa:%c\n",*pa);
    return 0;
}

