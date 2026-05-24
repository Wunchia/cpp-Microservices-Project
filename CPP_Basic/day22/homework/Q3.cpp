#include <iostream>
#include <vector>
using namespace std;

int main(int argc,char *argv[])
{
    vector<int> vec={1,2,3,4,5};
    
    auto it=vec.begin();

    while(it != vec.end()){
        if(*it%2==0){
            int double_val=*it*2;
            it=vec.insert(it+1,double_val);
            it++;
        }else{
            it++;
        }
    }

    for(int x:vec){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}

