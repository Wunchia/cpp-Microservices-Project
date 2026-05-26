#include <iostream>
#include <functional>
#include <map>
#include <string>
using namespace std;

class Calculator{
public:
    int add(int x,int y){
        return x+y;
    }

    int subtract(int x,int y){
        return x-y;
    }

    int multiply(int x,int y){
        return x*y;
    }
};

void test(){
    Calculator c;
    map<string,function<int(int,int)>> m_map;
    m_map["add"]=bind(&Calculator::add,&c,placeholders::_1,placeholders::_2);
    m_map["subtract"]=bind(&Calculator::subtract,&c,placeholders::_1,placeholders::_2);
    m_map["multiply"]=bind(&Calculator::multiply,&c,placeholders::_1,placeholders::_2);
    
    string op;
    while(cin>>op){
        if(op=="exit"){
            break;
        }
        int x,y;
        cin>>x>>y;
        cout<<m_map[op](x,y)<<endl;
    }
}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}

