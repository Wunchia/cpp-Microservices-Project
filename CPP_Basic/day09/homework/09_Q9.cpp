#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Base{
public:
    Base(int data)
    :m_data(data)
    {}

    int operator==(int data){
        if(this->m_data==data){
            return 0;
        }else{
            return 1;
        }
    }

    friend
    Base operator+(const Base&lhs,const Base& rhs);

    void print()const{
        cout<<m_data<<endl;
    }

private:
    int m_data;
};

Base operator+(const Base&lhs,const Base&rhs){
    return Base{lhs.m_data+rhs.m_data};
}

int main(int argc,char *argv[])
{
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout<<(x+y==j-i)<<endl;
    
    return 0;
}

