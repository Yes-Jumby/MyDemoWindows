// ClassMemory.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;
class A {
public:
    int a;
};//sizeof(A) = 4  

class B : virtual public A {
};// sizeof(B) =4+4=8  

class C : virtual public A {
};//sizeof(C) =4+4=8  

class D : public B, public C {
};
//sizeof(D)=8+8-4=12 ������Ҫע��Ҫ��ȥ4����ΪB��Cͬʱ�̳�A��ֻ��Ҫ����һ��A�ĸ����ͺ��ˣ�sizeof(D)=4(A�ĸ���)+4(B�����)+4(C�����)=12  

int main() {
    printf("%d\n", sizeof(D));
    A a;
    B b;
    C c;
    D d;
    return 0;
}

