#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 *  friend友元：
 *  1.普通函数的友元形式（友元函数）
 *  2.成员函数的友元形式（把成员函数声明为友元）
 *  3.友元类（把类声明为友元）
 */

class MyClass;

class FriendClass{
public:
    void func(const MyClass& obj);

};

class MyClass{
public:
    int getData(){
        return m_data;
    }
    // friend void FriendClass::func(const MyClass&obj);

    //把FriendClass声明为友元
    friend class FriendClass;

private:
    int m_data=1;
};

void FriendClass::func(const MyClass&obj){
    obj.m_data;
}

void test1(){

}

int main(int argc,char *argv[])
{
    test1();    
    return 0;
}

