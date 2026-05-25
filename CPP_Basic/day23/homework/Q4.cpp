#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

void test1(){
    vector<int> src={1,2,3,4,5};
    list<int> dst;
    copy(src.rbegin(),src.rend(),back_inserter(dst));

    copy(dst.begin(),dst.end(),std::ostream_iterator<int>(cout," "));
    cout<<endl;
}

int main(int argc,char *argv[])
{
    test1();
    
    return 0;
}

