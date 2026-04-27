#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int num=100;
void funcA(){
    cout<<"funcA()"<<endl;
}


namespace wd{
    int number=100;
    void func(){
        cout<<"A::wd::func()"<<endl;
    }
}
