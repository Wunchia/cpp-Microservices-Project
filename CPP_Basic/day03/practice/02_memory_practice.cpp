#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class SizeTest{
    int a;
    char b;
    double c;
    void func(){}
};

void test2(){
    cout<<"对象大小："<<sizeof(SizeTest)<<endl;
}

int main(int argc,char *argv[])
{
    test2();    
    return 0;
}

