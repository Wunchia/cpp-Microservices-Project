#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 菱形继承
 *
 * 虚拟继承在继承时使用关键字 virtual
 * 
 * 基类的子对象放到对象结构的最下方
 * 
 * 
 */

class A{
public:
    double m_a=1;
};

class B
:virtual public A
{
public:
    double m_b=2;
};

class C
:virtual public A
{
public:
    double m_c=3;
};

class D
:public B
,public C
{
public:
    double m_d=4;
};

void test1(){
    D d;
    cout<<sizeof(d)<<endl;
    cout<<d.m_b<<endl;
    cout<<d.m_c<<endl;
    cout<<d.m_d<<endl;
    cout<<d.m_a<<endl;//使用虚拟继承后可用
    cout<<d.B::m_a<<endl;
    cout<<d.C::m_a<<endl;
    cout<<d.A::m_a<<endl;//使用虚拟继承后可用
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}

