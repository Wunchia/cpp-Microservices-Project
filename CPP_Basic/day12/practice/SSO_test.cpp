#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

class String{
public:
    String(const char*pstr){
        _size=strlen(pstr);

        if(_size<16){
            _capacity=15;
            strcpy(_buffer._local,pstr);
        }else{
            _capacity=_size;
            _buffer._pointer=new char[_size+1];
            strcpy(_buffer._pointer,pstr);
        }
    }

    ~String(){
        if(_size>=16){
            delete[] _buffer._pointer;
            _buffer._pointer=nullptr;
        }
    }

    char &operator[](size_t idx){
        if(_size<16){
            return _buffer._local[idx];
        }else{
            return _buffer._pointer[idx];
        }
    }

    friend ostream& operator<<(ostream &os,const String& rhs){
        if(rhs._size<16){
            os<<rhs._buffer._local;
        }else{
            os<<rhs._buffer._pointer;
        }
        return os;
    }

    void print()const{
        cout<<"Content: "<<*this
            <<" | Size:"<<_size
            <<" | Capacity:"<<_capacity
            <<" | Location:"<<(_size<16?"Stack(Local)":"Heap(Pointer)")
            <<endl;
    }

private:
    union Buffer{
        char*_pointer;
        char _local[16];
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

void test(){
    String str1("hello");
    str1.print();

    String str2("hello,world!!!!C++!!!!!!!REDIS!!!!!!!!!!!");
    str2.print();

    cout<<"str1[2]:"<<str1[2]<<endl;
    cout<<"str2[20]:"<<str2[20]<<endl;
}

int main(int argc,char *argv[])
{
    test(); 
    return 0;
}

