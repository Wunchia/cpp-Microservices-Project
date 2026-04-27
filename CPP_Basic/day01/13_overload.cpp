#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 函数重载（overload）：
 * 同一作用域内，函数名相同，形参列表不同的一组函数
 *
 * 构成函数重载的条件：形参列表不同
 *      通过函数的参数个数区分
 *      个数相同，通过函数的参数类型区分
 *      个数、类型相同，通过参数位置不同区分
 *
 * 注意！！！！！！！
 * 函数重载和返回值没有任何关系
 *
 */

void addInt(int a,int b){
    cout<<a+b<<endl;

}

void addDouble(double a,double b){
    cout<<a+b<<endl;
}

void add(int a,int b){
    cout<<"add(int,int)"<<endl;
}

void add(double a,double b){
    cout<<"add(double,double)"<<endl;
}

void test1(){
    add(3,4);
    add(3.14,5.12);
}

void print(){
    cout<<"print()"<<endl;
}

void print(int a){
    cout<<"print(int)"<<endl;
}

void test2(){
    print();
    print(100);
}

void print3(int a,double b){
    cout<<"printf3(int,double)"<<endl;
}


void print3(double a,int b){
    cout<<"printf3(double,int)"<<endl;
}

void test4(){
    print3(3,4.5);
    print3(3.14,5);
}

//特殊的：二义性问题
void test05(){
    //两个print3都可以接收这两个值
    /* print3(100,100); error:模糊匹配 */
}

//如果某段代码希望以C的方式编译
extern "C"{
    void func(){}
    //C中不支持函数重载
    /* void func(int a){} */
}

int main(int argc,char *argv[])
{
    test1();
    test2();
    test4();
    
    return 0;
}

