#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 类型转换
 * 1.基本类型 ----> 自定义类型
 * 2.自定义类型 ----> 基本类型
 * 3.自定义类型 ---->另一个自定义类型
 * 
 * 自定义类型转换成其他的类型 ----> 类型转换函数
 * 语法：
 * operator 目标类型(){
 *      返回目标类型的数据或对象
 * }
 * 
 */

class A{
public:
    // explicit   //禁止隐式转换
    A(int data)
    : m_data(data)
    {
        cout<<"A(int)"<<endl;
    }

    int m_data;
};

void test1(){
    //一般的使用情况
    A a{1};
    cout<<a.m_data<<endl;

    //类型转换的情况
    A a2=10; //int ---> 自定义类型 隐式转换
             //调用A类的有参构造函数
    cout<<a2.m_data<<endl;
}

class Complex;

class Point{
public:
    Point(int x, int y)
    :m_x(x)
    ,m_y(y)
    {}

    //提供一个特殊的构造函数
    Point(const Complex& rhs);


    operator int(){
        cout<<"operator int()"<<endl;
        return m_x+m_y;
    }

    //一般的operator=
    //   Point& operator=(const Point &);
    //   Point& operator=(const Complex &rhs);

private:
    int m_x;
    int m_y;
};


void test2(){
    Point pt{1,2};
    int sum=pt;// Point ----> int
    cout<<sum<<endl;
}

class Complex{
public:
    Complex(int real,int image)
    :m_real(real)
    ,m_image(image)
    {}

    operator Point(){
        cout<<"Complex::Complex--->Point"<<endl;
        return Point{m_real,m_image};
    }

    friend Point::Point(const Complex&);
    // friend Point& Point::operator=(const Complex&);

private:
    int m_real;
    int m_image;
};


Point::Point(const Complex& rhs)
:m_x(rhs.m_real)
,m_y(rhs.m_image)
{
    cout<<"Point(const Complex&)"<<endl;
}

// Point& Point::operator=(const Complex &rhs){
//     cout<<"Point& operator=(const Complex&)"<<endl;
//     this->m_x=rhs.m_real;
//     this->m_y=rhs.m_image;
//     return *this;
// };

//测试自定义类型---->另一个自定义类型转换
//Complex对象 ----> Point类型的对象
//在哪个类里面写类型转换函数？
void test3(){
    Complex cx{3,4};
    Point pt{1,2};
    pt=cx;

    //扩展
    //除了使用类型转换函数外，还可以使用其他方式
    //1.使用参数特殊的构造函数
    //2.使用赋值运算符函数
}

int main(int argc,char *argv[])
{
    // test1();    
    // test2();
    test3();
    return 0;
}

