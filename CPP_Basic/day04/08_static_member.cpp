#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

/*
 * 静态数据成员：static修饰类中普通成员
 *
 * 特点：
 * 1.静态数据成员不依赖于对象，依赖于类
 * 2.不占据对象的内存大小
 * 3.静态数据成员一般通过类名作用域进行访问
 * 4.静态数据成员被所有的对象所共享
 * 5.静态数据成员需要在类外进行初始化
 *
 */

class MyClass{
public:
    // MyClass(int a)
    // :m_data(a){}

    //静态数据成员
    static int m_data;
};

//类外初始化静态数据成员
//要使用类名作用域
int MyClass::m_data=1;

void test1(){

    //访问静态的数据成员，一般通过类名作用域访问
    //此时根本就没创建对象
    cout<<MyClass::m_data<<endl;
    cout<<"-------------------"<<endl;

    MyClass obj1;
    MyClass obj2;
    MyClass obj3;
    cout<<obj1.m_data<<endl;
    cout<<obj2.m_data<<endl;
    cout<<obj3.m_data<<endl;
    //获取对象大小
    cout<<sizeof(obj1)<<endl;
}

class Student{
public:
    Student(int id,string name)
    :m_id(id)
    ,m_name(name)
    {m_count++;}

    int m_id;
    string m_name;
    static int m_classID;
    static int m_count;

    void print(){
        cout<<m_id<<" "<<m_name<<" "<<m_classID<<endl;
    }

    void getCount(){
        cout<<"count: "<<m_count<<endl;
    }

    ~Student(){
        m_count--;
    }
};

int Student::m_classID=10;
int Student::m_count=0;

//要描述zs，ls，ww这三个学生，他们是同一个班级的
void test2(){
    Student s1{1,"zs"};
    Student s2{2,"ls"};
    s1.getCount();
    Student s3{3,"ww"};
    cout<<"count:"<<Student::m_count<<endl;
    s1.print();
    s2.print();
    s3.print();
}

int main(int argc,char *argv[])
{
    // test1();    
    test2();
    return 0;
}
