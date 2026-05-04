#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class CopyDemo{
public:
    CopyDemo(const char* data){
        m_data=new char[strlen(data)+1];
        strcpy(m_data,data);
    }

    CopyDemo(const CopyDemo& other){
        m_data=new char[strlen(other.m_data)+1];
        strcpy(m_data,other.m_data);
        cout<<"深拷贝构造"<<endl;
    }
    void print(){
        cout<<"data:"<<m_data<<endl;
    }
    ~CopyDemo(){
        delete[] m_data;
    }
private:
    char* m_data;
};

int main(int argc,char *argv[])
{
    CopyDemo t1("hello");
    CopyDemo t2(t1);
    t2.print();
    return 0;
}

