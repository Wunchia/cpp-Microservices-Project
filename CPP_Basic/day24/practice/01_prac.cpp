#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void test1(){
    vector<int> vec{1,2,3,4,5};
    cout<<"for_each遍历"<<endl;
    for_each(vec.begin(),vec.end(),[](const int val){
        cout<<val<<" ";
    });
    cout<<endl;

    cout<<"修改元素"<<endl;
    for_each(vec.begin(),vec.end(),[](int &val){
        cout<<(val*=2)<<" ";
    });
    cout<<endl;
}

int main(int argc,char *argv[]){
    test1();
    return 0;
}
