#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

class LRUCache{
private:
    list<int> lst;//缓存容器 头部最近访问 尾部最久未访问
    size_t cap=3; //缓存最大容量

    //用一个哈希表记录 page 到链表迭代器的映射
    unordered_map<int,list<int>::iterator> ma;

public:
    void refer(int page){
        if(ma.find(page)!=ma.end()){
            lst.splice(lst.begin(),lst,ma[page]);
            return;
        }

        if(lst.size()==cap){
            int last_page=lst.back();
            ma.erase(last_page);
            lst.pop_back();
        }
        lst.push_front(page);
        ma[page]=lst.begin();  
    }

    void printCache(){
        for(int x:lst){
            cout<<x<<" ";
        }
        cout<<endl;
    }
};

int main(int argc,char *argv[])
{   
    LRUCache cache;

    cout << "cache.refer(1); // "; cache.refer(1); cache.printCache();
    cout << "cache.refer(2); // "; cache.refer(2); cache.printCache();
    cout << "cache.refer(3); // "; cache.refer(3); cache.printCache();
    cout << "cache.refer(2); // "; cache.refer(2); cache.printCache();
    cout << "cache.refer(4); // "; cache.refer(4); cache.printCache();
    cout << "cache.refer(1); // "; cache.refer(1); cache.printCache();
    
    return 0;
}

