#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//父类
class A{
public:
    void func(){
        cout<<"this is A"<<endl;
    }
};

class B{
public:
    void func(){
        cout<<"this is B"<<endl;
    }

};

//子类
class C
:public A
,public B
{
public:
    void func(){
        cout<<"this is C"<<endl;
    }
};

int main(int argc,char *argv[])
{
    C c;
    c.A::func();
    c.B::func();
    c.func();
    
    return 0;
}

