#include <iostream>
#include <functional>
using namespace std;

int func(int a,int b){
    cout<<"a: "<<a<<" b: "<<b<<endl;
    return a+b;
}

// 能否使用函数指针接收bind的返回结果
void test1(){
    func(1,2);
    cout<<"-----------------"<<endl;
    using F=int(*)(int,int);
    F f=func;
    f(1,2);
    //上下等价
    cout<<"-----------------"<<endl;
    int (*f1)(int,int)=&func;//用函数指针接收func函数
    f1(3,4);
    cout<<"-----------------"<<endl;

    // 能否使用函数指针接收bind的返回结果
    auto f2=bind(func,10,20);
    f2();
    cout<<"-----------------"<<endl;
    //函数指针只能接收同类型的函数，bind的返回结果是一个函数对象
    //f1=bind(func,100,200);//不能用函数指针接收bind的结果

    cout<<"-----------------"<<endl;
}

//function存普通函数
void test2(){
    // int func(int, int);
    // int (int,int)函数类型
    // 要保持函数的签名一致 返回值 形参要一致
    std::function<int(int,int)> f3=func;
    f3(1,2);
    cout<<"-----------------"<<endl;
    // int (int,int) ----> int()
    std::function<int()> f4=bind(func,1,2);
    f4();
}

//function存函数指针
void test3(){
    // int func(int, int);
    // int (int,int)函数类型
    // 要保持函数的签名一致 返回值 形参要一致
    std::function<int(int,int)> f3=&func;
    f3(1,2);
    cout<<"-----------------"<<endl;
    // int (int,int) ----> int()
    std::function<int()> f4=bind(&func,1,2);
    f4();
}

struct Callable
{
    void operator()(int a,int b){
        cout<<"a: "<<a<<" b: "<<b<<endl;
    }
};

//function 存储函数对象
void test4(){
    //void (int,int)函数类型
    function<void(int,int)>f1=Callable();
    f1(1,2);
    //使用bind改变函数形态
    //void (int,int) ----> void(int)
    function<void(int)>f2=bind(Callable(),1,std::placeholders::_1);
    f2(100);
}

//function存储lambda
void test5(){
    //void (int)函数类型
    function<void(int)>f1=bind([](int num)->void{
        cout<<"lambda"<<endl;
        cout<<num<<endl;
    },200);
    f1(100);//最后打印出的还是bind的数值
}

class MyClass
{
public:
    //成员函数
    void func(int a,int b){
        cout<<"a: "<<a<<" b: "<<b<<endl;
    }
};

//function存储类成员函数
void test6(){
    MyClass obj;
    obj.func(1,2);

    MyClass *p=&obj;
    p->func(1,2);
    cout<<"-----------------"<<endl;
    //void (MyClass &,int,int)函数类型
    //void (MyClass *,int,int)函数类型
    function<void(MyClass &,int,int)>f1=&MyClass::func;
    f1(obj,10,20);

    function<void(MyClass *,int,int)>f2=&MyClass::func;
    f2(&obj,10,20);

    //使用bind改变形态
    function<void(int,int)>f3=bind(&MyClass::func,obj,placeholders::_1,placeholders::_2);
    f3(100,200);

}



int main(int argc,char *argv[])
{
    //test1();    
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
    return 0;
}

