#include <iostream>
#include "stdio.h"

class A
{
public:
 void FuncA()
 {
     printf( "FuncA called\n" );
 }
 virtual void FuncB()
 {
     printf( "FuncB called\n" );
 }
};

class B 
: public A
{
public:
 void FuncA()
 {
     A::FuncA();
     printf( "FuncAB called\n" );
 }
    
 virtual void FuncB()
 {
     printf( "FuncBB called\n" );
 }
};

int main( void )
{
	B	b;
	A	*pa;
	pa = &b;
	A *pa2 = new A;
	pa->FuncA();//A中的funcA 普通成员函数根据指针类型调用
	pa->FuncB();//B中的funcB 触发覆盖
	pa2->FuncA(); //A中的funcA
	pa2->FuncB();//A中的funcB
	delete pa2;

	return 0;

}