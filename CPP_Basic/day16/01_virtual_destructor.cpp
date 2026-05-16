#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 析构函数：destructor
 * 加了virtual后：dtor
 * 
 * 如果没有虚析构函数，父类 子类种涉及动态内存分配
 * 如果使用了多态
 * Father *=子对象， delete f ：通过父指针只能访问父类的析构
 * 子类的析构函数没执行---->内存泄漏
 * 
 * 解决：
 * 使用虚析构函数，析构函数被加入到虚函数表中，
 * 表中存放的肯定是子类的虚析构函数
 * delete f -----> 执行子类的析构函数---->自动调用父类的析构
 * 
 */


class Father{
public:
    Father()
    :m_f(new int{1})
    {
        cout<<"Father();"<<endl;
    }

    virtual ~Father(){ //有了虚表 子类会override析构 只认~ 函数名全叫dtor
        cout<<"~Father()"<<endl;
        delete m_f;
    }

    int*m_f;
};

class Son:public Father
{
public:
    Son()
    :m_s(new int{2})
    {
        cout<<"Son()"<<endl;
    }

    ~Son(){
        cout<<"~Son()"<<endl;
        delete m_s;
    }
    int *m_s;
};

void test1(){
    //栈对象
    // Son son;
    //对象销毁时，调用子类的析构函数，再调用父类的析构函数

    //堆对象
    Father*p=new Son{};
    delete p;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

