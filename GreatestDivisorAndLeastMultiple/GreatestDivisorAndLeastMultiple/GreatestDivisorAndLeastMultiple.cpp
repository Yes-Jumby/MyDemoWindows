// GreatestDivisorAndLeastMultiple.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

int main()
{
    //int a = 100;//��������
    //int b = 110;
    //int c = 0; //��ʱ����
    //int ra = a;
    //int rb = b;
    //int lcm, gcd;
    //while (a%b != 0)
    //{
    //    c = a%b;
    //    a = b;
    //    b = c;
    //}
    //gcd = b;
    //lcm = ra*rb / gcd;
    //std::cout << "���Լ��" << gcd << std::endl;
    //std::cout << "��С������" << lcm << std::endl;
    //getchar();
    //char* p = "hello";
    //gcd = sizeof(p);
    //gcd = strlen(p);
    int i, j, k;										//����i��j��kΪ����
    for (i = 0; i <= 10; i++)								//i��һ��Ǯ�һ����������Է�Χ��1��10
    {
        for (j = 0; j <= 5; j++)								//j������Ǯ�һ����������Է�Χ��0��5
        {
            for (k = 0; k <= 2; k++)								//k�����Ǯ�һ����������Է�Χ��0��2
            {
                if (i + j * 2 + k * 5 == 10)								//3��Ǯ������Ƿ����ʮ
                {
                    printf("һ��%d��,����%d��,���%d��\n", i, j, k);			//��ÿ�οɶһ��ķ������
                }
            }
        }
    }
    int* p = nullptr;
    int a = sizeof(nullptr);
    a = sizeof(long);
    return 0;
}

