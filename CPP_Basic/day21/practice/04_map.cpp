#include <iostream>
#include <map>
#include <string>

using std::map;
using std::multimap;
using std::string;
using std::cin;
using std::cout;
using std::endl;

void practiceMapFamily(){
    cout<<"========map & multimap practice========"<<endl;

    map<string,string> userSession;
    userSession["admin"]="session_1001";

    // auto ret=userSession.insert({"guest","session_1002"});
    auto ret=userSession.insert({"admin","session_1002"});
    if(ret.second){
        cout<<"插入成功"<<endl;
    }else{
        cout<<"插入失败"<<endl;
    }

    cout<<"size of map:"<<userSession.size()<<endl;
    if(userSession["unknown_user"]==""){
        cout<<"now size of map:"<<userSession.size()<<endl;
    }

    auto it=userSession.find("admin");
    if(it!=userSession.end()){
        cout<<"admin session:"<<it->second<<endl;
    }

    userSession.erase("unknown_user");

    //multimap
    multimap<string,int> userFiles;
    userFiles.insert({"user_A",101});
    userFiles.insert({"user_A",102});
    userFiles.insert({"user_B",201});
    userFiles.insert({"user_A",103});

    cout<<"user_A 拥有的文件块数量:"<<userFiles.count("user_A")<<endl;
    cout<<"user_B 拥有的文件块数量:"<<userFiles.count("user_B")<<endl;

    cout<<"遍历 user_A 拥有的文件块:"<<endl;
    auto range=userFiles.equal_range("user_A");
    for(auto it=range.first;it!=range.second;it++){
        cout<<"file block:"<<it->second<<endl;
    }
    /* range是一个pair对象  
       range.first是区间起点 range.second是区间终点
    std::pair<std::multimap<std::string, int>::iterator, 
          std::multimap<std::string, int>::iterator>
    */
}

int main(int argc,char *argv[])
{
    practiceMapFamily();
    return 0;
}

