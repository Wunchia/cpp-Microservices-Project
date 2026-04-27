#include <iostream>

extern int global_val;

namespace A{
    int val=10;
}

int main(int argc,char *argv[])
{
    std::cout<<"作用域限定符："<<A::val<<std::endl;

    using A::val;
    std::cout<<"using 声明："<<val<<std::endl;

    using namespace std;
    cout<<"extern 变量："<<global_val<<endl;
    
    return 0;
}

