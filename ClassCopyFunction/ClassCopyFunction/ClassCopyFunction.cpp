// ClassCopyFunction.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class String
{
public:
    String(const char *str);
    String(const String &other);
    String & operator=(const String &other);
    ~String(void);
private:
    char *m_data;
};

String::String(const char *str)
{
    cout << "自定义构造函数" << endl;
    if (str == NULL)
    {
        m_data = new char[1];
        *m_data = '\0';
    }
    else
    {
        int length = strlen(str);
        m_data = new char[length + 1];
        strcpy_s(m_data, length + 1, str);
    }
}

String::String(const String &other)
{
    cout << "自定义拷贝构造函数" << endl;
    int length = strlen(other.m_data);
    m_data = new char[length + 1];
    strcpy_s(m_data, length + 1, other.m_data);
}

String & String::operator=(const String &other)
{
    cout << "自定义赋值函数" << endl;

    if (this == &other)
    {
        return *this;
    }
    else
    {
        delete[] m_data;
        int length = strlen(other.m_data);
        m_data = new char[length + 1];
        strcpy_s(m_data,length + 1,other.m_data);
        return *this;
    }
}

String::~String(void)
{
    cout << "自定义析构函数" << endl;
    delete[] m_data;
}
int main()
{
    cout << "a(\"abc\")" << endl;
    String a("abc"); //自定义构造函数

    cout << "b(\"cde\")" << endl;
    String b("cde");//自定义构造函数

    cout << " d = a" << endl;
    String d = a;//自定义拷贝构造函数

    cout << "c(b)" << endl;
    String c(b);//自定义拷贝构造函数

    cout << "c = a" << endl;
    c = a;//自定义赋值构造函数

    cout << endl;
}

