#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 嵌套类的访问规则
 *
 * 1.在外部类的外部访问内部类的成员
 * 
 * 2.在外部类的内部 访问内部类的成员
 *  创建内部类的对象 Inner inner：通过对象.方式访问内部类的成员。
 * 3.在内部类的内部 访问外部类的成员
 *
 */

class Outer{
public:
    class Inner1{
    public:
        void inner1Method1(){
            cout<<"innner1Method1()"<<endl;
        }
        int m_inner1Num1;
    private:
        void inner1Method2(){
            cout<<"innner1Method2()"<<endl;
        }
        int m_inner1Num2;
    };

private:
    class Inner2{
    public:
        void inner2Method1(){
            cout<<"innner1Method1()"<<endl;
        }
        int m_inner2Num1;
    private:
        void inner2Method2(){
            cout<<"innner1Method2()"<<endl;
        }
        int m_inner2Num2;

    };

public:
    int m_outerNum1;
    void outer(){
        cout<<"outerMethod1()"<<endl;
    }
private:
    int m_outerNum2;
    void outer(){
        cout<<"outerMethod2()"<<endl;
    }

};

void test1(){
    //在外部类的外部访问内部类的成员函数，
    //通过创建内部类的对象，通过对象方式访问
    //使用类名作用域，标记一下这个内部类是在哪个外部类中定义的

    Outer::Inner1 inner1;
    innner::inner1Method1();
    innner::m_inner1Method2();
    innner::inner1Method1();
    innner::inner1Method2();   

}

int main(int argc,char *argv[])
{
    
    return 0;
}

