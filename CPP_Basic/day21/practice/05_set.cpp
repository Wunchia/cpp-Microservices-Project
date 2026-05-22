#include <iostream>
#include <set>
#include <string>

using std::set;
using std::multiset;
using std::string;
using std::cin;
using std::cout;
using std::endl;

struct NetRequest{
    int req_id;
    int priority;

    //方式一：内部重载 operator<
    bool operator<(const NetRequest &other) const{
        if(this->priority!=other.priority){
            return this->priority>other.priority;
        }
        return this->req_id<other.req_id;
    }
};

//方式二：外部仿函数
struct CompareByID{
    bool operator()(const NetRequest&lhs,const NetRequest&rhs) const{
        return lhs.req_id<rhs.req_id;
    }
};

void practiceSetFamily(){
    cout<<"========set & multiset practice========"<<endl;
    set<NetRequest> requests;
    requests.insert({1001,5});
    requests.insert({1002,10});//最高优先级
    requests.insert({1003,2});//最低优先级
    requests.insert({1004,5});

    cout<<"自动按优先级（降序）处理的请求队列："<<endl;
    for(const auto&req:requests){
        cout<<"Priority:"<<req.priority<<" ReqID:"<<req.req_id<<endl;
    }

    multiset<int> thresholds{10,20,20,20,30,40,50};
    cout<<"\nMultiset thresholds测试:10,20,20,20,30,40,50"<<endl;

    //lower_bound()：返回第一个大于等于指定值的迭代器
    auto it_low=thresholds.lower_bound(20);
    //upper_bound()：返回第一个大于指定值的迭代器
    auto it_up=thresholds.upper_bound(20);
    cout<<"lower_bound(20)指向:"<<*it_low<<endl;
    cout<<"upper_bound(20)指向:"<<*it_up<<endl;

    cout<<"区间内所有20:";
    for(auto it=it_low;it!=it_up;++it){
        cout<<""<<*it;
    }
    cout<<endl;

    cout<<"---------------------"<<endl;
    //equal_range()：返回所有等于指定值的迭代器范围
    auto range=thresholds.equal_range(20);
    cout<<"区间内所有20(through equal_range):";
    for(auto it=range.first;it!=range.second;++it){
        cout<<""<<*it;
    }
    cout<<endl;

    thresholds.erase(it_low,it_up);
    cout<<"删除20后，thresholds的大小为:"<<thresholds.size()<<endl;
}


int main(int argc,char *argv[])
{
    practiceSetFamily();
    return 0;
}

