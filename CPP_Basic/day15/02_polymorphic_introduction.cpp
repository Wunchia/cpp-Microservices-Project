#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 多态：统一指令，针对不同的子类对象，表现出不同的行为
 * 
 * 代码中的体现：
 * 继承的前提条件下，父类型（指针或引用）接收子类对象，
 * 通过父类型的指针或者引用调用父子同名的虚函数，
 * 体现出不同的子类行为
 * 
 * override：重写
 * 
 */

class Phone{
public:
    virtual void aiAssitant()=0;
};

class Xiaomi:public Phone
{
public:
    virtual void aiAssitant(){
        cout<<"小爱同学"<<endl;
    }
};

class Huawei:public Phone
{
public:
    virtual void aiAssitant(){
        cout<<"小艺小艺"<<endl;
    }

};

class Apple:public Phone
{
public:
    virtual void aiAssitant(){
        cout<<"siri"<<endl;
    }

};

class Vivo:public Phone
{
public:
    virtual void aiAssitant(){
        cout<<"小 V"<<endl;
    }

};

void test1(){
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;
    //父类型的指针或引用接收子对象
    Phone *p;
    p=&phone1;
    p->aiAssitant();

    p=&phone2;
    p->aiAssitant();

    p=&phone3;
    p->aiAssitant();
}

void handlePhone1(Xiaomi *p){
    p->aiAssitant();
}

void handlePhone2(Huawei *p){
    p->aiAssitant();
}

void handlePhone3(Apple *p){
    p->aiAssitant();
}

//提供一个函数可以进行复用 处理所有的手机
//扩展性更好
void handlePhone(Phone *p){
    p->aiAssitant();
}

void test2(){
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;
    Vivo phone4;
    // handlePhone1(&phone1);
    // handlePhone2(&phone2);
    // handlePhone3(&phone3);

    handlePhone(&phone1);
    handlePhone(&phone2);
    handlePhone(&phone3);
    handlePhone(&phone4);
}
int main(int argc,char *argv[])
{
    test1();    
    // test2();
    return 0;
}

