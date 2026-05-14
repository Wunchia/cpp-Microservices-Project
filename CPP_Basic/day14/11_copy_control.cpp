#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 *
 *
 * 
 */

class Father
{
public:
    Father(int f)
    :m_f(f)
    {
        cout<<"Father(int)"<<endl;
    }
    int m_f;
};

class Son:public Father
{
public:
    Son(int f,int s)
    :Father(f)
    ,m_s(s)
    {
        cout<<"Son(int int)"<<endl;
    }
    int m_s;
};

void test1(){
    Son s1{1,2};
    cout<<s1.m_f<<endl;
    cout<<s1.m_s<<endl;
    cout<<"--------"<<endl;
    //对象复制
    Son s2=s1;//调用拷贝构造
    cout<<s2.m_f<<endl;
    cout<<s2.m_s<<endl;
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

