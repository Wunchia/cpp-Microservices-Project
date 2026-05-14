#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 继承的实质：
 * 把子类当作父类来使用，满足 "子类 is a 父类" 关系（"狗是动物"）
 * 
 * 继承的前提条件下，父子类之间的转换
 * 1.向上转型（自动类型转换）
 * 2.向下转型（强制类型转换）
 * 
 */

class Animal{};

class Dog:public Animal{};

class Cat:public Animal{};

void test1(){
    //用哪个对象，用相同类型的变量接收同类型的对象
    Animal animal;
    Dog dog1;
    Cat cat1;
    Dog &dog2=dog1;
    Cat &cat2=cat1;
    cout<<"------------------"<<endl;
    //使用继承后 满足 子类 is a 父类
    //子类可以当作父类来使用
    //可用使用父类接收子类
    Animal a1=dog1;
    Animal* a2=&dog1;
    Animal &a3=dog1;

    //如果反过来就不行
    //Dog dog3=animal; //动物是狗
    //如果两个类没有任何关系也不行
}

void handleDog(Dog &dog){
    //do sth
}
void handleCat(Cat &cat){
    //do sth
}

//可用复用的函数
void handleAnimal(Animal &animal){
    //do sth
}

void test2(){
    Dog dog;
    Cat cat;
    handleAnimal(dog);
    handleAnimal(cat);
}

//=====================================================

class GrandFather{
public:
    virtual void func(){}
    int m_gf=0;
};

class Father:public GrandFather
{
public:
    int m_f=1;
};

class Son : public Father
{
public:
    int m_s=2;
};

class GrandSon : public Son
{
public:
    int m_gs=3;
};

void test3(){
    //向上转型 用父类型指针接管子类型的内存空间
    Son son;
    Son *ps=&son;
    Father*pf=ps;//向上转型 自动类型转换 （狗是动物 自然成立）
    pf->m_f;
    //pf->m_s;//不能操作 
    //接到子类型的父类型指针 只能操作父类型中有的成员

    //========================================
    //向下转型 用子类型指针接管父类型的内存空间
    Father father;
    Father *f=&father;
    Son *s=(Son*)f;//向下转型 强制类型转换 （动物是狗 就有问题）
    s->m_f;
    s->m_s;//实际上f所指的父类型并没有这个东西
}

void test4(){
    //对象是Son 自身和父类们可以接收
    GrandFather *gf=new Son{};//用祖父类型指针接收自己 从而留出向下转型的空间
    //向下转型
    Father *f=dynamic_cast<Father*>(gf);
    if(f){
        cout<<"GrandFather* ----> Father"<<endl;
    }
    Son *s=dynamic_cast<Son*>(f);//最多转到自己这一辈
    if(s){
        cout<<"Father* ----> Son*"<<endl;
    }
    //--------------
    GrandSon *gs=dynamic_cast<GrandSon*>(s);//再往下 转换失败
    if(gs){
        cout<<"Son* ---->GrandSon*"<<endl;
    }
}

int main(int argc,char *argv[])
{
    test4();    
    return 0;
}

