#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 多继承下，子类对象的创建和销毁过程
 */

class Father1{
public:
    Father1(){
        cout<<"Father1()"<<endl;
    }
    ~Father1(){
        cout<<"~Father1()"<<endl;
    }
    double m_f1=1;
};

class Father2{
public:
    Father2(){
        cout<<"Father2()"<<endl;
    }
    ~Father2(){
        cout<<"~Father2()"<<endl;
    }
    double m_f2=2;
};

//多继承
class Son
:public Father1
,public Father2
{
public:
    Son(){
        cout<<"Son()"<<endl;
    }
    ~Son(){
        cout<<"~Son()"<<endl;
    }
    double m_s=3;
};

void test1(){
    Son son;
    cout<<son.m_f1<<endl;    
    cout<<son.m_f2<<endl;    
    cout<<son.m_s<<endl;    
    cout<<sizeof(son)<<endl;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

