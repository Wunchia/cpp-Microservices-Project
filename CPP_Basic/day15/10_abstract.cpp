#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 纯虚函数：虚函数，但没有实现
 * 
 * 抽象类：类中有纯虚函数的类 --->不能进行实例化（不能创建对象）
 * 
 * 抽象类一般作为接口或者标准存在,具体的实现交给子类去做
 * 强制子类去实现这个接口
 *
 * 抽象类：如果子类中有还没有实现的纯虚函数，
 * 那么这个子类也是抽象类，也不能实例化
 */

//抽象类
class AbstractClass{
public:
    //纯虚函数
    virtual void func()=0;
};

class Animal{
public:
    virtual void eat()=0;
};

class Dog:public Animal
{
public:
    virtual void eat(){
        cout<<"eat meat"<<endl;
    }
};

class Cat:public Animal
{
public:
    virtual void eat(){
        cout<<"eat fish"<<endl;
    }
};

// void handle(Animal *p){
//     p->eat();
// }

void test1(){
    Dog dog;
    Cat cat;
    Animal* p=&dog;
    p->eat();
    p=&cat;
    p->eat();
}

class A
{
public:
    virtual void func1()=0;
    virtual void func2()=0;
    virtual void func3()=0;
};

//B只实现了func1 所有仍然是抽象类
class B:public A
{
public:
    virtual void func1(){};
};

class C:public B{
public:
    virtual void func2(){}
    virtual void func3(){}
};

void test2(){
    // A a;
    // B b;
    C c;
}

int main(int argc,char *argv[])
{
    test1();    
    test2();
    return 0;
}

