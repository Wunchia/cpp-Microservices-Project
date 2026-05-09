#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 可调用实体：
 * 普通函数
 * 成员函数
 * 函数指针
 * 成员函数指针
 * 函数对象
 * lambda表达式
 * 
 * 函数对象：可以像函数一样调用的对象
 * 类中重载了operator()函数调用运算符的类
 * 
 * 使用场景：
 * 1.配合算法库使用
 * 2.函数对象的本质是对象，可以存储一些额外的数据
 *   并且这些数据的生命周期和对象是一致的
 * 
 */

class MyClass{
public:
    //operator()是函数调用运算符 后面的()才是参数列表
    void operator()(){
        cout<<"operator()()"<<endl;
    }

    void operator()(int num){
        cout<<"operator()(int)"<<endl;
        cout<<"num="<<num<<endl;
    }

    int operator()(int num1,int num2){
        cout<<"operator()(int,int)"<<endl;
        return num1+num2;
    }

private:
};


class MyClass2{
public:
    void operator()(){
        cout<<"operator()()"<<endl;
        count++;
    }

    void operator()(int num){
        cout<<"operator()(int)"<<endl;
        cout<<"num="<<num<<endl;
        count++;
    }

    int count=0;
};

void test1(){
    MyClass obj;
    //obj是个对象 但是可以像函数一样调用()
    obj(); //调用的是无参的那个函数

    //本质：
    // obj.operator()();

    obj(100);
    //本质：
    obj.operator()(100);

    int sum=obj(1,2);
    cout<<sum<<endl;
}

void test2(){
    int count=0;
}

void test3(){
    //访问不了 但如果用函数对象中存储的数据就可以跨生命周期访问
    //cout<<count<<endl; 
}

void test4(){
    MyClass2 obj;
    obj();
    obj(100);
    cout<<obj.count<<endl;
}

int main(int argc,char *argv[])
{
    // test1();
    test4();
    return 0;
}

