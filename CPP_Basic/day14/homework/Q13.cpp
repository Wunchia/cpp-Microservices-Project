#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
设计一个基类 Animal，
包含一个成员函数 void speak()，输出 "Animal speaks"。
设计一个派生类 Dog，公有继承自 Animal，
在派生类中重新定义一个同名的成员函数 void speak()，
输出 "Dog barks"。

在主函数中：
创建一个 Dog 对象。
通过该对象调用 speak()，观察输出结果。
尝试通过该对象调用基类 Animal 中被隐藏的 speak() 函数
（使用作用域解析符 ::），并观察输出。
*/
class Animal{
public:
    void speak(){
        cout<<"Animal speaks"<<endl;
    }
};

class Dog : public Animal
{
public:
    void speak(){
        cout<<"Dog barks"<<endl;
    }
};

int main(int argc,char *argv[])
{
    Animal ani;
    Dog dog;
    ani.speak();
    dog.speak();
    dog.Animal::speak(); 
    return 0;
}

