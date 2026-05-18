#include <iostream>
#include <set>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::set;

template <typename T>
T add(const T& a,const T& b){
    return a+b;
}

template <>
set<int> add<set<int>>(const set<int>& a,const set<int>&b){
    set<int> result=a;
    result.insert(b.begin(),b.end());
    return result;
}

void printSet(const set<int>& s){
    cout<<"{";
    for(int val:s){
        cout<<val<<" ";
    }
    cout<<"}";
}

int main(int argc,char *argv[])
{
    // ==========================================
    // 测试 1：两个整数类型相加
    // ==========================================
    int int1 = 10, int2 = 20;
    // 显式实例化或隐式推导均可
    int intResult = add(int1, int2); 
    std::cout << "1. 整数相加结果: " 
              << int1 << " + " << int2 << " = " << intResult << std::endl;

    // ==========================================
    // 测试 2：两个 double 型数据相加
    // ==========================================
    double d1 = 3.14, d2 = 2.71;
    double doubleResult = add(d1, d2);
    std::cout << "2. Double相加结果: " 
              << d1 << " + " << d2 << " = " << doubleResult << std::endl;

    // ==========================================
    // 测试 3：两个存放 int 的 set 融合
    // ==========================================
    std::set<int> set1 = {1, 3, 5, 7};
    std::set<int> set2 = {2, 3, 4, 5, 6}; // 注意：3 和 5 是重复元素

    std::set<int> setResult = add(set1, set2);

    std::cout << "3. Set 融合结果: " << std::endl;
    std::cout << "   Set 1: "; printSet(set1); std::cout << std::endl;
    std::cout << "   Set 2: "; printSet(set2); std::cout << std::endl;
    std::cout << "   融合后: "; printSet(setResult); 
    std::cout << " (重复元素已自动去重)" << std::endl;
    
    return 0;
}

