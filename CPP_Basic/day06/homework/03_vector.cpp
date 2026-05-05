#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void test(){
    vector<vector<int>> box={{1,2,3},{4,5,6},{7,8,9}};
    cout<<"size:"<<box.size()<<endl;
    cout<<"capacity:"<<box.capacity()<<endl;
    for(const auto &it:box){
        cout<<"<------------"<<endl;
        cout<<"size="<<it.size()<<endl;
        cout<<"capacity="<<it.capacity()<<endl;
        for(auto int_it=it.begin();int_it!=it.end();++int_it){
            cout<<*int_it<<endl;
        }
        cout<<"----------->"<<endl;
    }
}

int main(int argc,char *argv[])
{
    test(); 
    return 0;
}

