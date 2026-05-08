#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::string;

class Complex{
public:
    Complex(){}

    Complex(int real,int image)
    :m_real(real)
    ,m_image(image)
    {}
    

    void print()const{
        cout<<m_real<<"+"<<m_image<<"i"<<endl;
    }

    friend
    Complex operator+(const Complex&lhs,const Complex&rhs);

    friend
    ostream& operator<<(ostream&os,const Complex&cx);

    friend
    istream& operator>>(istream&is,Complex&cx);

    //operator+=
    Complex& operator+=(const Complex&rhs){
        this->m_real+=rhs.m_real;
        this->m_image+=rhs.m_image;
        return *this;
    }

    //operator++ 前置++
    //参数：无参
    //返回值：Complex&
    Complex& operator++(){
        cout<<"operator++()"<<endl;
        this->m_real+=1;
        this->m_image+=1;
        return *this;
    }

    //operator++ 后置++
    //参数：无参
    //返回值：Complex
    //C++标准中规定 对于后置++ 参数设置int
    //int本身没有任何含义，就是一个标记 用来区分前置和后置++
    Complex operator++(int){
        //用一个临时的对象来保持初始的对象状态
        Complex temp=*this;
        this->m_real+=1;
        this->m_image+=1;
        return temp;
    }

private:
    int m_real;
    int m_image;
};

//友元函数形式 operator+
Complex operator+(const Complex&lhs,const Complex&rhs){
    return Complex{lhs.m_real+rhs.m_real,lhs.m_image+rhs.m_image};
}

//采用友元函数的重载 operator<<
ostream& operator<<(ostream& os,const Complex&cx){
    os<<cx.m_real <<"+"<<cx.m_image<<"i";
    return os;
}

//采用友元函数重载 operator>>
istream& operator>>(istream& is,Complex&cx){
    is>>cx.m_real>>cx.m_image;
    return is;
}

void test1(){
    int a=1;
    &(++a);//左值
    //&(a++);//右值
    Complex cx1{1,1};
    //前置++ 形式上用成员函数
    cout<<"-----前置++-----"<<endl;
    cout<<cx1<<endl;
    cout<<++cx1<<endl;
    cout<<cx1<<endl;
    // Complex& cx.operator++();

    // 后置
    //cx++;
    //
    cout<<"-----后置++----"<<endl;
    cout<<cx1<<endl;
    cout<<cx1++<<endl;
    cout<<cx1<<endl;
}


int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

