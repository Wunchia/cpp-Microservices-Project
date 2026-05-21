#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using namespace std;

template <typename T>
void print(const T&t){
    for(const auto&e:t){
        cout<<e<<" ";
    }
    cout<<endl;
}

template <typename T>
void printContainer(const std::string&name,const T&container){
    cout<<name<<"[大小："<<container.size()<<"]:";
    print(container);
    if(!container.empty()){
        cout<<"(首元素地址："<<&(*container.begin())<<")";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    cout<<"======vector の insert======"<<endl;    
    vector<int> vec{10,3,20,3,30};
    cout<<"vec Capacity: "<<vec.capacity()<<endl;

    auto vec_it=vec.begin()+1;
    cout<<"vec_it:"<<*vec_it<<"  &vec_it:"<<&(*vec_it)<<endl;
    //扩容后 原迭代器失效，需要重新获取迭代器
    vec.insert(vec_it,15);
    cout<<"after insert:"<<endl;
    printContainer("vec",vec);
    cout<<"*vec_it:"<<*vec_it<<endl;

    cout<<"----correct operation----"<<endl;
    auto it=vec.begin();
    while(it!=vec.end()){
        if(*it==3){
            it=vec.insert(it,99);
            it+=2;
        }else{
            ++it;
        }
    }
    printContainer("vec",vec);

    cout<<"======deque の insert======"<<endl;    
    deque<int> deq{10,20,30};
    printContainer("deq",deq);
    auto deq_it=deq.begin()+1;
    cout<<"deq_it:"<<*deq_it<<"  &deq_it:"<<&(*deq_it)<<endl;
    deq_it=deq.insert(deq_it,15);
    cout<<"after insert:"<<endl;
    printContainer("deq",deq);
    cout<<"*deq_it:"<<*deq_it<<endl;
    
    cout<<"======list の insert======"<<endl;    
    list<int> lst{10,20,30};
    printContainer("lst",lst);
    // auto lst_it=lst.begin()+1;
    auto lst_it=std::next(lst.begin(),1);
    cout<<"lst_it:"<<*lst_it<<"  &lst_it:"<<&(*lst_it)<<endl;
    auto new_lst_it=lst.insert(lst_it,15);
    cout<<"after insert:"<<endl;
    printContainer("lst",lst);
    cout<<"*lst_it:"<<*lst_it<<"  &lst_it:"<<&(*lst_it)<<endl;
    cout<<"*new_lst_it:"<<*new_lst_it<<"  &new_lst_it:"<<&(*new_lst_it)<<endl;
    return 0;
}

