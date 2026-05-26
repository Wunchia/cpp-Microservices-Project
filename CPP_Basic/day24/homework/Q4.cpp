#include <iostream>
#include <functional>
using namespace std;

class Calculator{
public:
    int add(int x,int y){
        return x+y;
    }
};

void test1(){
    Calculator c;
    function<int(int)> c1=bind(&Calculator::add,&c,10,placeholders::_1);
    cout<<c1(2)<<endl;
    cout<<"------------"<<endl;
    function<int(int)> c2=bind(&Calculator::add,&c,placeholders::_1,20);
    cout<<c2(3)<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

