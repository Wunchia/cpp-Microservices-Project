#include <iostream>
#include <functional>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Printer{
public:
    void print(const string &s)const{
        cout<<s<<endl;
    }
};

void test(){
    vector<Printer> vec(3);

    for_each(vec.begin(),vec.end(),bind(mem_fn(&Printer::print),placeholders::_1,"hello"));

}

int main(int argc,char *argv[])
{
    test();    
    return 0;
}

