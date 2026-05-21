#include <iostream>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using namespace std;

/*
    智能指针和多态结合
 */

class Father{
public:
    virtual void func()=0;
    // virtual void func(){
    //     cout<<"Father::Func()"<<endl;
    // }
};

class Son: public Father
{
    void func()override{
        cout<<"Son::Func()"<<endl;
    }
};

void test1(){
    // Father* f=new Son{};
    // f->func();

    // <父类型>-----> {子类型的对象}
    unique_ptr<Father> up{new Son{}};
    //通过智能指针调用同名的虚函数
    up->func();
}

int main(int argc,char *argv[])
{
    test1() ;   
    return 0;
}

