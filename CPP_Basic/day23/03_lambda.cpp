#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * lambda表达式 (本质是匿名函数对象)
    基本语法：
   [捕获列表](参数列表)opt -> 返回值类型{
    //函数体 do something
   }

   捕获列表：获取lambda表达式同一作用域内的局部变量
   参数列表：与普通函数参数列表相同
   opt：可选参数 一般不用
   ->返回值类型：与普通函数返回值类型相同
   函数体：与普通函数函数体相同
*/

void test1(){
    // 无参数无返回值的lambda表达式
    []()->void{
        cout<<"lambda1"<<endl;
    }(); //func();

    // 一次性的调用
    // 有参数无返回值的lambda表达式
    [](int num)->void{
        cout <<"num="<<num <<endl;
        cout<<"lambda2"<<endl;
    }(100); //func(100);

    // 有参数有返回值的lambda表达式
    int sum=[](int a,int b)->int{
        cout<<"lambda3"<<endl;
        return a+b;
    }(1,2); //int sum=func(1,2);
    cout<<"sum="<<sum<<endl;

    cout<<"-----"<<endl;
    sum=[](int a,int b){
        cout<<"lambda3"<<endl;
        return a+b;
    }(1,2); //int sum=func(1,2);
    cout<<"sum="<<sum<<endl;

    //捕获列表
    int num1=10;
    int num2=20;

    [num1,num2]()->void{
        cout<<"num1+num2="<<num1+num2<<endl;
    }();
}

//捕获列表规则
void test2(){
    int a=1;
    int b=2;
    //& ：按引用捕获
    [&]()->void{
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
        ++a;
        ++b;
    }();
    cout<<"-----"<<endl;
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;
}

// =：按值捕获
void test3(){
    int a=1;
    int b=2;
    //= ：按值捕获
    [=]()->void{
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
        //++a;//会报错
        //++b;//会报错
    }();
    cout<<"-----"<<endl;
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;
}

class MyClass{
public:
    //成员函数
    void func(){
        int a=10;
        //局部位置
        //捕获this指针，指向当前对象的地址
        // [this]()->void{
        // [=]()->void{
        [&]()->void{
            //如果使用的是 & 或者 =，默认捕获this指针
            cout<<a<<endl;
            cout<<"m_data="<<this->m_data<<endl;
            this->m_data=100;
        }();
    }

    int m_data=1;
};

void test4(){
    int a=1;
    int b=2;
    //按值捕获所有局部变量
    [=]()mutable->void{
        ++a;
        ++b;
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
    }();
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();
    return 0;
}

