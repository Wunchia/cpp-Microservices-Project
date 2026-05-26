#include <iostream>
#include <functional>
using namespace std;

/*
bind:包装可调用对象，绑定函数参数，返回一个新的可调用对象
该返回的可调用对象可以像普通函数一样被调用，绑定的参数会被自动填充
*/


int add(int a,int b){
    cout<<"a: "<<a<<" b: "<<b<<endl;
    return a+b;
}

void test1(){
    add(1,2);
    cout<<"-----------------"<<endl;
    //固定add函数中的参数 a=1 b=2
    //int(int.int)->int()
    auto f1=bind(add,1,2);
    cout<<f1()<<endl;
    
    cout<<"-----------------"<<endl;
    //std::placeholders::_1是占位符 表示第一个参数
    //std::placeholders::_2是占位符 表示第二个参数
    //参数取值取决于实际的参数顺序
    auto f2=bind(add,std::placeholders::_1,std::placeholders::_2);
    cout<<f2(3,4)<<endl;

    auto f3=bind(add,std::placeholders::_2,std::placeholders::_1);
    cout<<f3(3,4)<<endl;

    auto f4=bind(add,std::placeholders::_1,10);
    cout<<f4(4)<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

