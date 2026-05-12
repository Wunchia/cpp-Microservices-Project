#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class CowString{
    //代理类
    class CharProxy{
    public:
        CharProxy(CowString& cow,int index)
        :m_self(cow)
        ,m_index(index)
        {}

        //读逻辑的封装：隐式转换为 char
        operator char()const{
            return m_self.m_pstr[m_index];
        }

        //------------访问功能 operator<<  --------------
        //cout<<s[0]---->CharProxy对象---->m_self---->m_pstr---->char
        // friend ostream& operator<<(ostream&os,const CharProxy &rhs);

        //------------读入功能 operator>> ---------------
        //cin>>s[0]---->CharProxy对象---->m_self---->m_pstr---->char
        friend istream& operator>>(istream&is,const CharProxy &rhs);

        //------------修改功能 operator=  --------------
        //s[0]='A'
        //CowString对象调用operator[]--->CharProxy对象--->m_self--->m_pstr[m_index]
        char& operator=(const char& ch){
            if(m_index<0||m_index>strlen(m_self.m_pstr)){
                cout<<"index is illegal"<<endl;
                static char nullChar='\0';
                return nullChar;
            }else{
                if(m_self.getRefCount()>1){
                    m_self.decrementRefCount();
                    char*temp=new char[4+strlen(m_self.m_pstr)+1]{}+4;
                    strcpy(temp,m_self.m_pstr);
                    m_self.m_pstr=temp;
                    m_self.initRefCount();
                }
                m_self.m_pstr[m_index]=ch;
                return m_self.m_pstr[m_index];
            }
        }

    private:
        CowString & m_self;//记录当前字符串   工作场地
        int m_index;//记录访问的数组下标   工作目标
    };

public:
    //===============构造函数==================
    //无参构造
    CowString()
    :m_pstr(new char[4+1]{}+4)
    {
        initRefCount();
    }

    //有参构造
    CowString(const char*pstr)
    :m_pstr(new char[4+strlen(pstr)+1]{}+4)
    {
        initRefCount();
        strcpy(m_pstr,pstr);
    }

    //拷贝构造
    CowString(const CowString&rhs)
    :m_pstr(rhs.m_pstr)//用浅拷贝 共享空间 然后改下引用计数就行
    {
        incrementRefCount();
    }

    //===============析构函数=================
    ~CowString(){
        decrementRefCount();
        if(getRefCount()==0){//如果不为0 则只需要减引用计数 然后指针置空
            delete[] (m_pstr-4);
            cout<<"release heap====>"<<endl;
        }
        m_pstr=nullptr;
    }

    //==============运算符重载（成员函数）==============
    //operator=
    CowString&operator=(const CowString& rhs){
        if(this!=&rhs){
            decrementRefCount();//先把原来的减掉
            if(getRefCount()==0){//检查是否需要回收空间
                delete[] (m_pstr-4);
                cout<<"release heap=====>"<<endl;
            }
            m_pstr=rhs.m_pstr;//核心操作
            incrementRefCount();//再给新的加上
        }
        return *this;
    }

    //char() 类型转换
    char operator[](int index)const{
        if(index<0||index>=strlen(m_pstr)){
            throw "index is illegal";
        }
        return m_pstr[index];
    }

    //operator[]  通过代理类实现
    CharProxy operator[](int index){
        return CharProxy(*this,index);
    }

    //==============工具函数==================
    int size(){
        return strlen(m_pstr);
    }

    char* c_str(){
        return m_pstr;
    }

    int getRefCount(){
        return *(int*)(m_pstr-4);
    }

    //===============友元函数===================
    friend ostream& operator<<(ostream &os,const CowString&rhs);
    // friend ostream& operator<<(ostream &os,const CharProxy &rhs);
    friend istream& operator>>(istream&is,const CharProxy &rhs);

private:
    char *m_pstr;

    void initRefCount(){
        *(int*)(m_pstr-4)=1;
    }

    void incrementRefCount(){
        ++*(int*)(m_pstr-4);
    }

    void decrementRefCount(){
        --*(int*)(m_pstr-4);
    }

};

//============友元函数 的 类外实现===========
ostream& operator<<(ostream &os,const CowString&rhs){
    os<<rhs.m_pstr;
    return os;
}

// ostream& operator<<(ostream &os,const CowString::CharProxy &rhs){
//     //cout<<s[0]---->CharProxy对象---->m_self---->m_pstr---->char
//     os<<rhs.m_self.m_pstr[rhs.m_index];
//     return os;
// }

istream& operator>>(istream&is,const CowString::CharProxy &rhs){
    //cin>>s[0]---->CharProxy对象---->m_self---->m_pstr---->char
    if(rhs.m_index<0||rhs.m_index>strlen(rhs.m_self.m_pstr)){
        // cout<<"index is illegal"<<endl;
        throw "index is illegal";
    }else{
        if(rhs.m_self.getRefCount()>1){
            rhs.m_self.decrementRefCount();
            char* temp=new char[4+strlen(rhs.m_self.m_pstr)+1]{}+4;
            strcpy(temp,rhs.m_self.m_pstr);
            rhs.m_self.m_pstr=temp;
            rhs.m_self.initRefCount();
        }
        is>>rhs.m_self.m_pstr[rhs.m_index];//如果没有其他引用，则直接改即可
        return is;
    }
}

void test1(){
    CowString s1{"hello"};
    CowString s2=s1;
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"--------------cout 访问----------------"<<endl;
    if(s1[0]=='h'){cout<<s1[0]<<endl;}
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"-------------[]= 修改-------------------"<<endl;
    s1[2]='L';
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
    cout<<"-------------cin>>[]读入----------------"<<endl;
    cin>>s1[0];
    cout<<"s1:"<<s1<<" RefCount:"<<s1.getRefCount()<<endl;
    cout<<"s2:"<<s2<<" RefCount:"<<s2.getRefCount()<<endl;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}

