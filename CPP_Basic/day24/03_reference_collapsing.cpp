#include <iostream>
using std::cin;
using std::cout;
using std::endl;

using namespace std;

/*
万能引用
void func(T && t) : ---> T && t 万能引用
既可以接收左值 又可以接收右值

引用折叠规则：
1.T &  &t 
2.T &&  &t 
3.T &  &&t 
4.T &&  &&t 
只要有左值引用参与 ----> 折叠为左值引用
*/

template< typename T>
void func(T&t){
    cout<<"func(T&t)"<<endl;
}

template <typename T>
void func2(T&&t){
    cout<<"func2(T&&t)"<<endl;
}

void test1(){
    int num=1;//左值
    func(num);// T= int & ----> int & &---->int &
    //func(1);error T= int&& --->int && &--->int &
    cout<<"-----------------"<<endl;
    func2(num);// T= int & ----> int & &&---->int &
    func2(1);// T= int && --->int && &&--->int &&
   }

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

