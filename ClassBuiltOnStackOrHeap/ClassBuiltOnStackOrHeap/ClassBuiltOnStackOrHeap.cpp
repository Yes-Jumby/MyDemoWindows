// ClassBuiltOnStackOrHeap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//class  A//only in heap ��
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

//class  A//only in heap �� �Ľ�
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

class  A//only in stack ջ
{
private:
    void * operator  new (size_t  t) {}      // ע�⺯���ĵ�һ�������ͷ���ֵ���ǹ̶���   
    void  operator  delete (void * ptr) {}  // ������new����Ҫ����delete   
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