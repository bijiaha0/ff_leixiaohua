#ifndef __MYSTRING__
#define __MYSTRING__

//class带有指针成员变量，就一定要写拷贝构造和拷贝赋值。
class String {
public:
    String(const char *cstr = 0);
    //拷贝构造(深拷贝)
    String(const String &str);
    //拷贝赋值
    String &operator=(const String &str);
    //析构函数
    ~String();
    //一般的成员函数
    char *get_c_str() const { return m_data; }

private:
    char *m_data;
};

#include <cstring>

inline
String::String(const char *cstr) {
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    } else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::~String() {
    //释放动态分配的内存
    delete[] m_data;
}

inline
String &String::operator=(const String &str) {
    //0、检测自我赋值
    if (this == &str)
        return *this;

    //1、清旧数据
    delete[] m_data;

    //2、
    m_data = new char[strlen(str.m_data) + 1];

    //3、
    strcpy(m_data, str.m_data);

    return *this;
}

inline
String::String(const String &str) {
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

#include <iostream>

using namespace std;

//打印
ostream &operator<<(ostream &os, const String &str) {
    os << str.get_c_str();
    return os;
}

#endif
