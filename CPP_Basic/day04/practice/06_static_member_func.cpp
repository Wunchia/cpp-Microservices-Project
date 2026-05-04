#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class FuncDemo{
public:
    int m_normal=10;
    static int m_static;

    void normalFunc(){
        cout<<m_normal<<" "<<m_static<<endl;
    }

    static void staticFunc(){
        cout<<"访问静态成员："<<m_static<<endl;
    }
};

int FuncDemo::m_static=20;

int main(int argc,char *argv[])
{
    FuncDemo f;
    f.normalFunc();
    FuncDemo::staticFunc();
    return 0;
}

