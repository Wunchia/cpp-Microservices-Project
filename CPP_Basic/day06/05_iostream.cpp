#include <iostream>
#include <unistd.h>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

/*
 * 通用输入输出流 istream/ostream
 *
 * cin:标准输入流 默认输入设备：键盘
 *      本质：istream类型的一个全局对象
 *      Point pt;
 *      istream cin;
 * 
 * cout:标准输出流 默认输出设备：终端控制台
 *      本质：ostream类型的一个全局对象
 *      ostream cou;
 * 
 * 缓冲区：
 * 行缓冲 全缓冲 非缓冲
 */

void test1(){
    cout<<"input nums:"<<endl;
    int num1;
    int num2;
    cin>>num1;
    cin>>num2;
    cout<<"num1="<<num1<<endl;
    cout<<"num2="<<num2<<endl;
}
void test2(){
    cout<<"input nums:"<<endl;
    int num1;
    int num2;
    cin>>num1>>num2;
    cout<<"num1="<<num1<<endl;
    cout<<"num2="<<num2<<endl;
    //能够连续输入输出 和连续赋值时类似的
    /*
     * Point pt1;
     * Point pt2;
     * Point pt3;
     * pt3=pt2=pt1; 连续调用了operator=这个函数
     * 返回值类型为Point&
     * Point& operator=();
     * pt3.operator=(pt2.operator=(pt1));
     * 
     * << >>
     * ostream&operator<<();
     * istream&operator>>();
     * cout << data1 << data2;
     * (cout.operator<<(data1)).operator<<(data2);
     * 相当于：(cout << data1) << data2; 其中括号部分返回 cout 引用
     */
}

//cin可以作为if判断的条件
void test3(){
    cout<<"input a num:"<<endl;
    int num;
    // if(cin.good()){
    //good状态---> true
    //非good状态--->false
    //cin作为条件时，隐式类型转换为bool类型
    if(cin){
        cin>>num;
    }
    cout<<num<<endl;
}

//测试缓冲区
void test4(){
    for(int i=0;i<100;++i){
        cout<<'a';
    }
    //程序结束时进行刷新
}

void test5(){
    for(int i=0;i<100;++i){
        cout<<'a';
    }
    //让程序暂停5秒
    sleep(5);
    cout<<"test5 end";//到程序结束才输出到屏幕
    //证明cout中有缓冲区
}

//全缓冲
void test6(){
    for(int i=0;i<1030;++i){
        cout<<'a';
    }//立刻打出来一部分
    //让程序暂停5秒
    sleep(5);
    cout<<"test5 end";//等5秒后接着输出
    //证明cout缓冲区满时会刷新
}

//行缓冲
void test7(){
    for(int i=0;i<10;++i){
        cout<<'a'<<endl;//遇到换行符刷新
    }
    //让程序暂停5秒
    sleep(5);
    cout<<"test5 end";
    //证明cout中有缓冲区
}

void test8(){
    for(int i=0;i<100;i++){
        //标准错误流
        std::cerr<<'a';//cerr没有缓冲区
    }
    sleep(5);
    cout<<"test8 end";
}

int main(int argc,char *argv[])
{
    // test1();    
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    test8();
    return 0;
}

