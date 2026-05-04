#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class AssignDemo{
public:
    AssignDemo(const char* s){
        m_str=new char[strlen(s)+1];
        strcpy(m_str,s);
    }

    AssignDemo& operator=(const AssignDemo& rhs){
        if(this==&rhs){
            return *this;
        }
        delete[] m_str;
        m_str=new char[strlen(rhs.m_str)+1];
        strcpy(m_str,rhs.m_str);
        return *this;
    }

    void print(){
        cout<<"m_str:"<<m_str<<endl;
    }

    ~AssignDemo(){
        delete[] m_str;
    }
private:
    char* m_str;
};

int main(int argc,char *argv[])
{
    AssignDemo D1("hello");
    AssignDemo D2("world");
    AssignDemo D3("C++");
    D3=D2=D1;
    D1.print();
    D2.print();
    D3.print();
    return 0;
}

