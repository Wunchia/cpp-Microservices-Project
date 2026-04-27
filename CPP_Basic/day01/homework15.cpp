#include <iostream>
using std::cin;
using std::cout;
using std::endl;
// 内联函数 VS 宏 编程
// 1.使用宏定义计算平方
// 2.使用内联函数计算平方

#define sqrt(a) (a*a)

inline int sqrt2(int a){
    int result=a*a;
    return result;
}

int main(int argc,char *argv[])
{
    cout<<"2的平方="<<sqrt(2)<<endl;
    cout<<"2的平方="<<sqrt2(2)<<endl;
    return 0;
}

