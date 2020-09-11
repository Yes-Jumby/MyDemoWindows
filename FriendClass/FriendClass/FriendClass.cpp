// FriendClass.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

////////////////////类的成员函数是友元函数////////////////////


class A;    //当用到友元成员函数时，需注意友元声明与友元定义之间的互相依赖。这是类A的声明
class B
{
public:
    void set_show(int x, A &a);             //该函数是类A的友元函数
};

class A
{
public:
    friend void B::set_show(int x, A &a);   //该函数是友元成员函数的声明
private:
    int data;
    void show() 
    { 
        cout << data << endl; 
    }
};

void B::set_show(int x, A &a)       //只有在定义类A后才能定义该函数，毕竟，它被设为友元是为了访问类A的成员
{
    a.data = x;
    cout << a.data << endl;
}
/////////////类是友元////////////////

class Window;

class Screen
{
    friend class Window;
private:
    int data = 100;
    void show()
    {
        cout << data << endl;
    }
    
};
class Window
{
public:
    void show(Screen s)
    {
        s.show();
        cout << s.data << endl;
    }
};
int main(void)
{
    class A a;
    class B b;

    b.set_show(8, a);

    Screen s;
    Window w;
    w.show(s);
    system("PAUSE");

    return 0;
}