#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;


/*
find:找到了返回对应位置的迭代器，没有找到返回end()迭代器
*/

void test1(){
    vector<int> box{1,2,3,3,4,5};
    auto it=find(box.begin(),box.end(),3);
    if(it!=box.end()){
        cout<<"找到"<<endl;
        cout<<"*it="<<*it<<endl;
    }else{
        cout<<"没有找到"<<endl;
    }
    cout<<"-----"<<endl;
    ++it;
    cout<<"*it="<<*it<<endl;
    ++it;
    cout<<"*it="<<*it<<endl;
}

bool func(int num){
    return num>3;
}

//函数对象
struct OverThree{
    bool operator()(int num){
        return num>3;
    }
};

//find_if:第三个参数是个一元谓词：
//一元谓词：返回值为bool类型的，一个参数的函数
void test2(){
    vector<int> box{1,2,3,3,4,5};
    // auto it=find_if(box.begin(),box.end(),func);
    // auto it=find_if(box.begin(),box.end(),&func);
    // auto it=find_if(box.begin(),box.end(),OverThree());
    auto it=find_if(box.begin(),box.end(),
        [](int num)->bool{
            return num>3;
        }
    );
    cout<<"*it="<<*it<<endl;
    ++it;
    cout<<"*it="<<*it<<endl;

}

//replace:替换所有等于val的元素为new_val
//void replace(迭代器first,迭代器last,值val,新new_val);
void test3(){
    vector<int> box{1,2,3,3,4,5};
    replace(box.begin(),box.end(),3,100);
    std::copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}

//replace_if:替换所有满足条件的元素为new_val
//void replace_if(迭代器first,迭代器last,一元谓词pred,新new_val);
void test4(){
    vector<int> box{1,2,3,3,4,5};
    replace_if(box.begin(),box.end(),
        [](int num)->bool{
            return num>3;
        },
        100
    );
    std::copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}

//remove:1.删除所有等于val的元素 2.移动剩余元素到前面
//ForwardIterator remove(迭代器first,迭代器last,值val);
void test5(){
    vector<int> box{1,2,3,3,4,5};
    auto it=remove(box.begin(),box.end(),3);
    std::copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl<<"-------------"<<endl;
    std::copy(box.begin(),it,std::ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"*it="<<*it<<endl;
    //结合erase删除元素
    box.erase(it,box.end());
    std::copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}

//remove_if:删除所有满足条件的元素
//ForwardIterator remove_if(迭代器first,迭代器last,一元谓词pred);
void test6(){
    vector<int> box{1,2,3,3,4,5};
    auto it=remove_if(box.begin(),box.end(),
        [](int num)->bool{
            return num>3;
        }
    );
    std::copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    //test5();
    test6();
    return 0;
}

