// FriendClass.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;

////////////////////��ĳ�Ա��������Ԫ����////////////////////


class A;    //���õ���Ԫ��Ա����ʱ����ע����Ԫ��������Ԫ����֮��Ļ���������������A������
class B
{
public:
    void set_show(int x, A &a);             //�ú�������A����Ԫ����
};

class A
{
public:
    friend void B::set_show(int x, A &a);   //�ú�������Ԫ��Ա����������
private:
    int data;
    void show() 
    { 
        cout << data << endl; 
    }
};

void B::set_show(int x, A &a)       //ֻ���ڶ�����A����ܶ���ú������Ͼ���������Ϊ��Ԫ��Ϊ�˷�����A�ĳ�Ա
{
    a.data = x;
    cout << a.data << endl;
}
/////////////������Ԫ////////////////

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