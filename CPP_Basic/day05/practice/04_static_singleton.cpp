#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class StaticSingleton{
public:
    static StaticSingleton& getInstance(){
        static StaticSingleton instance;
        return instance;
    }
    void print()const{
        cout<<"i am singleton"<<endl;
    }
private:
    StaticSingleton(){}
    StaticSingleton(const StaticSingleton&)=delete;
    StaticSingleton& operator=(const StaticSingleton&)=delete;
};

void test(){
    StaticSingleton& instance=StaticSingleton::getInstance();
    instance.print();
}

int main(int argc,char *argv[])
{
    test();
    return 0;
}

