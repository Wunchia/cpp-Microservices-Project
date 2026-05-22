#include <iostream>
#include <algorithm>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

//自定义类型：模拟文件传输中的数据块
struct FileChunk{
    int chunk_id;
    size_t size;
};

template <typename Container>
void print(const Container &c){
    for(auto &e:c){
        cout<<" "<<e;
    }
    cout<<endl;
}

void practiceVector(){
    cout<<"=======vector 实践======="<<endl;
    //常用API
    vector<int>nums{10,20,30};
    print(nums);
    nums.push_back(40);
    nums.insert(nums.begin()+1,50);
    nums[0]=99;
    nums.pop_back();
    print(nums);

    auto it_find=find(nums.begin(),nums.end(),20);
    if(it_find!=nums.end()){
        cout<<"找到："<<*it_find<<endl;
    }
    //自定义类型
    vector<FileChunk> chunks={
        {1,1024},
        {2,2048},
        {3,512}
    };
    cout<<"文件块遍历："<<endl;
    for(const auto&chunk:chunks){
        cout<<"chunk_id:"<<chunk.chunk_id<<
        " size:"<<chunk.size<<endl;
    }

    //迭代器失效的场景
    vector<int> vec={1,2,3,4,5};
    //场景1：边遍历边删除
    for(auto it=vec.begin();it!=vec.end();){
        if(*it%2==0){
            it=vec.erase(it);
        }else{
            ++it;
        }
    }
    print(vec);

    //场景2：底层扩容导致迭代器失效
    vector<int> dynamic_vec;
    dynamic_vec.reserve(2);
    dynamic_vec.push_back(1);
    dynamic_vec.push_back(2);

    auto it=dynamic_vec.begin();
    int *ptr=&dynamic_vec[0];

    cout<<*it<<endl;//内存未被释放
    cout<<*ptr<<endl;//内存未被释放

    cout<<"扩容前：capacity="<<dynamic_vec.capacity()<<endl;
    dynamic_vec.push_back(3);
    cout<<"扩容后：capacity="<<dynamic_vec.capacity()<<endl;

    cout<<*it<<endl;//原内存已被释放
    cout<<*ptr<<endl;//原内存已被释放
}

int main(int argc,char *argv[])
{
    practiceVector();
    return 0;
}

