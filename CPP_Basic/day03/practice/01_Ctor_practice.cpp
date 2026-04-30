#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    Computer():_brand("Unknown"),_price(0){
        cout<<"无参构造"<<endl;
    }
    Computer(std::string brand,double price=5000)
    : _brand(brand),_price(price){
        cout<<"多参构造"<<endl;
    }

    void print(){cout<<_brand<<" "<<_price<<endl;}
private:
    std::string _brand;
    double _price;
};

void test1(){
    Computer c1;
    c1.print();
    Computer c2("Apple",9999);
    c2.print();
    Computer c3("Dell");
    c3.print();
}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

