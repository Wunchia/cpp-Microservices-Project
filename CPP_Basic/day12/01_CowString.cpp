#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ostream;

class CowString{
public:
    //无参构造
    CowString()
    :m_pstr(new char[4+1]{}+4)
    {
        //初始化引用计数器为1
        // *(int*)(m_pstr-4)=1;
        initRefCount();
    }

    //有参构造
    CowString(const char *pStr)
    :m_pstr(new char[4+strlen(pStr)+1]{}+4)
    {
        //初始化引用计数器为1
        // *(int*)(m_pstr-4)=1;
        initRefCount();
        //数据复制
        strcpy(m_pstr,pStr);
    }

    //析构
    ~CowString(){
        //引用计数器-1
        decrementRefCount();
        //判断引用计数的值和0的关系
        //如果为0 说明没有string对象在引用这片空间了 进行回收
        if(getRefCount()==0){
            delete[] (m_pstr-4);
            cout<<"release heap====>"<<endl;
        }
        //如果不为0 说明还有string对象在引用这片空间 不回收
        //将指针设置为空
        m_pstr=nullptr;
    };

    //拷贝构造
    CowString(const CowString& rhs)
    :m_pstr(rhs.m_pstr)//深拷贝--->浅拷贝  共享空间
    {
        //引用计数+1
        // ++*(int*)(m_pstr-4);
        incrementRefCount();
    }

    //赋值运算符
    CowString&operator=(const CowString&rhs){
        //自赋值判断
        if(this!=&rhs){
            //引用计数-1
            decrementRefCount();
            //如果引用计数为0 回收原本空间
            if(getRefCount()==0){
                delete[] (m_pstr-4);
                cout<<"release hesp====>"<<endl;
            }
            //更改指针指向 让当前对象的字符指针指向新的空间 
            m_pstr=rhs.m_pstr;
            //将新空间的引用计数+1  浅拷贝
            incrementRefCount();
        }
        //返回当前对象 *this
        return *this;
    }

# if 0
    //operator[]
    char& operator[](int index){
        if(index<0||index>=strlen(m_pstr)){
            cout<<"index is illegal"<<endl;
            //throw "index is illegal";
            static char nullChar='\0';
            return nullChar;
        }else{
            return m_pstr[index];
        }
    }
    //通过下标访问index位置的字符没问题
    //但是有共享时，修改会对其他的string对象产生影响
#endif

    //operator[]
    char& operator[](int index){
        if(index<0||index>=strlen(m_pstr)){
            cout<<"index is illegal"<<endl;
            //throw "index is illegal";
            static char nullChar='\0';
            return nullChar;
        }else{
            //获取引用计数 是否大于1
            if(getRefCount()>1){
                //如果大于1 说明有共享
                //当前的引用计数-1
                decrementRefCount();
                //进行深拷贝
                char* temp=new char[4+strlen(m_pstr)+1]{}+4;
                strcpy(temp,m_pstr);
                //更改底层指针
                m_pstr=temp;
                //新的空间的引用计数初始化为1
                initRefCount();
            }
            //返回字符
            return m_pstr[index];
        }
    }

    int size(){
        return strlen(m_pstr);
    }

    char* c_str(){
        return m_pstr;
    }

    int getRefCount(){
        return *(int*)(m_pstr-4);
    }

    friend ostream& operator<<(ostream &os,const CowString& rhs);

private:
    void initRefCount(){
        *(int*)(m_pstr-4)=1;
    }

    void incrementRefCount(){
        ++*(int*)(m_pstr-4);
    }

    void decrementRefCount(){
        --*(int*)(m_pstr-4);
    }

    char* m_pstr;
};


ostream& operator<<(ostream &os,const CowString& rhs){
    os<<rhs.m_pstr;
    return os;
}

void test1(){
    CowString s1;
    CowString s2{"abc"};
    cout<<s1<<endl;
    cout<<s2<<endl;
}

void test2(){
    CowString s1{"abc"};
    cout<<"s1 RefCount:"<<s1.getRefCount()<<endl;
    cout<<"-------------------"<<endl;
    CowString s2=s1;
    cout<<"s1 RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2 RefCount:"<<s2.getRefCount()<<endl;
    cout<<s1<<endl;
    cout<<s2<<endl;
}

void test3(){
    //没有共享
    CowString s1{"abc"};
    cout<<s1<<endl;
    cout<<"--------------"<<endl;

    //有共享
    CowString s2{"hello"};
    CowString s3=s2;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"s3:"<<s3<<" RefCount:"<<s3.getRefCount()<<endl;
}

//测试对象的赋值操作
void test4(){
    CowString s1{"abc"};
    CowString s2=s1;
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    CowString s3{"bcd"};
    cout<<"s3:"<<s3<<" RefCount:"<<s3.getRefCount()<<endl;
    cout<<"------s1=s3-----------"<<endl;
    s1=s3;
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"s3:"<<s3<<" RefCount:"<<s3.getRefCount()<<endl;
    cout<<"-------s2=s3------------"<<endl;

    s2=s3;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"s3:"<<s3<<" RefCount:"<<s3.getRefCount()<<endl;
}

void test5(){
    // 此时底层数组空间没有共享 --->OK的
    // 如果发生了共享
    CowString s1{"abc"};
    CowString s2=s1;
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"---------------"<<endl;
    cout<<s1[0]<<endl;
    s1[0]='A';
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
}

int main(){
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}