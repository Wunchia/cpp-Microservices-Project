#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}

int main(int argc,char *argv[])
{
    int x=1,y=2;
    swap(x,y);
    cout<<x<<" "<<y<<endl;    
    return 0;
}

