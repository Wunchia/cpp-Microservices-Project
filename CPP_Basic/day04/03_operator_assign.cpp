#include <iostream>
using std::cin;
using std::cout;
using std::endl;
/*
 * 对象的赋值操作：赋值运算符函数
 * 
 * 语法：
 * 类名& operator=(const 类名& rhs){
 *      函数体
 * }
 * 
 * 形式上：
 * 1.为什么返回值要加& ？ 为了能够连续赋值
 * 2.为什么形参要加const ？ 为了能传左值也能传右值
 * 3.为什么形参要加& ？ 为了减少一次拷贝
 *  
 */

class Point{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout<<"Point(int,int)"<<endl;
    }

    //拷贝构造函数
    Point(const Point&rhs)
    :m_x(rhs.m_x)
    ,m_y(rhs.m_y)
    {
        cout<<"Point(const Point&)"<<endl;
    }

    //operator =
    Point& operator=(const Point&rhs){
        cout<<"operator ="<<endl;
        this->m_x=rhs.m_x;
        this->m_y=rhs.m_y;
        return *this;
    }

    void print(){
        cout<<m_x<<" "<<m_y<<endl;
    }

    void show(){        
        cout<<"this:"<<this<<endl;
    }

private:
    int m_x;
    int m_y;
};

void test1(){
    //内置类型
    int a=1;
    int b=2;
    b=a;

    //推广到自定义类型
    Point pt1{1,2};
    Point pt2{3,4};
    pt2=pt1;//调用一个赋值运算符函数
    //赋值运算符函数的本质就是一个成员函数
    pt2.operator=(pt1);
    pt2.print();
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

