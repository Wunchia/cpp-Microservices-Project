#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/*
 * 单例的自动释放：
 * 方式四：利用atexit()+pthread_once+destroyInstance()
 * 
 * atexit(函数指针)：把函数指针指向的函数注册到atexit当中
 * 参数的这个函数是一个回调函数
 * 当满足程序结束的条件时，被注册到atexit当中的函数被自动调用
 * 
 */

class Singleton{
public:
    static Singleton* getInstance(){
        //执行初始化的那个函数
        pthread_once(&m_once_control,&initRoutine);
        return m_pInstance;
    }

    //提供一个用了初始化的函数
    static void initRoutine(){
        //初始化只会被执行一次
        m_pInstance=new Singleton{};
        atexit(&destroyInstance);
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
    static pthread_once_t m_once_control;
};
//静态成员类外初始化
Singleton*Singleton:: m_pInstance=nullptr;

pthread_once_t Singleton::m_once_control=PTHREAD_ONCE_INIT;

void test1(){
    cout<<Singleton::getInstance()<<endl;
    cout<<Singleton::getInstance()<<endl;
    cout<<Singleton::getInstance()<<endl;
}

int main(int argc,char *argv[])
{
    
    test1();    
    return 0;
}

