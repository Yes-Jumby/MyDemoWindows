// Finalclass.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;

template <typename T>
class Base 
{
    friend T;
private:
    Base() 
    {
        cout << "base" << endl;
    }
    ~Base() {}
};

class B :virtual public Base<B> 
{   //һ��ע�� ��������̳�
public:
    B() 
    {
        cout << "B" << endl;
    }
};

class C :public B 
{
public:
    //C() {}     //�̳�ʱ�����޷�ͨ������
};


int main() 
{
    B b;      //B���޷����̳�
    B* a = new B();
    //C c;
    return 0;
}
//https://www.cnblogs.com/yanenquan/p/4006691.html