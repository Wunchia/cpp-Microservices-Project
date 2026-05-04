#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class ConstDemo{
public:
    void display(){
        cout<<"调用：普通成员函数："<<endl;
    }

    void display()const{
        cout<<"调用：const成员调用："<<endl;
    }
};

int main(int argc,char *argv[])
{
    ConstDemo obj;
    obj.display();

    const ConstDemo cobj;
    cobj.display();

    return 0;
}

