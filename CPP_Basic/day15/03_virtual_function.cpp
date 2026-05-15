#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 虚函数：
 * 
 * 
 */

class Father{
public:
    virtual void func1(){
        cout<<"Father::func1()"<<endl;
    }

    void func2(){}

    //声明虚函数
    virtual void func3();
};

//类外具体实现虚函数
//virtual 类外实现时不要再加virtual
void Father::func3(){}

class Son : public Father
{
public:
    //子类中重写虚函数 virtual关键字可省略，但最好写上
    //override:用来标记子类中重写的父类的虚函数
    virtual void func1()override{//子类中virtual 和 override 都可省略
        cout<<"Son::func1()"<<endl;
    }

    void func2()//override 只能标记虚函数 这里是 name hiding
    {}

};

void test1(){
    //通过父类型去调用子对象中的方法 才是多态
    //这里不是多态
    Son son;
    son.func1();//这是隐藏 name hiding
    son.Father::func1();

    //这才是多态
    Father *f=&son;
    f->func1();//这是多态 
    
    //多态的条件
    //1.继承为前提条件
    //2.父类中要定义虚函数 （建立虚表）
    //3.子类中要重写父类的虚函数 override 
    //4.父类的指针或引用接收子对象
    //5.通过父类型调用同名的虚函数（根据具体子对象的实现表现不同）
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

