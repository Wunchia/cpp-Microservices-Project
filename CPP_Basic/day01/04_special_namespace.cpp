#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 特色的命名空间：
 * 1.嵌套的命名空间
 * 2.匿名的命名空间
 *
 */

//嵌套的命名空间
//outer
namespace outer{
int num1 =1;
void func1(){
    cout<<"outer::func()"<<endl;
}

//inner
namespace inner{
    int num2=2;
    void func2(){
        cout<<"inner::func2()"<<endl;
    }
}//end of inner
}//end of outer

void test01(){
    //使用作用域限定符
    cout<<outer::num1<<endl;
    cout<<outer::inner::num2<<endl;
}

void test02(){
    //使用using声明机制
    using outer::num1;
    cout<<num1<<endl;
    using outer::inner::num2;
    cout<<num2<<endl;
}

void test03(){
    using namespace outer::inner;
    cout<<num2<<endl;
}

//匿名的命名空间
namespace {
    int number=100;
}

void test04(){
    //访问匿名的命名对象
    //可以直接使用
    cout<<number<<endl;
    //可以使用作用域限定符
    cout<<::number<<endl;
}

int main(int argc,char *argv[])
{
    test01();
    test02();
    test03();
    test04();
    return 0;
}

