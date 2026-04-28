#include <iostream>
using std::cin;
using std::cout;
using std::endl;
/*
 * C++中的struct 和class有啥区别
 * 默认权限不一样，其他一样
 */

class Dog{
    // dog.m_data;//类中如果没有设置权限，默认是private
    int m_data;
    void func(){};
};

//C中的struct不能写函数
//C++中的struct可以写函数，默认权限是public:w
struct Student{
    int m_data;
    void func(){
        cout<<"student::func()"<<endl;
    }
};

void test1(){
    Dog dog;
    //dog.m_data;//默认私有
    Student stu;
    stu.func();
    stu.m_data;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

