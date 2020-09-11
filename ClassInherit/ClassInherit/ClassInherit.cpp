// ClassInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;

class Father
{
public:
    int m_fMember;
    Father() { cout << "父类构造" << endl; }
    virtual ~Father() { cout << "父类析构" << endl; }
};


class Child : public Father {
public:
    int m_cMember;
    Child() { cout << "子类构造" << endl; }
    ~Child() { cout << "子类析构" << endl; }
};


int main(int argc, char** argv)
{
    Father* pObj1 = new Child();
    delete pObj1;
    cout << "=================" << endl;
    Child* pObj2 = new Child();
    delete pObj2;
    return 0;
}

//class Father
//{
//public:
//    int m_fMember;
//    Father() { cout << "父类构造"<< endl; }
//    ~Father() { cout << "父类析构" << endl; }
//};
//
//
//class Child : public Father {
//public:
//    int m_cMember;
//    Child() { cout << "子类构造" << endl; }
//    ~Child() { cout << "子类析构" << endl; }
//};
//
//
//int main(int argc, char** argv)
//{
//    Father* pObj1 = new Child();
//    delete pObj1;
//    cout << "=================" << endl;
//    Child* pObj2 = new Child();
//    delete pObj2;
//    return 0;
////    父类构造
////    子类构造
////    父类析构
////    == == == == == == == == =
////    父类构造
////    子类构造
////    子类析构
////    父类析构
//}

