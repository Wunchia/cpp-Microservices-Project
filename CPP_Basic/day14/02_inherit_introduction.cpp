#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 
 * 
 * 
 */

//父类 基类 超类
class Animal{
public:
    string name;
    int age;
    void eat(){
        cout<<"eat something!"<<endl;
    }


};

//Dog类继承了Animal
//子类 派生类
class Dog:public Animal{


};

class Cat:public Animal{


};

void test1(){
    Dog dog;
    dog.eat();

    Cat cat;
    cat.eat();
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}
