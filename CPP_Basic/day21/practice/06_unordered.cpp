#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <functional>
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::hash;
using std::cin;
using std::cout;
using std::endl;

struct TcpEndpoint{
    string ip;
    uint16_t port;

    bool operator==(const TcpEndpoint&rhs)const{
        return ip==rhs.ip&&port==rhs.port;
    }
};

//==========方法一：定义独立的哈希仿函数============
struct EndpointHash{
    size_t operator()(const TcpEndpoint&ep)const{
        size_t ip_hash=hash<string>{}(ep.ip);
        size_t port_hash=hash<uint16_t>{}(ep.port);
        //得到最终的哈希值
        return ip_hash^(port_hash+0x9e3779b9+(ip_hash<<6)+(ip_hash>>2));
    }
};

//==========方法二：偏特化hash模板============
namespace std{
    template<>
    struct hash<TcpEndpoint>{
        size_t operator()(const TcpEndpoint&ep)const{
            return EndpointHash{}(ep);
        }
    };
}

void practiceUnorderedCustomTypes(){
    cout<<"======自定义类型的三种哈希处理方法======"<<endl;

    unordered_set<TcpEndpoint,EndpointHash> activeNodes1;
    activeNodes1.insert({"127.0.0.1",8080});

    unordered_set<TcpEndpoint> activeNodes2;
    activeNodes2.insert({"10.0.0.1",443});

    auto lambdaHash=[](const TcpEndpoint&ep){
        return hash<string>{}(ep.ip)^hash<uint16_t>{}(ep.port);
    };
    unordered_set<TcpEndpoint,decltype(lambdaHash)> activeNodes3(10,lambdaHash);
    activeNodes3.insert({"172.16.0.5",22});

    cout<<"三种方式均成功插入自定义类型"<<endl;
}

void practiceUnorderedInternals(){
    cout<<"======哈希表 桶与扩容======"<<endl;

    unordered_map<TcpEndpoint,string> connectionPool;

    connectionPool.reserve(100);

    connectionPool[{"127.0.0.1",8080}]="Session_A";
    connectionPool[{"192.168.1.11",80}]="Session_B";
    connectionPool[{"10.0.0.1",443}]="Session_C";

    //
    cout<<"当前负载因子："<<connectionPool.load_factor()<<endl;
    cout<<"最大允许负载因子："<<connectionPool.max_load_factor()<<endl;
    cout<<"当前桶数："<<connectionPool.bucket_count()<<endl;

    cout<<"---底层哈希冲突与链表分布探测---"<<endl;
    for(unsigned i=0;i<connectionPool.bucket_count();i++){
        if(connectionPool.bucket_size(i)>0){
            cout<<"桶"<<i<<"有"<<connectionPool.bucket_size(i)<<"个元素"<<endl;
            //遍历单条链表(bucket内部的迭代器是local_iterator)
            for(auto it=connectionPool.begin(i);it!=connectionPool.end(i);it++){
                cout<<"   ->ip: "<<it->first.ip<<", session: "<<it->second<<endl;
            }
        }
    }
}

int main(int argc,char *argv[])
{
    practiceUnorderedCustomTypes();
    practiceUnorderedInternals();
    return 0;
}

