#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Base{
public:
    Base(int val)
    :m_val(val){}

    void print(){
        cout<<m_val<<endl;
    }
private:
    int m_val;
};

class SpecialMember{
public:
    SpecialMember(int n,int& ref,int bval)
    :m_constData(n),
     m_refData(ref),
     m_objBase(bval)
    {}

    void print(){
        cout<<"constData:"<<m_constData<<endl;
        cout<<"refData:"<<m_refData<<endl;
        cout<<"objBase";
        m_objBase.print();
    }

private:
    const int m_constData;
    int &m_refData;
    Base m_objBase;
    static int m_staticData;
};

int SpecialMember::m_staticData=0;

int main(int argc,char *argv[])
{
    int a=4;
    cout<<"add of a:"<<&a<<endl;
    SpecialMember s1(2,a,1);
    s1.print();

    return 0;
}

