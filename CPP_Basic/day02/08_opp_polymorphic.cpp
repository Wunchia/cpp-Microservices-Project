#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 多态：对于同一个指令，不同的子类对象表现的行为或形式不同
 *      这个情况称为多态。
 *
 */

class Animal{
public:
    virtual
    void eat(){
        cout<<"eat..."<<endl;
    }
};

class Dog:public Animal{
    void eat(){
        cout<<"eat meat"<<endl;
    }    
};

class Cat:public Animal{
    void eat(){
        cout<<"eat fish"<<endl;
    }
};

void test1(){
    //多态的使用：通过父类型接收子对象
    //通过父类型调用同名的虚函数
    //体现出来不同的子类的行为
    Dog dog;
    Cat cat;
    Animal *animal;
    animal=&dog;
    animal->eat();
    animal=&cat;
    animal->eat();
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

