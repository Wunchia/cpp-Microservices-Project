#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Demo{
public:
    void show(){
        cout<<"非const调用"<<endl;
    }
    void show()const{
        cout<<"const调用"<<endl;
    }
    void onlyConst()const{
        cout<<"只有const版本"<<endl;
    }
};

void test1(){
    Demo d1;
    const Demo d2;

    d1.show();
    d2.show();

    d1.onlyConst();
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

