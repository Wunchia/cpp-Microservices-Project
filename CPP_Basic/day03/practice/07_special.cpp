#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class SubObject{
public:
    SubObject(int a){
        cout<<"SubObject构造"<<endl;
    }
};

class Special{
public:
    Special(int v,int& ref,int subV)
    : _cVal(v)
    , _refVal(ref)
    , _sub(subV)
    {}

private:
    const int _cVal;
    int &_refVal;
    SubObject _sub;
    static int _staticVal;
};

int Special::_staticVal=100;

void test(){
    int x=10;
    Special s(1,x,5);
}

int main(int argc,char *argv[])
{
    test();
    return 0;
}

