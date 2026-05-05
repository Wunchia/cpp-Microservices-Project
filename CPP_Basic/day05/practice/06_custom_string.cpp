#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class MyString{
public:
    MyString(const char* str=""){
        _data=new char[strlen(str)+1];
        strcpy(_data,str);
        cout<<"构造函数"<<endl;
    }

    MyString(const MyString& rhs){
        _data=new char[strlen(rhs._data)+1];
        strcpy(_data,rhs._data);
        cout<<"拷贝构造"<<endl;
    }

    MyString& operator=(const MyString& rhs){
        if(this!=&rhs){
            char*pTemp=new char[strlen(rhs._data)+1];
            strcpy(pTemp,rhs._data);
            delete[] _data;
            _data=pTemp;
            cout<<"赋值运算符"<<endl;
        }
        return *this;
    }

    ~MyString(){
        cout<<"析构函数"<<endl;
        delete[] _data;
    }
private:
    char* _data;
};

void test(){
   MyString str {"hello"};
   MyString str1(str);
   MyString str2="g++";
   str2=str;
}

int main(int argc,char *argv[])
{
    test(); 
    return 0;
}

