#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
 * 封装的通常做法：
 * 1.把不想被外界访问的成员使用private修饰
 * 2.给外界提供一个访问的接口：读写分离操作
 * 访问需求：提供getxxx方法 读操作
 * 修改需求：提供setxxx方法 用于数据修改
 * 
 */

class Employee{
public:
    int id=1;
    string name="zs";
private:
    double salary=12000;
};

class Student{
public:
    int id;
    string name;
    //提供访问的入口getxxx
    int getScore(){
        //进行权限的校验
        //如果是老师或者教务人员
        return score;
    }
    //提供一个修改的入口 setxxx
    void setScore(int newScore){
        //对数据进行校验
        score=newScore;
    }
private:
    int score;
}

void  test1(){
    Employee zs;
    cout<<zs.id<<endl;
    cout<<zs.name<<endl;
    cout<<zs.salary<<endl;
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}

