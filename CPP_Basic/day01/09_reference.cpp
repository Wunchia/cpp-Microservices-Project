#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 引用：一个已经存在的变量或者对象的别名
 * 语法：
 * 数据类型 & 引用名 = 变量/对象
 *
 *  引用的本质：是一个特殊的指针
 *  引用一经绑定就不能够进行修改 
 *  （本质是一个常量指针）
 */

void test01(){
    //num是本名
    int num=1;
    //ref是别名
    int &ref=num;

    cout<<ref<<endl;
    //通过别名进行修改
    ref=2;
    cout<<"----------"<<endl;
    cout<<ref<<endl;

    int num2=10;
    ref=num2;//这里并不是修改了指向 而是一个赋值操作
             //将10 赋值给num
}

//引用VS指针
void test02(){
    int num=1;
    int *p; //声明了一个指针
    p=&num;

    //引用定义的时候必须要进行初始化
    /* int &ref; */
    int &ref=num;

    cout<<&num<<endl;//num的地址
    cout<<p<<endl;//p的指向 即num的地址
    cout<<&p<<endl;//指针的地址 p的地址
    cout<<&ref<<endl;//引用的地址 还是num的地址
    //对引用取地址，取的是所绑定的变量的地址

}


int main(int argc,char *argv[])
{
    /* test01(); */
    test02();
    return 0;
}

