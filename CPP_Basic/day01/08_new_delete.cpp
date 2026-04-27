#include <stdlib.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//C语言中用的是malloc / free 是库函数
void test01(){
    int *p=(int *)malloc(4);//返回void * ，需强制类型转换
    *p=100;
    cout<<*p<<endl;
    free(p);
    p=NULL;
}

/* 
 * C++中使用new / delete 是关键字，不是函数
 * new分配空间
 * delete释放空间
 *
 */
void test02(){
    //值初始化
    int *p1=new int();
    cout<<*p1<<endl;
    int *p2=new int(10);//填10 *p2的值就为10
    cout<<*p2<<endl;

    //其他写法：初始化列表方式
    int *p3=new int {};
    cout<<*p3<<endl;
    
    int *p4=new int {100};
    cout<<*p4<<endl;

    delete p1;
    delete p2;
    delete p3;
    delete p4;
}

int main(int argc,char *argv[])
{
    test01();
    test02();
    return 0;
}

