#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//在构造函数 析构函数中调用虚函数

class Father{
public:
    virtual void func(){
        cout<<"Father::func()"<<endl;
    }

    void fatherMethod1(){
        cout<<"Father::method1()"<<endl;
        Father::func();
    }
    void fatherMethod2(){
        cout<<"Father::method2()"<<endl;
        func();
    }
};

class Son : public Father{
public:
    virtual void func()override{
        cout<<"Son::func()"<<endl;
    }
};

void test1(){
    //测试父对象
    Father father;
    father.fatherMethod1();
    father.fatherMethod2();
    cout<<"--------------"<<endl;
    //测试子对象
    Son son;
    son.fatherMethod1();//father的结果 因为用了类名作用域
    son.fatherMethod2();//son的结果 
    //执行的函数是继承来的，但当前对象（this）仍然是son
    //this指向的自己的vfptr查自己的虚表 找到自己重写的版本
    //这里体现的是一个特殊的多态，
    //运行结果取决于具体对象的类型
}
int main(int argc,char *argv[])
{
    test1();
    return 0;
}

