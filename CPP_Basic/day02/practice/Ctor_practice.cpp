#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    //1.无参构造
    Computer() : _brand("Unknown"), _price(0){
        cout<<"无参构造被调用"<<endl;
    }

    //2.多参构造+初始化列表+参数默认值
    Computer(std::string brand,float price=5000.0)
    : _brand(brand), _price(price){
        cout<<"有参构造被调用："<<_brand<<endl;
    }
private:
    std::string _brand;
    float _price;
};

int main(int argc,char *argv[])
{
    Computer c1;
    Computer c2("MacBook");
    Computer c3("Alienware",20000); 
    return 0;
}

