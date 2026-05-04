#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Computer{
    void destroy(){
        delete this;
    }
private:
    ~Computer(){
        cout<<"~Computer"<<endl;
    }
};

int main(int argc,char *argv[])
{
    // Computer c1;
    Computer* p=new Computer();
    return 0;
}

