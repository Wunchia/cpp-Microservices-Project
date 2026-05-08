#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 *  所有带 . 的和sizeof运算符不能重载，其他的可以
 *
 * 运算符重载的本质：函数调用
 * 1.普通的函数 test1()
 * 2.成员函数  对象.func() 指针->func()
 * 
 * 重载一个运算符时，需要考虑：
 * 1.采用什么形式：普通函数 or 成员函数
 * 2.函数的返回值
 * 3.函数的参数
 * 4.函数体的代码逻辑应该怎么写，和运算符本身逻辑一致
 * 
 */

class Point{
public:
    Point(int x,int y)
    : m_x(x)
    , m_y(y)
    {}

    Point &operator=(const Point&rhs){
        this->m_x=rhs.m_x;
        this->m_y=rhs.m_y;
        return *this;
    }

    Point operator+(const Point&rhs){
        Point temp(this->m_x+rhs.m_x,this->m_y+rhs.m_y);
        return temp;
    }

    void print()const{
        cout<<m_x<<" "<<m_y<<endl;
    }
private:
    int m_x;
    int m_y;    
};

void test1(){
    int a=1;
    int b=2;
    a+b;

    Point pt1{1,2};
    Point pt2{3,4};
    Point pt3=pt1+pt2;
    //简写
    // pt2=pt1;
    //本质是成员函数的调用
    pt2.operator=(pt1);
    pt2.print();
    pt3.print();
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

