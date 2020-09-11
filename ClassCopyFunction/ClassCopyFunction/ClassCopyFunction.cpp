// ClassCopyFunction.cpp : �������̨Ӧ�ó������ڵ㡣
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
    cout << "�Զ��幹�캯��" << endl;
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
    cout << "�Զ��忽�����캯��" << endl;
    int length = strlen(other.m_data);
    m_data = new char[length + 1];
    strcpy_s(m_data, length + 1, other.m_data);
}

String & String::operator=(const String &other)
{
    cout << "�Զ��帳ֵ����" << endl;

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
    cout << "�Զ�����������" << endl;
    delete[] m_data;
}
int main()
{
    cout << "a(\"abc\")" << endl;
    String a("abc"); //�Զ��幹�캯��

    cout << "b(\"cde\")" << endl;
    String b("cde");//�Զ��幹�캯��

    cout << " d = a" << endl;
    String d = a;//�Զ��忽�����캯��

    cout << "c(b)" << endl;
    String c(b);//�Զ��忽�����캯��

    cout << "c = a" << endl;
    c = a;//�Զ��帳ֵ���캯��

    cout << endl;
}

