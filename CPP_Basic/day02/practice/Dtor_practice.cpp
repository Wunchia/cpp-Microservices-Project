#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class StringModel{
public:
    //构造函数：分配堆内存
    StringModel(const char *pstr){
        cout<<"构造函数：申请内存"<<endl;
        _pstr=new char[strlen(pstr)+1];
        strcpy(_pstr,pstr);
    }

    //拷贝构造函数
    StringModel(const StringModel& other){
        cout<<"拷贝构造函数：执行深拷贝"<<endl;
        _pstr=new char[strlen(other._pstr)+1];
        strcpy(_pstr,other._pstr);
    }

    //析构函数：释放堆内存
    ~StringModel(){
        if(_pstr){
            delete[] _pstr;
            _pstr= nullptr;
            cout<<"析构函数：释放内存"<<endl;
        }
    }

    void print(){cout<<_pstr<<endl;}
private:
    char *_pstr;
};

void testTiming(){
    cout<<"------局部对象------"<<endl;
    StringModel s1("LocalObj");
    StringModel s2=s1;
    //s1 离开作用域会自动析构
}

int main(int argc,char *argv[])
{
    testTiming();

    cout<<"\n----堆对象----"<<endl;
    StringModel* s2=new StringModel("HeapObj");
    cout<<"---观察点----"<<endl;
    delete s2;
    return 0;
}

