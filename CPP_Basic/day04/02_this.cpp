#include <iostream>
using std::cin;
using std::cout;
using std::endl;
/*
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

    //所有的成员函数中，形参列表中都有1个隐含的参数this
    //this本质是一个指针，常量指针
    //指向的是当前对象
    //哪个对象调用这个函数，谁就是当前对象
    void print(){
        cout<<m_x<<" "<<m_y<<endl;
        this;
        this->m_x;
        this->m_y;
    }

    void show(){        
        cout<<"this:"<<this<<endl;
    }

private:
    int m_x;
    int m_y;
};

void test1(){
    Point pt{1,2};
    //pt就是当前对象
    pt.show();
    cout<<"pt的地址："<<&pt<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

