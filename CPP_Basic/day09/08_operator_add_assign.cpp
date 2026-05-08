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

    
    Complex& operator+=(const Complex&rhs){
        this->m_real+=rhs.m_real;
        this->m_image+=rhs.m_image;
        return *this;
    }
    

private:
    int m_real;
    int m_image;
};

//友元函数形式
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

    Complex cx1{1,1};
    cout<<cx1<<endl;
    Complex cx2{2,2};
    Complex cx3=cx1+cx2;
    cx3.print();
    cx2.print();
}

void test2(){
    Complex cx;
    cout<<"please input the real and image: "<<endl;
    cin>>cx;
    cout<<cx<<endl;

    Complex cx1{1,2};
    cx+=cx1;
    cout<<cx<<endl;
    
}

int main(int argc,char *argv[])
{
    test1(); 
    test2();
    return 0;
}

