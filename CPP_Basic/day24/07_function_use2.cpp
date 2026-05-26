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
    // 定义了一种新类型 function<double()>容器
    // 作为一种接口
    using AreaCall=function<double()>;
    
    //setAreaCall 初始化
    //回调函数的注册
    void setAreaCall(AreaCall ac){
        m_areaCall=ac;
    }

    // area 调用回调函数
    void handleAreaCall(){
        if(m_areaCall){
            // 调用回调函数
            cout<<"invoke....."<<endl;
            cout<<"area:"<<m_areaCall()<<endl;
        }
    }

    //让新类型作为数据成员
    AreaCall m_areaCall;
};

//子类
class Rectangle
{
public:
    Rectangle(double l,double w):m_l(l),m_w(w){}
    double area(){
        cout<<"Rectangle area"<<endl;
        return m_l*m_w;
    }

    double m_l;
    double m_w;
};

class Circle
{
public:
    Circle(double r):m_r(r){}
    double area(){
        cout<<"Circle area"<<endl;
        return m_r*m_r*3.14;
    }

    double m_r;
};


void test1(){
    Rectangle r(1,2);   //double(Rectangle*)
    Circle c(3);    //double(Circle*)
    Figure f;
    // double()    
    f.setAreaCall(bind(&Rectangle::area,&r));
    f.handleAreaCall();
    cout<<"-----------------"<<endl;
    f.setAreaCall(bind(&Circle::area,&c));
    f.handleAreaCall();
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

