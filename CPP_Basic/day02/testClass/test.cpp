#include <iostream>
#include "MyClass.hpp"
using std::cin;
using std::cout;
using std::endl;

void test1(){
    MyClass obj;
    //对象.成员
    obj.func();
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

