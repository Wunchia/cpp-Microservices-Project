#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void testFunc(int a,int b=10,int c=20){
    cout<<a<<" "<<b<<" "<<c<<endl;
}

int main(int argc,char *argv[])
{
    testFunc(1);
    testFunc(1,2);
    testFunc(1,2,3);    
    return 0;
}

