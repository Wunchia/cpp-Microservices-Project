#include <iostream>
#include <deque>
#include <string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
//编写程序，从标准输入读取 string 序列，
//存入一个 deque 中。编写一个循环，
//用迭代器打印 deque 中的元素

void test(){
    deque<string> deq;
    string str;
    while(cin>>str){
        deq.push_back(str);
    }
    for(auto it=deq.begin();it!=deq.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}

