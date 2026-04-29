#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 规范的初始化一般使用初始化列表的方式进行
 * 数据成员的初始化
 * 
 * 如果有多个数据成员要初始化，中间用逗号分隔
 * 
 * 初始化顺序和声明的数据成员的顺序相关，和初始化列表
 * 的顺序无关
 *  
 */

class Point{
public:
    //无参构造函数
    Point(){
        cout<<"Point()"<<endl;
    }

    //有参构造函数
    Point(int x,int y)
    :m_x(x),m_y(m_x)
    {
        cout<<"Point(int,int)"<<endl;
    }

    void print(){
        cout<<m_x<<" "<<m_y<<endl;
    }
private:
    //列表初始化的顺序 依照类内成员变量声明的顺序
    int m_y;
    int m_x;
};

void test01(){
    Point pt{10,20};
    //使用{}，初始化列表方式
    pt.print();
}

class MyClass{
public:
    //注意！！如果构造函数有默认值，最好不要重载
    MyClass(int data1=1,int data2=1)
    :m_data1(data1)
    ,m_data2(data2)
    {

    }
    // MyClass(){

    // }
private:
    int m_data1=10;//C++之后可以直接给数据成员赋值，相当于初始化
    int m_data2=20;
};

void test2(){
    MyClass obj;
}

int main(int argc,char *argv[])
{
    test01();
    return 0;
}

