// VirtualBase.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;
class A {
protected:
    int a;
public:
    A(int a) :a(a) {}
};
class B : virtual public A {  //���������
protected:
    int b;
public:
    B(int a, int b) :A(a), b(b) {}
};
class C : virtual public A {  //���������
protected:
    int c;
public:
    C(int a, int c) :A(a), c(c) {}
};
class D : virtual public B, virtual public C {  //���������
private:
    int d;
public:
    D(int a, int b, int c, int d) :A(a), B(a, b), C(a, c), d(d) {}
    void display();
};
void D::display() {
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "d=" << d << endl;
}
int main() {
    (new D(1, 2, 3, 4))->display();
    return 0;
}

