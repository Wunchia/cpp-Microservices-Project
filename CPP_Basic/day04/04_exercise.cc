#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class Computer
{
public:
    //构造函数
    Computer(const char *brand, int price)
    : m_brand(new char[strlen(brand) + 1]{})
    , m_price(price)
    {
        cout << "constructor" << endl;
        strcpy(m_brand, brand);
    }

    //拷贝构造
    Computer(const Computer &rhs)
    : m_brand(new char[strlen(rhs.m_brand) + 1]{})
    , m_price(rhs.m_price)
    {
        strcpy(m_brand, rhs.m_brand);
        cout << "deep copy constructor" << endl;
    }

    //赋值运算符
    Computer& operator=(const Computer&rhs){
        cout<<"operator="<<endl;
        if(this==&rhs){
            return *this;
        }
        delete[]this->m_brand;
        this->m_brand=new char[strlen(rhs.m_brand)+1]{};
        strcpy(this->m_brand,rhs.m_brand);
        this->m_price=rhs.m_price;
        return *this;
    }

    //析构函数
    ~Computer()
    {
        if(m_brand){
            delete[] m_brand;
            m_brand = nullptr;
        }
        cout << "destructor" << endl;
    }

    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }

private:
    char *m_brand;
    int m_price;
};

void test1()
{
    Computer pc1{"xiaomi", 1999};
    Computer pc2 = pc1;
    pc1.print();
    pc2.print();
}

void test2(){
    Computer pc1{"xiaomi",1999};
    Computer pc2{"huawei",6999};
    pc1.print();
    pc2.print();
    pc2=pc1;//编译器自动添加的赋值运算符重载是浅拷贝，会double free
    pc1.print();
    pc2.print();
}

int main(int argc, char *argv[])
{
    // test1();
    test2();
    return 0;
}
