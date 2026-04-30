#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 对象数据成员
 * 自定义类型中用到了其他的自定义类型
 * 
 * class B{
 * 
 * }
 * class A{
 *   B b;
 * }
 *
 */

class A{
public:
    A(){
        cout<<"A()"<<endl;
    }

    A(int data)
    :m_dataA(data)
    {
        cout<<"A()"<<endl;
    }

    ~A(){
        cout<<"~A()"<<endl;
    }

    int m_dataA;
};

class B{
public:
    B(){
        cout<<"B()"<<endl;
    }

    B(int data)
    :m_dataB(data)
    {
        cout<<"B()"<<endl;
    }

    ~B(){
        cout<<"~B()"<<endl;
    }

    int m_dataB;
};

class C{
    public:
    C(){ //没有加初始化列表，但是这里有隐式的调用
        cout<<"C()"<<endl;
    }

    C(int a,int b)
    : m_a(a)
    ,m_b(b)
    {
        cout<<"C(int,int)"<<endl;
    }

    ~C(){
        cout<<"~C()"<<endl;
    }

    //对象类型的成员数据
    A m_a;
    B m_b;
};

void test1(){
    C c(1,2);
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}
