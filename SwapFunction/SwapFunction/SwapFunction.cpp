// SwapFunction.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include<iostream>
#include<string>
#include<algorithm>//sort函数包含的头文件
using namespace std;
//定义一个学生类型的结构体
typedef struct student
{
    string name;           //学生姓名
    int achievement;     //学生成绩
} student;




//用来显示学生信息的函数
void show(student *stu, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "姓名:" << stu[i].name << '\t' << "成绩:" << stu[i].achievement << endl;
    }
}

int main()
{
    student stu[] = { { "张三四",99 },{ "李四",87 },{ "王二",100 } ,{ "麻子",60 } };
    cout << "交换前：" << endl;
    show(stu, 4);
    swap(stu[0], stu[3]);
    cout << "交换后：" << endl;
    show(stu, 4);

    float a = 3.123456, b = 1234567.000000;
    swap(a, b);
    cout << fixed;
    cout << a << "->" << b << endl;
    return 0;
}
