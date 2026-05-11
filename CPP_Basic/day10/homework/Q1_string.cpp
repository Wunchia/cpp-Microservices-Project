#include <iostream>
#include <vector>
#include <istream>
#include <string.h>
#include <sstream>

using namespace std;

class String
{
public:
    String()
    :_pstr(new char[1])
    {
        _pstr[0] = '\0';
    };
    
    String(const char *pstr) 
    : _pstr(new char[strlen(pstr) + 1])
    {
        cout << "constructor" << endl;
        strcpy(_pstr, pstr);
    }
    
    String(const String &s) 
    : _pstr(new char[strlen(s._pstr) + 1])
    {
        strcpy(_pstr, s._pstr);
    }
    
    ~String()
    {
        if (_pstr != nullptr)
        {
            delete[] _pstr;
        }
        _pstr = nullptr;
    }

    String &operator=(const String &s)
    {
        if (this != &s)
        {
            delete[] _pstr;
            _pstr = new char[strlen(s._pstr) + 1];
            strcpy(_pstr, s._pstr);
        }

        return *this;
    }
    String &operator=(const char *pstr)
    {
        delete[] _pstr;
        _pstr = new char[strlen(pstr) + 1];
        strcpy(_pstr, pstr);
        return *this;
    }

    String &operator+=(const String &s)
    {
        char *tmp = _pstr;
        _pstr = new char[strlen(tmp) + strlen(s._pstr) + 1];
        strcpy(_pstr, tmp);
        strcat(_pstr, s._pstr);
        delete[] tmp;
        return *this;
    }
    String &operator+=(const char *pstr)
    {
        char *tmp = _pstr;
        _pstr = new char[strlen(tmp) + strlen(pstr) + 1];
        strcpy(_pstr, tmp);
        strcat(_pstr, pstr);
        delete[] tmp;
        return *this;
    }

    char &operator[](std::size_t index)
    {
            return _pstr[index];
       
    }
    const char &operator[](std::size_t index) const
    {
            return _pstr[index];
  
    }

    std::size_t size() const
    {
        return strlen(_pstr);
    }
    const char *c_str() const
    {
        return _pstr;
    }

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
};

inline String operator+(const String &lhs, const String &rhs)
{
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}
inline String operator+(const String &lhs, const char *rhs)
{
    return lhs + String(rhs);
}
inline String operator+(const char *lhs, const String &rhs)
{
    return rhs + String(lhs);
}

inline bool operator==(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}

inline bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

inline bool operator<(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

inline bool operator>(const String &lhs, const String &rhs)
{
    return rhs < lhs;
}

inline bool operator<=(const String &lhs, const String &rhs)
{
    return !(rhs < lhs);
}

inline bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}

inline ostream &operator<<(ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}

istream &operator>>(istream &is, String &s)
{
    while (is && isspace(is.peek()))
    {
        is.get();
    }
    const int INITIAL = 16;
    char *buf = new char[INITIAL];
    int capacity = INITIAL;
    int len = 0;

    int ch;
    while (is && !isspace(ch = is.get()) && ch != EOF)
    {
        if (len + 1 >= capacity)
        {
            capacity *= 2;
            char *newbuf = new char[capacity];
            memcpy(newbuf, buf, len);
            delete[] buf;
            buf = newbuf;
        }
        buf[len++] = static_cast<char>(ch);
    }

    buf[len] = '\0';
    s = buf;
    delete[] buf;
    return is;
}

int main() {
 
    String s2("Hello");
    cout << "s2: \"" << s2 << "\" (length: " << s2.size() << ")" << endl;

    String s3(s2);
    cout << "s3 (copy of s2): \"" << s3 << "\"" << endl;

    String s4;
    s4 = s2;
    cout << "s4 (assigned from s2): \"" << s4 << "\"" << endl;
    s4 = "World";
    cout << "s4 (assigned from C-string): \"" << s4 << "\"" << endl;

   
    String s5("Hello");
    s5 += String(" C++");
    cout << "s5 after += String: \"" << s5 << "\"" << endl;
    s5 += " !";
    cout << "s5 after += C-string: \"" << s5 << "\"" << endl;

  
    String s6 = s2 + String(" World");
    cout << "s2 + String(\" World\") = \"" << s6 << "\"" << endl;
    String s7 = s6 + " from operator";
    cout << "s6 + C-string = \"" << s7 << "\"" << endl;
    String s8 = "Prefix " + s7;
    cout << "C-string + s7 = \"" << s8 << "\"" << endl;

    const String s9("ConstString");
    cout << "s9[3] = " << s9[3] << endl;      // 's'
    s5[0] = 'h';
    cout << "s5 after modification: " << s5 << endl;

    String a("Apple"), b("Banana"), c("Apple");
    cout << "a == c: " << (a == c) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a < b:  " << (a < b) << endl;
    cout << "b > a:  " << (b > a) << endl;
    cout << "a <= c: " << (a <= c) << endl;
    cout << "a >= c: " << (a >= c) << endl;

    istringstream iss("   HelloWorld   C++String");
    String input1, input2;
    iss >> input1 >> input2;
    cout << "Read from stream (first word): \"" << input1 << "\"" << endl;
    cout << "Read from stream (second word): \"" << input2 << "\"" << endl;


    String empty;
    empty += "NonEmpty";
    cout << "Empty after +=: \"" << empty << "\"" << endl;

    String self("self");
    self = self;
    cout << "Self assignment: " << self << endl;

    String test("Test");
    cout << "Size of \"" << test << "\": " << test.size() << endl;
    cout << "c_str(): " << test.c_str() << endl;

    cout << "\nAll tests finished (no assertions used)." << endl;
    return 0;
}