#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 虚函数的原理：
 * 对象结构发生了变化 多了一个指针
 * 
 * 虚函数指针：vfptr 指向虚函数表
 * vftable（一个指针数组）:记录要执行的虚函数的地址（函数指针）
 * 
 * 
 */

class Father{
public:
    virtual //加个虚函数 
    void func1(){
        cout<<"Father::func1()"<<endl;
    }
    //===========================================
    virtual 
    void func2(){
        cout<<"Father::func2()"<<endl;
    }

    virtual void display(){
        cout<<"Father::display()"<<endl;
    }

    double m_f=1;
};

class Son : public Father
{
public:
    virtual void display()override{
        cout<<"Son::display()"<<endl;
    }
    double m_s=2;
};

void test1(){
    Father father;
    cout<<sizeof(father)<<endl;//8-->16 多个vfptr
    Son son;
    cout<<sizeof(son)<<endl;//16-->24 多个继承来的vfptr
}

void test2(){
    //使用多态
    Son son;
    Father*f=&son;
    f->display();
    f->func2();
    f->Father::display();
}

int main(int argc,char *argv[])
{
    // test1();    
    test2();
    return 0;
}

