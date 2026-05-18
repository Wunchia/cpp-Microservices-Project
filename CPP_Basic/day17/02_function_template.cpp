#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 把模板作用在函数上： 函数模板
 * 
 * 基本语法：
 * template <typename/class T,typename U,typename K>
 * template:关键字
 * T/U/K：模板参数（类型参数），一种通用类型
 * 这个字母使用什么无所谓，就是一个“代号”
 * 通常一般会用：
 * T：type  
 * K：key 
 * V：value
 * E：element
 * 尽量不要使用XYZ像这样的命名
 * 
 */

// 函数声明 和 实现写在一起的
template <typename T>
void print(T t){

}

void test1(){
    //显式实例化 指明具体类型是啥
    print<int>(100);
    print<double>(3.14);

    cout<<"----------"<<endl;
    //隐式实例化
    print(10);
    print(3.14);
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

