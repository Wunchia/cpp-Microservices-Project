#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//直接通过子对象调用 这不是多态

class Father{
public:
    virtual void func(){
        cout<<"Father::func()"<<endl;
    }
};

class Son : public Father{
public:
    virtual void func(){
        cout<<"Son::func()"<<endl;
    }
};

void test1(){
    //创建子类对象
    //通过子对象直接调用
    Son son;
    son.func(); 
    //
    son.Father::func();   
}
int main(int argc,char *argv[])
{
    test1();
    return 0;
}

