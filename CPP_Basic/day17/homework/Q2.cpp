#include <iostream>
#include <type_traits>
using std::cin;
using std::cout;
using std::endl;

template <typename... Args>
auto sum(Args... args){
    static_assert(sizeof...(Args)>0,"at least one argument is required.");

    return (...+args);
}

int main(int argc,char *argv[])
{
    auto result=sum(1,2.5,3,4.2f);
    
    cout<<"Result:"<<result<<endl;
    cout<<"Type:"<<typeid(result).name()<<endl;

    return 0;
}

