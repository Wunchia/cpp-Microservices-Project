#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 *
 *
 */

class MyClass{
public:
    int getData(){
        return m_data;
    }
    //把普通函数test1声明为友元
    friend void test1();
private:
    friend void test2();
    int m_data=1;
};

void test1(){
    MyClass obj;
    cout<<obj.m_data<<endl;
}

void test2(){
    MyClass obj;
    cout<<obj.m_data<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    test2();
    return 0;
}

