#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * C++中提供强转表达式，使用static_cast类型转换
 *
 * 1.基本类型之间的转换
 * 2.void* --->其他类型指针的转换
 *
 *
 */

void test01(){
    double d=3.14;
    int a=(int)d;
    cout<<a<<endl;
}

void test02(){
    double d=3.14;
    int *p=(int *)&d;//无类型检查，不报错，执行后是垃圾值
    cout<<*p<<endl;
}

void test03(){
    double d=3.14;
    /* int *p=static_cast<int*>(&d);//报错，有类型检查 */
    //基本类型之间的转换
    int num=static_cast<int>(d);
    cout<<num<<endl;

    //void*---->其他指针类型的转换
    int *p1=static_cast<int*>(malloc(4));
}

int main(int argc,char *argv[])
{
    test01();    
    test02();
    test03();

    return 0;
}

