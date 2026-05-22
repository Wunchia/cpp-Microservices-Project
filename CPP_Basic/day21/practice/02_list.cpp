#include <iostream>
#include <list>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;

struct ClientSession{
    int fd;
    string ip;

    bool operator<(const ClientSession &other)const{
        return fd<other.fd;
    }
};

void practiceList(){
    cout<<"=========List Practice=========="<<endl;

    list<ClientSession> session;
    session.push_back({102,"127.0.0.1"});
    session.push_front({101,"127.0.0.2"});
    session.insert(++session.begin(),{103,"127.0.0.3"});

    for(auto &e:session){
        if(e.fd==101){
            e.ip="127.0.0.4";
        }
    }

    //list的独有算法
    session.sort();

    cout<<"排序后的session:"<<endl;
    for(auto &e:session){
        cout<<e.fd<<" "<<e.ip<<endl;
    }

    //迭代器失效测试
    auto it_first=session.begin();
    auto it_second=++session.begin();

    session.erase(it_first);

    cout<<"it_first:"<<it_first->ip<<endl;
    //cout<<++it_first->ip<<endl; //it_first已失效
    cout<<"first session:"<<session.begin()->ip<<endl;
    cout<<"second session:"<<it_second->ip<<endl;
}

int main(int argc,char *argv[])
{
    practiceList(); 
    return 0;
}

