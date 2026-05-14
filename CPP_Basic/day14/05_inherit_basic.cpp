#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 基本语法：在已有的类的继承上进行拓展
 * 子类可用复用父类的成员，也可用定义子类自己的成员
 * 
 * class A{} ----> 父类/基类
 * class B : public A{} 子类/派生类
 */

class Father{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

class son:public Father{//没有加权限的话默认是private继承

};

class Father1{
public:
    int m_father1Data=1;
};

class Father2{
public:
    int m_father2Data=2;
};

class Son1
: public Father1
, public Father2
{};

void test1(){
    Son1 son;
    cout<<son.m_father1Data<<endl;
    cout<<son.m_father2Data<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

