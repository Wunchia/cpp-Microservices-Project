#include "person.pb.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace test;

int main(int argc,char *argv[])
{
    Person p1;
    p1.set_name("test");
    p1.set_id(100);
    p1.set_email("example@gmail.com");

    //序列化 将C++中的结构体保存到二进制序列中
    std::string output;
    p1.SerializeToString(&output);
    cout<<"size: "<<output.size()<<endl;
    cout<<"output: "<<output<<endl;

    //反序列化
    Person p2;
    cout<<"p2.name:"<<p2.name()
        <<", p2.id:"<<p2.id()
        <<", p2.email:"<<p2.email()<<endl;

    return 0;
}
