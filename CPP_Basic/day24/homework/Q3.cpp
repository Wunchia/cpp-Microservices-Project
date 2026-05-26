#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class Figure
{
public:
    using AreaCall=function<double()>;

    void setAreaCall(AreaCall ac){//注册回调
        m_areaCall=ac;
    }

    void handleAreaCall(){//执行回调
        if(m_areaCall){
            cout<<"invoke....."<<endl;
            cout<<"area:"<<m_areaCall()<<endl;
        }
    }

    AreaCall m_areaCall;
};

class Rectangle{
public:
    Rectangle(double l,double w)
    :m_l(l)
    ,m_w(w){}

    double area(){
        cout<<"Rectangle area"<<endl;
        return m_l*m_w;
    }

    double m_l;
    double m_w;
};


class Circle{
public:
    Circle(double r)
    :m_r(r){}

    double area(){
        cout<<"Circle area"<<endl;
        return m_r*m_r*3.14;
    }

    double m_r;
};

void test1(){
    Rectangle r1{2,3};
    Circle c1{2};
    Figure f1;
    f1.setAreaCall(bind(&Rectangle::area,&r1));
    f1.handleAreaCall();
    cout<<"-----------------"<<endl;
    f1.setAreaCall(bind(&Circle::area,&c1));
    f1.handleAreaCall();
}

int main(int argc,char *argv[])
{
    test1();;    
    return 0;
}

