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
    
    //普通函数实现 工具函数
    // int getReal()const{
    //     return m_real;
    // }
    // int getImage()const{
    //     return m_image;
    // }

    void print()const{
        cout<<m_real<<"+"<<m_image<<"i"<<endl;
    }

    friend
    Complex operator+(const Complex&lhs,const Complex&rhs);

    //采用成员函数形式
    // Complex operator+(const Complex&rhs){
    //     return Complex{this->m_real+rhs.m_real,this->m_image+rhs.m_image};
    // }

    friend
    ostream& operator<<(ostream&os,const Complex&cx);

    friend
    istream& operator>>(istream&is,Complex&cx);

    private:
    int m_real;
    int m_image;
};

//普通函数形式
// Complex operator+(const Complex&lhs,const Complex&rhs){
//     return Complex{lhs.getReal()+rhs.getReal(),lhs.getImage()+rhs.getImage()};
// }

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
}

void test2(){
    Complex cx;
    cout<<"please input the real and image: "<<endl;
    cin>>cx;
    cout<<cx<<endl;
}

int main(int argc,char *argv[])
{
    test1(); 
    test2();
    return 0;
}

