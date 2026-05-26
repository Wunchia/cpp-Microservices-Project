#include <iostream>
#include <functional>
using namespace std;

/*
    使用 std::function + std::bind 实现函数式多态
*/

//父类 抽象类
class Figure
{
public:
    virtual double area()=0;

};

//子类
class Rectangle:public Figure
{
public:
    Rectangle(double l,double w):m_l(l),m_w(w){}
    double area()override{
        cout<<"Rectangle area"<<endl;
        return m_l*m_w;
    }
    double m_l;
    double m_w;
};

class Circle:public Figure
{
public:
    Circle(double r):m_r(r){}
    double area()override{
        cout<<"Circle area"<<endl;
        return m_r*m_r*3.14;
    }
    double m_r;
};

//继承式多态
void test1(){
    Rectangle r(1,2);
    Circle c(3);
    Figure *p=&r;
    cout<<p->area()<<endl;
    p=&c;
    cout<<p->area()<<endl;
}

//函数式多态 ----> std::function 函数多态包装器
void test2(){
    Rectangle r(1,2);
    Circle c(3);
    function<double()> f;
    f=bind(&Rectangle::area,&r);
    cout<<f()<<endl;
    cout<<"-----------------"<<endl;
    f=bind(&Circle::area,&c);
    cout<<f()<<endl;
}

int main(int argc,char *argv[])
{
    test1();
    test2();
    return 0;
}

