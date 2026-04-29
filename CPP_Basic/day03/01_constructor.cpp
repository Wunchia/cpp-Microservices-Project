#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 构造函数：constructor
 * 特殊的成员函数。
 * 作用：在对象创建过程中会自动调用
 * 
 * 语法：
 * 类名（形参列表）{
 *      构造函数体
 * }
 * 说明：
 * 1.没有返回值类型
 * 2.函数名必须和类名一样
 * 3.形参列表和普通函数一样
 * 无参：无参构造函数
 * 有参：有参构造函数
 * ----->构成构造函数的重载（类中可以有多个构造函数）
 * 4.把一些初始化的操作放在构造函数体内部
 * 
 * 注意：
 * 1.如果类中没有写任何的构造函数，编译器会帮我们生成一个默认无参构造函数
 * 2.如果类中有任意的构造函数，编译器就不会帮我们生成一个默认无参构造函数
 *  
 */

class Point{
public:
    //无参构造函数
    Point(){
        m_x=1;
        m_y=2;
        cout<<"Point()"<<endl;
    }

    //有参构造函数
    Point(int x,int y=2){
        cout<<"Point(int,int)"<<endl;
        m_x=x;
        m_y=y;
    }

    /*void setX(int x){
        m_x=x;
    }
    void setY(int y){
        m_y=y;
    }
    */
    void print(){
        cout<<m_x<<" "<<m_y<<endl;
    }
private:
    int m_x;
    int m_y;
};

void test01(){
    Point pt1;
    // Point pt1();
    // 注意！！无参构造函数调用时，不能加小括号，因为会被视作函数声明
    // 但是可以加{}
    Point pt{};
    // pt.setX(1);
    // pt.setY(2);
    pt1.print();

    pt.print();
    cout<<"-----------"<<endl;

    // Point pt2(1);
    Point pt2{10,20};
    //使用{}，初始化列表方式
    pt2.print();
}

class MyClass{
public:
    //可以显式地把无参构造函数写出来
    // MyClass(){};
    MyClass()=default;
    //增加一个构造函数
    MyClass(int data){
        m_data=data;
    }
    int m_data;
};

void test02(){
    // MyClass obj;//会调用无参构造
    MyClass obj2{2};
}

int main(int argc,char *argv[])
{
    test01();
    // test02();
    return 0;
}

