#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 类中权限修饰符
 * 1.public
 * 2.private：在类的内部可以访问，类的外部不可访问
 * 3.protected
 *
 */

class MyClass{
public:
    int data1;
    void func1(){
        cout<<"func1()"<<endl;
        cout<<data2<<endl;
    }
private:
    int data2;
    void func2(){
        cout<<"func2()"<<endl;
    }
};

void test1(){

    MyClass obj;
    obj.data1;
    // obj.data2;//private不能外部访问
    obj.func1();
    // obj.func2();//private不能外部访问
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

