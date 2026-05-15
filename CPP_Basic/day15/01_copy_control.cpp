#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 拷贝构造 赋值运算符函数
 * 如果类中没有显式写出来拷贝构造和赋值运算符函数，
 * 会调用默认版本的拷贝构造和赋值运算符函数
 * 子类自己的成员和继承来的父类成员都会进行复制
 * 
 * 如果你在代码中显式的写出来拷贝构造，
 * 那么要在子类中手动调用父类的拷贝构造
 * 
 */

class Father{
public:
    Father(){
        cout<<"Father();"<<endl;
    }
    Father(int f)
    :m_f(f)
    {
        cout<<"Father(int);"<<endl;
    }

    Father(const Father&rhs)
    :m_f(rhs.m_f)
    {
        cout<<"Father(const Father&);"<<endl;
    }

    Father&operator=(const Father&rhs)
    {
        cout<<"Father&operator=(const Father&);"<<endl;
        this->m_f=rhs.m_f;
        return *this;
    }

    int m_f;
};

class Son: public Father{
public:
    Son(int f,int s)
    :Father(f)
    ,m_s(s)
    {
        cout<<"Son(int,int);"<<endl;
    }

    Son(const Son&rhs)
    :Father(rhs)
    ,m_s(rhs.m_s)
    {
        cout<<"Son(const Son&)"<<endl;
    }

    Son &operator=(const Son &rhs){
        cout<<"Son &operator=(const Son&);"<<endl;
        this->Father::operator=(rhs);
        this->m_s=rhs.m_s;
        return *this;
    }

    int m_s;
};

void test1(){
    Son s1{1,2};
    Son s2=s1;
    cout<<s2.m_f<<endl;
    cout<<s2.m_s<<endl;
}

void test2(){
    Son s1{1,2};
    Son s2{3,4};
    s2=s1;

    cout<<s2.m_f<<endl;
    cout<<s2.m_s<<endl;
}

int main(int argc,char *argv[])
{
    // test1(); 
    test2();
    return 0;
}

