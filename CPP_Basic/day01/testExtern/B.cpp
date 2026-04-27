#include <iostream>
using std::cin;
using std::cout;
using std::endl;

extern int num;
extern void funcA();

namespace wd{
extern int number;
extern void func();
}

void test1(){
    cout<<num<<endl;
    funcA();
}

void test2(){
    cout<<wd::number<<endl;
    wd::func();
}

int main(int argc,char *argv[])
{
    test1(); 
    test2();
    return 0;
}

