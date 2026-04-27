#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void func(const int num){
    // num=20; 报错，num只读
    cout<<"Function param:"<<num<<endl;
}

int main(int argc,char *argv[])
{
    int val=10;
    int other=20;

    const int num=5; //常量变量
    const int *p1=&val;//常量指针：指向的内容不可变
    int *const p2=&val;//指针常量：指针的指向不可变
    const int * const p3=&val;//双重const:指向和内容都不可变

    p1=&other;
    *p2=30;

    func(val);
    return 0;
}

