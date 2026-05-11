#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 嵌套类：
 * 把一个类定义在另一个类里面
 * 
 * 作用：
 * 内部类主要为外部类提供服务，并且对外界可以隐藏内部类
 * 
 */

//外部类
class Outer{
private:
    //内部类
    class Inner1{
    public:
        //内部类的成员函数
        void func1(){}
    private:
        //内部类的数据成员
        int m_data1;
    };

public:
    //内部类 （不能重名）
    class Inner2{
    public:
        //内部类的成员函数
        void func2(){}
    private:
        //内部类的数据成员
        int m_data2;
    };

    //外部类的成员函数
    void func(){}
    //外部类的数据成员
    int m_data;
};

//场景：
class Car{
    class Engine{

    };

};

/* 自定义数据结构的时候可能会使用嵌套类结构
 * class LinkedList{
 * private:
 *      class Node{
 *          int value;
 *          Node * next;
 *      }
 * public:
 * Node * head;
 * bool add(int value){
 *    Node* newNode=new Node{value};
 * }
 * bool remove(int value);
 * ......
 * }
 * 
 * LinkedList list();
 * list.add(1);
 * list.add(2);
 * list.add(3);
 * list.remove(3);
 * 
 */

void test1(){

}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

