#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Data{
public:
    Data(int d=1)
    :_data(d)
    {
        cout<<"Data()"<<endl;
    }

    int getData()const{
        return _data;
    }

    ~Data(){
        cout<<"~Data()"<<endl;
    }
private:
    int _data;
};

class MiddleLayer{
public:
    MiddleLayer(Data* p)
    :_pdata(p)
    {
        cout<<"MiddleLayer(Data *)"<<endl;
    }

    ~MiddleLayer(){
        cout<<"~MiddleLayer()"<<endl;
        if(_pdata){
            delete _pdata;
            _pdata=nullptr;
        }
    }

    Data* operator->(){
        return _pdata;
    }

    Data& operator*(){
        return *_pdata;
    }

private:
    Data * _pdata;
};

class ThirdLayer{
public:
    ThirdLayer(MiddleLayer* pml)
    :_pml(pml)
    {
        cout<<"ThirdLayer(MiddleLayer *)"<<endl;
    }

    ~ThirdLayer(){
        cout<<"~ThirdLayer()"<<endl;
        if(_pml){
            delete _pml;
            _pml=nullptr;
        }
    }

    MiddleLayer& operator->(){
        return *_pml;
    }

    //operator*没有递归特性
    Data& operator*(){
        return **_pml;
    }

private:
    MiddleLayer* _pml;
};

int main(int argc,char *argv[])
{
    ThirdLayer t1{new MiddleLayer{new Data{100}}};

    cout<<"Data val through -> : "<<t1->getData()<<endl;
    cout<<"Data val through * : "<<(*t1).getData()<<endl;
    cout<<"-----End of Scope----"<<endl;
    
    return 0;
}

