// ClassInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;

class Father
{
public:
    int m_fMember;
    Father() { cout << "���๹��" << endl; }
    virtual ~Father() { cout << "��������" << endl; }
};


class Child : public Father {
public:
    int m_cMember;
    Child() { cout << "���๹��" << endl; }
    ~Child() { cout << "��������" << endl; }
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
//    Father() { cout << "���๹��"<< endl; }
//    ~Father() { cout << "��������" << endl; }
//};
//
//
//class Child : public Father {
//public:
//    int m_cMember;
//    Child() { cout << "���๹��" << endl; }
//    ~Child() { cout << "��������" << endl; }
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
////    ���๹��
////    ���๹��
////    ��������
////    == == == == == == == == =
////    ���๹��
////    ���๹��
////    ��������
////    ��������
//}

