#include <my_header.h>

/*Usage:通过传参创建
 * 权限可写可不写*/
int main(int argc,char *argv[])
{
    mode_t mode=0777;
    if(argc>=3){
        sscanf(argv[2],"%o",&mode);
    }
    int ret=mkdir(argv[1],mode);
    ERROR_CHECK(ret,-1,"mkdir failed");

    return 0;
}

