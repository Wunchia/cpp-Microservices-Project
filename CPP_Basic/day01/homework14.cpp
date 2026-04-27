#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//函数重载练习,处理不同类型数组

// 打印整型数组
void processArray(int arr[], int size){
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

// 打印双精度浮点数组并计算平均值
void processArray(double arr[], int size){
    double sum=0;
    for(int i=0;i<size;i++){
        sum+=arr[i];
        cout<<arr[i]<<" ";
    }
    cout<<endl<<"avg="<<sum/size<<endl;
}

int main(int argc,char *argv[])
{
    int arr1[5]={1,2,3,4,5};
    processArray(arr1,5);
    double arr2[3]={3.14,2.18,7.2};
    processArray(arr2,3);
    return 0;
}

