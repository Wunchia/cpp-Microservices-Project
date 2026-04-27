#include <iostream>
using std::cin;
using std::cout;
using std::endl;

inline int add(int a,int b){
    return a+b;
}

inline void show(int a);

void show(int a){
    cout<<"value:"<<a<<endl;
}

int main(int argc,char *argv[])
{
    show(add(5,5));
    return 0;
}

