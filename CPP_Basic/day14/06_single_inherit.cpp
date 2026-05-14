#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 单继承下的子类对象的创建和销毁过程
 * 
 * 创建过程：先父后子 
 */

class Father{
public:
    Father(){
        cout<<"Father()"<<endl;
    }

    Father(int f)
    :m_f(f)
    {
        cout<<"Father(int)"<<endl;
    }

    ~Father(){
        cout<<"~Father()"<<endl;
    }
    int m_f;
};

class Son:public Father
{
public:
    Son(){//有一个隐式的初始化 默认会调用父类的无参构造
        cout<<"Son()"<<endl;
    }

    //有参构造
    Son(int f,int s)
    :Father(f)
    ,m_s(s)
    {
        cout<<"Son(int,int)"<<endl;
    }

    ~Son(){
        cout<<"~Son()"<<endl;
    }

    int m_s;
};

void test1(){
    Son son;
    cout<<son.m_f<<endl;
    cout<<son.m_s<<endl;
    cout<<sizeof(son)<<endl;
    //子类对象中有2部分，一部分继承来的父类的成员
    //另一部分子类自己定义的

}

void test2(){
    // Son son1;
    // cout<<sizeof(son1)<<endl;
    cout<<"--------------------"<<endl;
    Son son2{1,2};
}

int main(int argc,char *argv[])
{
    // test1();    
    test2();
    return 0;
}

