#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

class String
{
public:
	String()
    :_pstr(new char[1]{'\0'})
    {
        cout<<"String()"<<endl;
    }

	String(const char *pstr)
    :_pstr(new char[strlen(pstr)+1]{})
    {
        strcpy(_pstr,pstr);
        cout<<"String(const char*)"<<endl;
    }

	String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr)+1]{})
    {
        strcpy(_pstr,rhs._pstr);
        cout<<"String(const String&)"<<endl;
    }

	String &operator=(const String &rhs){
        if(this!=&rhs){
            char* temp=new char[strlen(rhs._pstr)+1];
            strcpy(temp,rhs._pstr);
            delete[] _pstr;
            _pstr=temp;
        }
        cout<<"operator="<<endl;
        return *this;
    }

	~String(){
        delete[]_pstr;
        _pstr=nullptr;
        cout<<"~String()"<<endl;
    }

	void print()const{
        cout<<_pstr<<endl;
    }

    String & append(const String & rhs){
        if(this!=&rhs){
            char* temp=new char[strlen(_pstr)+strlen(rhs._pstr)+1];
            strcpy(temp,_pstr);
            strcat(temp,rhs._pstr);
            delete[] _pstr;
            _pstr=temp;
        }
        return *this;
    }
    
    String & append(const char * pstr){
        char*temp=new char[strlen(_pstr)+strlen(pstr)+1];
        strcpy(temp,_pstr);
        strcat(temp,pstr);
        delete[] _pstr;
        _pstr=temp;
        return *this;
    }
    
    size_t length() const{
        return strlen(this->_pstr);
    }
    
    const char * c_str() const{
        return _pstr;
    }

private:
	char * _pstr;
};

int main()
{
	String str1;
	str1.print();

	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();

    str4.append(str3);
	str4.print();
    str4.append("!");
	str4.print();

    cout<<str4.length()<<endl;
    cout<<str4.c_str()<<endl;
	
	return 0;
}

