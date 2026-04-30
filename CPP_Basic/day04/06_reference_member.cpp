#include <iostream>
#include <string>
using std::ostream;
using std::string;
using std::cin;
using std::cout;
using std::endl;

/*
 * 引用数据成员：必须要在初始化列表中进行初始化
 *
 * 引用所绑定的 变量或者对象 声明周期大于等于该对象
 */


class Point{
public:
    Point(int x,int y,int &z)
    :m_x(x)
    ,m_y(y)
    ,m_z(z)
    {}
    void print(){
        cout<<m_x<<" "<<m_y<<" "<<m_z<<endl;
    }
    int m_x;
    int m_y;
    //引用数据成员
    int &m_z;

private:

};

void test1(){
    int num=3;
    Point p1{1,2,num};
    p1.print();
}

//====================================================
class Mother;

class Baby{
public:
    Baby(string name,Mother &m)
    :m_name(name)
    ,m_mother(m)
    {}

    string m_name;
    Mother &m_mother;
};

class Mother{
public:
    Mother(string name)
    :m_name(name)
    {}

    string m_name;
};

void test2(){
    Mother mother{"lili"};
    Baby baby{"Kongling",mother};
}

//===================================================

class Printer{
public:
    Printer(ostream &os)
    :m_os(os)
    {}
    ostream &m_os;
    void print(){
        m_os<<"123";
    }
};

void test3(){
    Printer pt{cout};
    pt.print();
}

int main(int argc,char *argv[])
{
    // test1();    
    test3();
    return 0;
}

