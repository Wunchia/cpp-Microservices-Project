#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace wd{
int num=1;
void func(){
    cout << "wd::func()" <<endl;
}
}//end of wd

namespace zs{
int num=2;
void func(){
    cout << "zs::func()" <<endl;
}
}//end of zs

/*
 * 命名空间的使用
 *
 */


void test01(){
    //使用作用域限定符::
    cout<<zs::num<<endl;
    cout<<wd::num<<endl;
}

void test02(){
    //使用using声明机制
    using wd::num;
    cout<<num<<endl;
    using wd::func;
    func();
}

void test03(){
    //使用using编译指令
    using namespace wd;
    cout<<num<<endl;
    func();
}

int main(int argc,char *argv[])
{
    test01(); 
    test02();
    return 0;
}

