#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
    //单个变量
    int *p=new int(10);
    delete p;
    
    //连续空间
    int *arr=new int[5]{1,2,3,4,5};
    delete[] arr;//必须使用delete[]

    return 0;
}

