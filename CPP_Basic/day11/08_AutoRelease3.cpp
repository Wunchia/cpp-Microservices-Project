#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 单例的自动释放：
 * 方式三：利用atexit()+destroyInstance()
 * 
 * atexit(函数指针)：把函数指针指向的函数注册到atexit当中
 * 参数的这个函数是一个回调函数
 * 当满足程序结束的条件时，被注册到atexit当中的函数被自动调用
 * 
 * 单例的两种模式：
 * 1.懒加载（懒汉式）：不用的时候不创建，用的时候再创建
 * 2.立即加载（饿汉式）：不管用不用这个单例对象，
 *                     先把这个单例对象创建出来，用的时候给你返回
 * 
 */

class Singleton{
public:
    static Singleton* getInstance(){
        if(!m_pInstance){
            m_pInstance=new Singleton{};
            //把销毁函数注册到 atexit
            atexit(&destroyInstance);
        }
        return m_pInstance;
    }

    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;

    // 提供回收资源的操作  (手动清理)
    static void destroyInstance(){
        cout<<"destroyInstance()"<<endl;
        if(m_pInstance){
            delete m_pInstance;
            m_pInstance=nullptr;
        }
    }


private:
    Singleton(){}
    ~Singleton(){}
    static Singleton* m_pInstance;
};
//静态成员类外初始化
Singleton*Singleton:: m_pInstance=nullptr;

void test1(){
    atexit(&Singleton::destroyInstance);

    cout<<Singleton::getInstance()<<endl;
    cout<<Singleton::getInstance()<<endl;
    cout<<Singleton::getInstance()<<endl;
}

int main(int argc,char *argv[])
{
    
    cout<<"main start"<<endl;
    test1();    
    cout<<"main end"<<endl;
    return 0;
}

