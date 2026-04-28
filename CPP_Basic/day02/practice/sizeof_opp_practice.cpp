#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Empty{};
class Base{
    int a;// 4 bytes
    char b;// 1 bytes -> 对齐到4
};

int main(int argc,char *argv[])
{
    cout<<"空类大小："<<sizeof(Empty)<<endl;
    cout<<"普通类大小："<<sizeof(Base)<<endl;    
    return 0;
}

