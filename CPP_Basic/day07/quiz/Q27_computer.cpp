#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char* brand,double price)
    :_brand(new char[strlen(brand)+1])
    ,_price(price)
    {
        strcpy(_brand,brand);
    }

    Computer(const Computer& rhs)
    :_brand(new char[strlen(rhs._brand)+1])
    ,_price(rhs._price)
    {
        strcpy(_brand,rhs._brand);
    }

    Computer& operator=(const Computer& rhs){
        if(this!=&rhs){
            char *temp=new char[strlen(rhs._brand)+1];
            strcpy(temp,rhs._brand);
            delete[]_brand;
            _brand=temp;
            _price=rhs._price;
        }
        return *this;
    }

    void print()const{
        cout<<_brand<<" "<<_price<<endl;
    }

    ~Computer(){
        delete[]_brand;
        _brand=nullptr;
    }
private:
    char* _brand;
    double _price;
};

int main(int argc,char *argv[])
{
    Computer c1("hp",5999);
    Computer c2("macbook",8999);
    Computer c3(c2);
    c1.print();
    c2.print();
    c3.print();
    c3=c1;
    c3.print();

    return 0;
}

