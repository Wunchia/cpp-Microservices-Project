#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void test1(){
    vector<int> box{1,5,8,3,6,9,2,7,4};
    auto it=remove_if(box.begin(),box.end(),[](int n){return n>5;});
    box.erase(it,box.end());
    copy(box.begin(),box.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}



int main(int argc,char *argv[])
{
    test1();
    
    return 0;
}

