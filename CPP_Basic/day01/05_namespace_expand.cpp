/*#include "myheader.h"*/
#include <string.h>
#include <iostream>
/*#include 第三方库头文件*/

using std::cin;
using std::cout;
using std::endl;

namespace wd{
    int num=1;
    /*int num=2;*/
}

//上下是同一个命名空间
namespace wd{
    /* int num=2; */
}

void test01(){

}

int main(int argc,char *argv[])
{
    test01();    
    return 0;
}

