#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 保证某个类型的对象系统中只有1份，无论获取了多少次，
 * 拿到的始终是同一个对象
 * 
 * 单例设计模式的实现步骤：
 * 1.private修饰构造函数（构造函数私有）
 * 2.提供一个public函数，返回这个唯一的对象，类内创建单例对象后返回
 * 
 * 实现方式一：
 * 单例对象创建在静态区
 * 
 */

class Singleton{
public:
    static Singleton & getInstance(){
        //返回一个唯一的对象
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
private:
    Singleton(){}
};

void test1(){
    //从类外调用成员函数需要 对象.函数
    //但没有对象 所以无法 对象.函数
    //因此需要使用静态函数
    cout<<&Singleton::getInstance()<<endl;
    cout<<&Singleton::getInstance()<<endl;
    cout<<&Singleton::getInstance()<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

