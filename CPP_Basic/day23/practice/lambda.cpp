#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sytaxPractice(){
    int x=10;
    int y=20;
    //按值捕获
    auto captureByValue=[x]()->void{
        cout<<"x="<<x<<endl;
    };
    captureByValue();
    cout<<"-------------"<<endl;
    //按引用捕获
    auto captureByReference=[&y]()->void{
        y+=5;
        cout<<"y="<<y<<endl;
    };
    captureByReference();
    cout<<"y="<<y<<endl;
    cout<<"-------------"<<endl;
    //有参
    auto withParameters=[](int a,int b)->void{
        cout<<"a="<<a<<" b="<<b<<endl;
    };
    withParameters(100,200);
    cout<<"-------------"<<endl;
    //有返回值
    auto withReturnValue=[](int a,int b)->int{
        return a+b;
    };
    int sum=withReturnValue(100,200);
    cout<<"sum="<<sum<<endl;

}

void containerTreaversalPractice(){
    vector<int> box{1,2,3,4,5};
    for_each(box.begin(),box.end(),[](int n){cout<<n<<" ";});
    cout<<endl;

    for_each(box.begin(),box.end(),[](int &n){n*=2;});
    for_each(box.begin(),box.end(),[](int n){cout<<n<<" ";});
    cout<<endl;
}

int main(int argc,char *argv[])
{
    sytaxPractice();
    containerTreaversalPractice();
    
    return 0;
}

