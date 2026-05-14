#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 访问权限修饰符：
 * public
 * 
 * private
 * 
 * protected 
 * 
 * 
 * private VS protected:
 * 继承时访问的权限不同
 */

class MyClass{
public:
    void func(){
        m_data_public;
        m_data_protected;
        m_data_protected;
    }

    int m_data_public;
protected:
    int m_data_protected;
private:
    int m_data_private;
};

void test1(){
    MyClass obj;
    obj.m_data_public;
    // obj.m_data_protected;
    // obj.m_data_private;
}
//===========================================

class Father{
public:
    int m_data1;
protected:
    int m_data2;//只能在类内访问，但可以继承给子类
private:
    int m_data3;//只有father内能访问，也继承不了
};

class Son:public Father{
public:
    void sonMethod(){
        m_data1;// 
        m_data2;// protected OK
        // m_data3;// private NO
    }

};

int main(int argc,char *argv[])
{
    
    return 0;
}

