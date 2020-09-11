// ClassMemory.cpp : 定义控制台应用程序的入口点。
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
//sizeof(D)=8+8-4=12 这里需要注意要减去4，因为B和C同时继承A，只需要保存一个A的副本就好了，sizeof(D)=4(A的副本)+4(B的虚表)+4(C的虚表)=12  

int main() {
    printf("%d\n", sizeof(D));
    A a;
    B b;
    C c;
    D d;
    return 0;
}

