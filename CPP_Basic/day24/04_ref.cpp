#include <iostream>
#include <functional>
using namespace std;

/*
std::ref------>引用包装器
*/

void func(int a,int & b,const int c){
    a++;
    b++;
    //c++;
    cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<endl;
}

void test1(){
    int a=1;
    int b=2;
    int c=3;
    //bind的传值方式默认是值传递
    //如果要传递引用，需要使用引用包装器
    //std::ref  /  std::cref
    auto f=bind(func,a,std::ref(b),c);
    f();
    cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<endl;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

