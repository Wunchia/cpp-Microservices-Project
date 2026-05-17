#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Base
{
public:
	Base(int i) 
	{
		b = i;
	}
    
    Base():b(0){}
    virtual void Print()
    {	cout << "Base 's Print() called." << endl;}
protected:
	int b;
};

class Derived1
:public Base
{
public:
    virtual
	void Print()override
	{
		cout<<"Derived1's Print() called."<<endl;
	}
};

class Derived2
:public Base
{
public:
    virtual
    void Print()override
    {
        cout << "Derived2's Print() called. "<< endl;
    }
};

void fun(Base * obj)
{      
	obj->Print();
}

int main(void)
{ 
    Derived1 d1;
    Derived2 d2;
    fun(&d1);
    fun(&d2);
	return 0;
}
//程序的执行结果如下：
//Derived1's Print() called.
//Derived2's Print() called.


