#include <iostream>
#include <map>
#include <string>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;

void visitMap(map<string,int> m){
    for(auto &p:m){
        cout<<"name:"<<p.first<<" age:"<<p.second<<" | ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    map<string,int> m;
    m.insert(
        {
            {"张三",20},
            {"李四",22},
        }
    );    
    
    auto result=m.find("张三");
    cout<<result->second<<endl;

    m["李四"]=24;

    m["王五"]=25;

    visitMap(m);

    return 0;
}

