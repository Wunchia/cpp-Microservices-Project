#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
    double d=3.14;
    int i=static_cast<int>(d);

    void*vptr=&i;
    int *iptr=static_cast<int*>(vptr);

    cout<<"i:"<<i<<", *iptr:"<<*iptr<<endl;
    
    return 0;
}

