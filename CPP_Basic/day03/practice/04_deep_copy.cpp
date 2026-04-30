#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class String{
public:
    String(const char*pstr){
        _pstr=new char[strlen(pstr)+1];
        strcpy(_pstr,pstr);
    }

    String(const String&rhs){
        _pstr=new char[strlen(rhs._pstr)+1];
        strcpy(_pstr,rhs._pstr);
        cout<<"调用深拷贝构造"<<endl;
    }

    ~String(){
        cout<<"调用析构"<<endl;
        delete[] _pstr;
    }
private:
    char* _pstr;
};

void test(){
    String s1("hello");
    String s2{s1};
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}

