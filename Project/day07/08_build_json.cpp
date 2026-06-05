#include <iostream>
#include <nlohmann/json.hpp>
using namespace std;
using json=nlohmann::json;

int main(int argc,char *argv[])
{
    //1.基本数据类型
    json j1;
    cout<<j1.dump()<<endl;//null

    json j2=false;
    cout<<j2.dump()<<endl;//false

    json j3=2.67;
    cout<<j3.dump()<<endl;//2.67

    json j4="蓝蓝";
    cout<<j4.dump()<<endl;//"蓝蓝"

    // 2.初始化列表
    // 数组
    json j5={"vincio","loves","lanlan",520};
    cout<<j5.dump(2)<<endl;
    // 对象
    json j6={
        {"name","vincio"},
        {"age",18}
    };
    cout<<j6.dump(2)<<endl;

    // 3.解决歧义
    // null
    json j7;

    // ""
    json j8="";

    // []
    // json j9={};//是null
    json j9=json::array();
    cout<<j9.dump(2)<<endl;

    // {}
    // json j10={};//也是null
    json j10=json::object();
    cout<<j10.dump(2)<<endl;

    //如何表示二维数组
    // [["currency","USD"],["value",42.99]]
    json d1={{"currency","USD"},{"value",42.99}};
    cout<<d1.dump(2)<<endl;//d1是对象
    json d2=json::array({{"currency","USD"},{"value",42.99}});
    cout<<d2.dump(2)<<endl;//d2才是数组

    //4.动态构建 json
    json d4; //null
    d4["pi"]=3.1415926;
    d4["happy"]=true;
    d4["name"]="Niels";
    d4["nothing"]=nullptr;
    d4["answer"]["everything"]=42;
    d4["list"]={1,0,2};
    d4["object"]={{"currency","USD"},{"value",42.99}};

    cout<<d4.dump(2)<<endl;

    return 0;
}
