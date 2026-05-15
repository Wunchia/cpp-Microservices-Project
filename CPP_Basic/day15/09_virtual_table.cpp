#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Father{
public:
    virtual void func1(){
        cout<<"Father::func1()"<<endl;
    }
    
    virtual void func2(){
        cout<<"Father::func2()"<<endl;
    }

    virtual void func3(){
        cout<<"Father::func3()"<<endl;
    }

    long m_f=1;
};

class Son:public Father{
public:
    virtual void func1()override{
        cout<<"Son::func1()"<<endl;
    }
    
    virtual void func2()override{
        cout<<"Son::func2()"<<endl;
    }

    virtual void func3()override{
        cout<<"Son::func3()"<<endl;
    }

    virtual void func4(){
        cout<<"Son::func4()"<<endl;
    }

    long m_s=2;
};

void test1(){
    //验证Father
    Father father;
    long*f=(long*)&father;
    cout<<f[0]<<endl;
    cout<<f[1]<<endl;
    long* vftable=(long*)f[0];
    typedef void(*F)();
    F f1=(F)vftable[0];
    f1();
    f1=(F)vftable[1];
    f1();
    f1=(F)vftable[2];
    f1();
    cout<<f[2]<<endl;
    cout<<f[3]<<endl;
    cout<<"-------------"<<endl;
    //验证Son
    Son son;
    long*s=(long*)&son;
    cout<<s[0]<<endl;
    cout<<s[1]<<endl;
    cout<<s[2]<<endl;
    cout<<s[3]<<endl;
    long* s_vftable=(long*)s[0];
    typedef void(*S)();
    S f2=(S)s_vftable[0];
    f2();
    f2=(S)s_vftable[1];
    f2();
    f2=(S)s_vftable[2];
    f2();
    cout<<s[4]<<endl;
    cout<<s[5]<<endl;
    cout<<"----------------------"<<endl;
    Son son_t;
    Father *fa_t=(Father*)&son;
    long* f_from_s=(long*)fa_t;
    cout<<f_from_s[0]<<endl;
    cout<<f_from_s[1]<<endl;
    cout<<f_from_s[2]<<endl;
    cout<<f_from_s[3]<<endl;
    cout<<f_from_s[4]<<endl;
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}

