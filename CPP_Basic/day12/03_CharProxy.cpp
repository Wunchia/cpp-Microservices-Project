#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ostream;

class CowString{
    //定义一个内部类CharProxy 帮CowString进行读写区分
    class CharProxy{
    public:
        CharProxy(CowString& cow,int index)
        :m_self(cow)
        ,m_index(index)
        {}
        //operator<<
        //cout<<s[0];
        //---> CharProxy对象--->m_self--->m_pstr--->char
        friend ostream& operator<<(ostream&os,const CharProxy &rhs);

        //operator=
        //s[0]='A' CowString对象调用operator[]--->CharProxy对象
        //--->m_self---->m_pstr[m_index]
        char& operator=(const char& ch){
           if(m_index<0||m_index>=strlen(m_self.m_pstr)){
            cout<<"index is illegal"<<endl;
            //throw "index is illegal";
            static char nullChar='\0';
            return nullChar;
        }else{
            //获取引用计数 是否大于1
            if(m_self.getRefCount()>1){
                //如果大于1 说明有共享
                //当前的引用计数-1
                m_self.decrementRefCount();
                //进行深拷贝
                char* temp=new char[4+strlen(m_self.m_pstr)+1]{}+4;
                strcpy(temp,m_self.m_pstr);
                //更改底层指针
                m_self.m_pstr=temp;
                //新的空间的引用计数初始化为1
                m_self.initRefCount();
            }
            //赋值字符
            m_self.m_pstr[m_index]=ch;
            //返回字符
            return m_self.m_pstr[m_index]; 
        }}
    private:
        CowString & m_self;//记录当前字符串对象的状态
        int m_index;//记录访问的数组的下标
    };

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
    }

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
                cout<<"release heap====>"<<endl;
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

#if 0
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
    //无法区分读写操作
#endif

    //operator[]
    CharProxy operator[](int index){
        return CharProxy{*this,index};
    };

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
    friend ostream& operator<<(ostream&os,const CowString::CharProxy &rhs);

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

//CharProxy类的operator<<
ostream& operator<<(ostream&os,const CowString::CharProxy &rhs){
    os<<rhs.m_self.m_pstr[rhs.m_index];
    return os;
}

void test1(){
    // 此时底层数组空间没有共享 --->OK的
    // 如果发生了共享
    CowString s1{"abc"};
    CowString s2=s1;
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"---------------"<<endl;
    cout<<s1[0]<<endl;
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"---------------"<<endl;
    s1[0]='A';
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
}

int main(){
    test1();
    return 0;
}