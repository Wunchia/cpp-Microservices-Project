#include <iostream>
#include <string>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//定义一个字符数组类CharArray

class CharArray{
public:
    CharArray(const char* pstr)
   :m_pstr(new char[strlen(pstr)+1]{})
   ,m_size(strlen(pstr))
    {
        cout<<"constructor"<<endl;
        strcpy(m_pstr,pstr);
    }

    void print()const{
        cout<<m_pstr<<endl;
    }

    //operator[] 重载
    char& operator[](size_t index){
        if(index<0||index>=m_size){
            // throw "index is illegal";
            static char NullChar='\0';
            return NullChar;
        }
        return this->m_pstr[index];
    }

    ~CharArray(){
        if(m_pstr){
            delete[] m_pstr;
            m_pstr=nullptr;
        }
    }

private:
    char* m_pstr;
    int m_size;
};


void test1(){
    string str="abc";
    cout<<str[0]<<endl;
    cout<<str[1]<<endl;
    cout<<str[2]<<endl;
    cout<<"----------"<<endl;
    cout<<str.operator[](2)<<endl;
}


void test2(){
    CharArray ch{"abcd"};
    ch.print();
    cout<<ch[0]<<endl;
    ch[0]='A';
    cout<<ch[0]<<endl;
}

int main(int argc,char *argv[])
{
    test2();    
    return 0;
}

