// SwapFunction.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include<iostream>
#include<string>
#include<algorithm>//sort����������ͷ�ļ�
using namespace std;
//����һ��ѧ�����͵Ľṹ��
typedef struct student
{
    string name;           //ѧ������
    int achievement;     //ѧ���ɼ�
} student;




//������ʾѧ����Ϣ�ĺ���
void show(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "����:" << stu[i].name << '\t' << "�ɼ�:" << stu[i].achievement << endl;
    }
}

int main()
{
    student stu[] = { { "������",99 },{ "����",87 },{ "����",100 } ,{ "����",60 } };
    cout << "����ǰ��" << endl;
    show(stu, 4);
    swap(stu[0], stu[3]);
    cout << "������" << endl;
    show(stu, 4);

    float a = 3.123456, b = 1234567.000000;
    swap(a, b);
    cout << fixed;
    cout << a << "->" << b << endl;
    return 0;
}
