#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class ThisPointer{
public:
    void compareAddress(){
        cout<<"this 指针的值："<<this<<endl;
    }
};

int main(int argc,char *argv[])
{
    ThisPointer obj1,obj2;
    cout<<"addr of obj1:"<<&obj1<<endl;
    obj1.compareAddress();
    
    cout<<"addr of obj2:"<<&obj2<<endl;
    obj2.compareAddress();
    return 0;
}

