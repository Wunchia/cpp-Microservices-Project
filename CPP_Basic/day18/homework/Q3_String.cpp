#include <iostream>
#include <cstring>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;

class String{
public:
    String(const char*str=""){
        length=strlen(str);
        data=new char[length+1];
        memcpy(data,str,length+1);
        cout<<"String(const char*str)"<<endl;
    }

    ~String(){
        delete[] data;
        cout<<"~String()"<<endl;
    }

    String(const String&rhs)
    :length(rhs.length)
    {
        data=new char[length+1];
        memcpy(data,rhs.data,length+1);
        cout<<"String(const String&)"<<endl;
    }

    String& operator=(const String&rhs){
        if(this!=&rhs){
            char* temp=new char[length+1];
            memcpy(temp,rhs.data,length+1);
            delete[] data;
            data=temp;
        }
        cout<<"String &operator=(const String&rhs)"<<endl;
        return *this;
    }

    String(String&& rhs)noexcept
    :data(rhs.data)
    ,length(rhs.length)
    {
        rhs.data=nullptr;
        rhs.length=0;
        cout<<"String(String&&)"<<endl;
    }

    String& operator=(String&& rhs)noexcept{
        if(this!=&rhs){
            delete[] data;
            data=rhs.data;
            length=rhs.length;
            rhs.data=nullptr;
            rhs.length=0;
        }
        cout<<"String& operator=(String&& rhs)"<<endl;
        return *this;
    }

    void print()const{
        cout<<(data?data:"nullptr")<<endl;
    }
private:
    char* data;
    size_t length;
};

void test1(){
    String s1{"hello"};
    String s2=s1;
    String s3=std::move(s1);

    String s4;
    s4=std::move(s2);

    cout<<"s3: ";s3.print();
    cout<<"s4: ";s4.print();
    
}

int main(int argc,char *argv[])
{
    test1(); 
    return 0;
}

