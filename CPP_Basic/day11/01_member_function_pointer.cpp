#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void func1()
{
    cout << "func1()" << endl;
}

void func2()
{
    cout << "func2()" << endl;
}

void func3()
{
    cout << "func3()" << endl;
}

void test1()
{
    func1();
    func2();
    func3();

    cout<<"-----简写-----"<<endl;
    //简写形式
    void (*f)()=func1;
    f();

    cout<<"-----完整------"<<endl;
    // 完整写法
    f = &func2;
    (*f)();
    f();

    cout << "-----别名-----" << endl;
    // 定义一个别名
    typedef void (*F)();
    int a = 1;
    F ff = &func1;
    ff();

    cout << "-------------" << endl;
    // 其他写法 C++11后可以用using
    //using 别名=代指的类型
    using FFF = void (*)();
    int b = 1;
    FFF fff = &func3;
    fff();
}

class FFF{
public:
    void f1(){
        cout<<"FFF::f1()"<<endl;
    }

    void f2(){
        cout<<"FFF::f2()"<<endl;
    }

    void f3(){
        cout<<"FFF::f3()"<<endl;
        cout<<"m_data: "<<m_data<<endl;
    }
    int m_data=1;
};

void test2(){
    FFF obj;
    obj.f1();
    obj.f2();
    obj.f3();
    FFF *p=&obj;
    p->f1();
    p->f2();
    p->f3();
    cout<<"----------"<<endl;
    //使用类名作用域方式
    //对于成员函数指针来说需要完整写法
    void (FFF::*f)()=&FFF::f1;
    //成员函数的调用需要依赖于对象
    (obj.*f)();//对象.f1(); 解引用得到函数名称
    (p->*f)();//指针->f1();
}

//空指针测试
void test3(){
    //此时有没有对象存在？ 没有
    FFF *p=nullptr;
    p->f1();
    p->f2();
    p->f3();
}
int main(int argc, char *argv[])
{
    // test1();
    // test2();
    test3();
    return 0;
}
