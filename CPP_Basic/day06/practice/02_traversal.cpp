#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void testTraversal(){
    vector<int> v={10,20,30,40,50};

    for(size_t i=0;i<v.size();++i){
        cout<<v[i]<<" ";
    }
    cout<<endl;

    for(const auto &it:v){
        cout<<it<<" ";
    }
    cout<<endl;

    for(auto it=v.begin();it!=v.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main(int argc,char *argv[])
{
    testTraversal();
    return 0;
}

