#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class Complex{
public:
    Complex(int real=0,int image=0)
    :m_real(real)
    ,m_image(image)
    {}

    //-----打印------
    void print()const{
        cout<<m_real<<"+"<<m_image<<"i"<<endl;
    }

    //------流重载------
    friend ostream& operator<<(ostream& os,const Complex&cx);
    friend istream& operator>>(istream& is,Complex&cx);

    //-----加减法------
    friend Complex operator+(const Complex&lhs,const Complex&rhs);
    friend Complex operator-(const Complex&lhs,const Complex&rhs);

    //------复合赋值运算符------
    Complex& operator+=(const Complex&rhs){
        this->m_real+=rhs.m_real;
        this->m_image+=rhs.m_image;
        return *this;
    }

    Complex& operator-=(const Complex&rhs){
        this->m_real-=rhs.m_real;
        this->m_image-=rhs.m_image;
        return *this;
    }

    //------自增运算符-------
    // 前置++
    Complex& operator++(){
        ++m_real;
        ++m_image;
        return *this;
    }

    // 后置++ 
    Complex operator++(int){
        Complex temp=*this;
        ++(*this);
        return temp;
    }

    //------自减运算符-------
    // 前置--
    Complex& operator--(){
        --m_real;
        --m_image;
        return *this;
    }

    // 后置-- 
    Complex operator--(int){
        Complex temp=*this;
        --(*this);
        return temp;
    }

private:
    int m_real;
    int m_image;
};

//-----非成员函数实现------
Complex operator+(const Complex& lhs,const Complex& rhs){
    return Complex{lhs.m_real+rhs.m_real,lhs.m_image+rhs.m_image};
}

Complex operator-(const Complex& lhs,const Complex& rhs){
    return Complex{lhs.m_real-rhs.m_real,lhs.m_image-rhs.m_image};
}

ostream& operator<<(ostream& os,const Complex&cx){
    os<<cx.m_real<<"+"<<cx.m_image<<"i";
    return os;
}

istream& operator>>(istream& is,Complex&cx){
    is>>cx.m_real>>cx.m_image;
    return is;
}

//测试函数
void test_operators(){
    Complex c1{5,5};
    Complex c2{2,3};

    cout<<"Initial: c1="<<c1<<", c2="<<c2<<endl;

    cout<<"c1+c2="<<(c1+c2)<<endl;
    cout<<"c1-c2="<<(c1-c2)<<endl;

    c1+=c2;
    cout<<"c1+=c2 后 c1="<<c1<<endl;
    c1-=c2;
    cout<<"c1-=c2 后 c1="<<c1<<endl;

    cout<<"-----Inc/Dec Test----"<<endl;
    cout<<"Before: c1="<<c1<<endl;
    cout<<"后置++ "<<c1++<<" after: "<<c1<<endl;
    cout<<"前置++ "<<++c1<<" after: "<<c1<<endl;
    cout<<"后置-- "<<c1--<<" after: "<<c1<<endl;
    cout<<"前置-- "<<--c1<<" after: "<<c1<<endl;
}

int main(int argc,char *argv[])
{
    test_operators();
    return 0;
}

