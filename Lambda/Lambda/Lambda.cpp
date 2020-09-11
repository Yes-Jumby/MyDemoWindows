// Lambda.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return  a < b;
}

struct MyStruct
{
        static char dda1;
        short d;
        char dda;
    
        struct MyStruct1
        {
            char dda1;
            short d;
            char dda;

            int type;
        };
        MyStruct1 s;
    private :
        static void K() {}
    int type;
};

struct A1
{
    char a;
    short b;
    char c;
    int d;
};

struct A2
{
    char a;

    char c;
    short b;
    int d;
};

struct A3
{
    char a;
    short b;
    int d;
    char c;

};

class A
{
public:
    A()
    {
        data = 0;
        cout << "A()" << data << endl;
    }
    ~A()
    {
        cout << "~A()" << data << endl;
    }
    A(int a)
    {
        data = a;
        cout << "A(int a)" << data << endl;
    }
    A(const A &a)
    {
        data = a.data;
        cout << "A(const A &a)" << data << endl;
    }
    A(const A &&a)
    {
        data = a.data;
        cout << "A(const A &&a)" << data << endl;
    }
    A &operator=(const A&src)
    {
        if (this != &src)
        {
            data = src.data;
        }
        cout << "A &operator=(const A&src)" << data <<endl;
        return *this;
    }
    int data;
};
A Increase(A a)
{
    A temp = a;
    temp.data += 1;
    return temp;

}
void test()
{
    A a(1);
    //A B(2);
    A b = Increase(a);
    //a = b;
}

#include <iostream>

using namespace std;

int  f1()
{
    cout << "f1" << endl;
    return 1;
}
int  f2()
{
    cout << "f2" << endl;
    return 2;
}
int  f3()
{
    cout << "f3" << endl;
    return 3;
}

//int main()
//{
//    cout << "first--" << f1() << "   second--" << f2() << "   third--" << f3() << endl;
//    return 0;
//}
int main()
{
    //cout << sizeof(A1) << endl;//12
    //cout << sizeof(A2) << endl;//8
    //cout << sizeof(A3) << endl;//12
    test();

    cout << "first--" << f1() << "   second--" << f2() << "   third--" << f3() << endl;

    system("pause");
    return 0;
}

