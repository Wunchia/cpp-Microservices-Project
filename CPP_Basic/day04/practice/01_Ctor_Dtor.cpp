#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class Demo{
public:
    Demo(int id,const char*name)
    :m_id(id){
        m_name=new char[strlen(name)+1];
        strcpy(m_name,name);
        cout<<"构造对象："<<m_id<<"["<<m_name<<"]"<<endl;
    }

    ~Demo(){
        delete[] m_name;
        cout<<"析构对象："<<m_id<<endl;
    }

private:
    int m_id;
    char* m_name;
};

void test(){
    Demo d1{1,"local_1"};
    Demo d2{2,"lobal_2"};
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}

