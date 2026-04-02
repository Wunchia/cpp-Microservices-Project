#include <my_header.h>

/*Usage: */
int main(int argc,char *argv[])
{
    char *ptmp="192.168.100.100";

    struct in_addr addr;
    inet_aton(ptmp,&addr);//点分十进制的字符串ip
                          //转换成了网络字节序的in_addr的十进制形式
    printf("十进制的地址：%d\n",addr.s_addr);//这里addr.s_addr是大端
    printf("%x\n",addr.s_addr);//这里addr.s_addr是大端
    
    printf("=====\n");
    
    printf("%x\n",ntohl(addr.s_addr));

    char*pc=inet_ntoa(addr);//将网络字节序的十进制
                            //转换为本机点分十进制的ip
    printf("pc=%s\n",pc);//这里pc指向的是字符串
    return 0;
}

