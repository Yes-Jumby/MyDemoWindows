// Finalclass.cpp : 定义控制台应用程序的入口点。
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
{   //一定注意 必须是虚继承
public:
    B() 
    {
        cout << "B" << endl;
    }
};

class C :public B 
{
public:
    //C() {}     //继承时报错，无法通过编译
};


int main() 
{
    B b;      //B类无法被继承
    B* a = new B();
    //C c;
    return 0;
}
//https://www.cnblogs.com/yanenquan/p/4006691.html