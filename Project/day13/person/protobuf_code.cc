#include "person.pb.h"
#include <iostream>
#include <bitset>

using namespace std;
using namespace test;

int main(int argc,char *argv[])
{
    Person p;
    p.set_id(100);
    p.set_name("aaa");
    string data;
    p.SerializePartialToString(&data);
    cout<<"size:"<<data.size()<<endl;

    for(auto c:data){
        cout<<bitset<8>(c)<<" ";
    }
    cout<<endl;

}
