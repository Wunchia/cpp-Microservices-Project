#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class Book{
public:
    Book(const char*name){
        cout<<"构造："<<name<<endl;
        _name=new char[strlen(name)+1];
        strcpy(_name,name);
    }

    ~Book(){
        cout<<"析构："<<_name<<endl;
        delete[] _name;
    }
private:
    char* _name;
};

void test3(){
    Book b1("C++ Primer");
    Book*b2=new Book("Inside the C++ Object Model");
    delete b2;
}

int main(int argc,char *argv[])
{
    test3();
    return 0;
}

