#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Complex{
public:
    Complex(int real,int image)
    :m_real(real)
    ,m_image(image)
    {}
    
    int getReal()const{
        return m_real;
    }
    int getImage()const{
        return m_image;
    }

    void print()const{
        cout<<m_real<<"+"<<m_image<<"i"<<endl;
    }

    // friend
    // Complex operator+(const Complex&lhs,const Complex&rhs);

    //采用成员函数形式
    Complex operator+(const Complex&rhs){
        return Complex{this->m_real+rhs.m_real,this->m_image+rhs.m_image};
    }

    private:
    int m_real;
    int m_image;
};

//普通函数形式
// Complex operator+(const Complex&lhs,const Complex&rhs){
//     return Complex{lhs.getReal()+rhs.getReal(),lhs.getImage()+rhs.getImage()};
// }

//友元函数形式
// Complex operator+(const Complex&lhs,const Complex&rhs){
//     return Complex{lhs.m_real+rhs.m_real,lhs.m_image+rhs.m_image};
// }

void test1(){
    int a=1;
    int b=2;

    Complex cx1{1,1};
    Complex cx2{2,2};
    Complex cx3=cx1+cx2;

    cx3.print();
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}

