#include <iostream>
#include <vector>
#include <string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//编写程序，从一个 vector<char> 初始化一个 string。

void test(){
    vector<char> vec{'a','b','c','d','e'};
    string str{vec.begin(),vec.end()};
    cout<<str<<endl;
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}

