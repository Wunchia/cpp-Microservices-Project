#include <iostream>

class EagerSingleton{
public:
    static EagerSingleton& getInstance(){
        return instance;
    }
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;
private:
    EagerSingleton() = default;
    ~EagerSingleton() = default;
    static EagerSingleton instance;
};

EagerSingleton EagerSingleton::instance;
int main(int argc,char *argv[]){
    EagerSingleton& instance1 = EagerSingleton::getInstance();
    EagerSingleton& instance2 = EagerSingleton::getInstance();
    std::cout<<"instance1="<<&instance1<<std::endl;
    std::cout<<"instance2="<<&instance2<<std::endl;
    return 0;
}