#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

void print(int i){
    cout<<"int:"<<i<<endl;
}

void print(double d){
    cout<<"double:"<<d<<endl;
}

void print(std::string s){
    cout<<"string:"<<s<<endl;
}

int main(int argc,char *argv[])
{
    print(10);
    print(3.14);
    print("hello overload");    
    return 0;
}

