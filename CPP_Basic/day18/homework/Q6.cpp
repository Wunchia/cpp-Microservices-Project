#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Computer{
private:
    string _brand;
    double _price;
public:
    Computer(string brand,double price)
    :_brand(brand)
    ,_price(price)
    {
        cout<<"Computer(string,double)"<<endl;
    }
    ~Computer(){
        cout<<"~Computer()"<<endl;
    }
    void run()const{
        cout<<_price<<" 的 "<<_brand<<" is running"<<endl;
    }
};

template <typename T>
class SmartComputer{
private:
    T* _ptr;
public:
    explicit SmartComputer(T*p=nullptr)
    :_ptr(p)
    {}

    ~SmartComputer(){
        delete _ptr;
        cout<<"RAII类已销毁 资源已自动释放"<<endl;
    }

    SmartComputer(const SmartComputer&)=delete;
    SmartComputer&operator=(const SmartComputer&)=delete;

    T* operator->()const{
        return _ptr;
    }

    T& operator*()const{
        return *_ptr;
    }

    bool isValid()const{return _ptr!=nullptr;}
};

int main(int argc,char *argv[])
{
    cout<<"---------进入作用域----------"<<endl;
    {
        SmartComputer<Computer>myPC(new Computer{"Apple",19999});
        if(myPC.isValid()){
            myPC->run();
        }
    }
    cout<<"--------离开作用域-----------"<<endl;
    return 0;
}

