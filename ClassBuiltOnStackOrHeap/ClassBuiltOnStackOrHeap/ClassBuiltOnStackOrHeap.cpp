// ClassBuiltOnStackOrHeap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//class  A//only in heap 堆
//{
//public:
//    A() {}
//    void  destory() { delete   this; }
//private:
//    ~A() {}
//};

//int main()
//{
//    A * a = new A();
//    //A aa;
//    return 0;
//}

//class  A//only in heap 堆 改进
//{
//protected:
//    A() {}
//    ~A() {}
//public:
//    static  A* create()
//    {
//        return   new  A();
//    }
//    void  destory()
//    {
//        delete   this;
//    }
//};
//
//int main()
//{
//    A * a = A::create();
//    a->destory();
//    //A aa;
//    return 0;
//}

class  A//only in stack 栈
{
private:
    void * operator  new (size_t  t) {}      // 注意函数的第一个参数和返回值都是固定的   
    void  operator  delete (void * ptr) {}  // 重载了new就需要重载delete   
public:
    A() {}
    ~A() {}
};

int main()
{
    A  aa;
    //A  *a = new A();
    //A aa;
    return 0;
}