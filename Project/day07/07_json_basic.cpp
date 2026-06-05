#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json=nlohmann::json;

int main(int argc,char *argv[])
{
    //解析文件
    ifstream f("example.json");
    json j1=json::parse(f);//反序列化操作
    // cout<<j1.dump()<<endl;//序列化
    cout<<j1.dump(2)<<endl;//序列化

    //解析字符串（裸字符串）
    json j2=json::parse(R"({
        "pi":3.14,
        "hello":"world"
        })");
    cout<<j2.dump(2)<<endl;
    return 0;
}
