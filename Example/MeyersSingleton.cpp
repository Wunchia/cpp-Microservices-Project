#include <iostream>

class MeyersSingleton{
public:
    static MeyersSingleton& getInstance(){
        static MeyersSingleton instance;
        return instance;
    }
    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;
private:
    MeyersSingleton() = default;
    ~MeyersSingleton() = default;
};

int main(int argc,char *argv[])
{
    MeyersSingleton& instance1 = MeyersSingleton::getInstance();
    MeyersSingleton& instance2 = MeyersSingleton::getInstance();
    std::cout<<"instance1="<<&instance1<<std::endl;
    std::cout<<"instance2="<<&instance2<<std::endl;
    return 0;
}

