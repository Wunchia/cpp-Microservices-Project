#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//全局变量
int gNum=100;

void func(){
    cout<<"in func()"<<endl;
}

void test1(){
    //局部变量
    int num1=1;
    int num2=2;
    int *p=new int{10};
    cout<<"&num1="<<&num1<<endl;//栈区地址
    cout<<"&num2="<<&num2<<endl;//栈区地址
    cout<<"&p="<<&p<<endl;//栈区地址
    cout<<"p="<<p<<endl;//堆区地址

    //静态变量
    static int num3=3;
    cout<<"&gNum="<<&gNum<<endl;//全局变量 全局/静态区
    cout<<"&num3="<<&num3<<endl;//静态变量 全局/静态区
    cout<<"&hello="<<&"hello"<<endl;//文字常量区

    //函数指针 输出指针的指向
    void (*f)()=&func;
    f();
    //指针是有效地址 cout会隐式转换为1 因此需要用printf
    cout<<"f="<<f<<endl;
    printf("f=%pf\n",f);//程序代码区
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

