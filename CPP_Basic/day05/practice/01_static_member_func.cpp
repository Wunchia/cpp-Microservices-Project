#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Base{
public:
    int _a=10;
    static int _s_val;
    //普通成员函数
    void normalFunc(){
        cout<<"访问非静态成员："<<_a<<endl;
        cout<<"访问静态成员："<<_s_val<<endl;
    }
    //静态成员函数
    static void staticFunc(){
        cout<<"静态函数访问静态成员："<<_s_val<<endl;
    }
};

int Base::_s_val=100;

int main(int argc,char *argv[])
{
    Base obj;
    obj.normalFunc();
    Base::staticFunc();
    return 0;
}

