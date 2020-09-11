// GreatestDivisorAndLeastMultiple.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

int main()
{
    //int a = 100;//两个整数
    //int b = 110;
    //int c = 0; //临时变量
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
    //std::cout << "最大公约数" << gcd << std::endl;
    //std::cout << "最小公倍数" << lcm << std::endl;
    //getchar();
    //char* p = "hello";
    //gcd = sizeof(p);
    //gcd = strlen(p);
    int i, j, k;										//定义i，j，k为整型
    for (i = 0; i <= 10; i++)								//i是一角钱兑换个数，所以范围从1到10
    {
        for (j = 0; j <= 5; j++)								//j是两角钱兑换个数，所以范围从0到5
        {
            for (k = 0; k <= 2; k++)								//k是五角钱兑换个数，所以范围从0到2
            {
                if (i + j * 2 + k * 5 == 10)								//3种钱数相加是否等于十
                {
                    printf("一角%d个,两角%d个,五角%d个\n", i, j, k);			//将每次可兑换的方案输出
                }
            }
        }
    }
    int* p = nullptr;
    int a = sizeof(nullptr);
    a = sizeof(long);
    return 0;
}

