#include <iostream>
#include <set>

using namespace std;

int main(int argc,char *argv[])
{
    int n,m;
    while(cin>>n>>m){
        set<int> union_set;
        int element;
        for(int i=0;i<n;i++){
            cin>>element;
            union_set.insert(element);
        }
        for(int i=0;i<m;i++){
            cin>>element;
            union_set.insert(element);
        }
        
        bool first=true;
        for(auto it=union_set.begin();it!=union_set.end();++it){
            if(first){
                first=false;
            }else{
                cout<<" ";
            }
            cout<<*it;
        }
        cout<<endl;
    }
    return 0;
}

