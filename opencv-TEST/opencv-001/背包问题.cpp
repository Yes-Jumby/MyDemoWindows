#include <algorithm>
#include <iostream>
#include "SpendTime.h"
using namespace std;

struct Thing
{
    int w;//容量
    int v;//价值
}list[101];

int dp[101][101];

int mainbeibao()
{
    cout << sizeof(dp) << endl;
    int s = 5;//背包容量
    int n = 5;//物品总数
    list[0].w = 1; list[0].v = 1;
    list[1].w = 1; list[1].v = 2;
    list[2].w = 1; list[2].v = 3;
    list[3].w = 1; list[3].v = 4;
    list[4].w = 1; list[4].v = 5;
    
    //for (int i = 0; i <= n; i++)
    for (int j = 0; j <= s; j++)
    {
        dp[0][j] = 0;//初始化二维数组
    }
/////////////////////////////////////
    CSpendTime SpendTime;
    SpendTime.Start();

    //for (int i = 1; i <= n; i++)//循环每个物品，执行状态转移方程
    //{
    //    for (int j = s; j >= list[i].w; j--)
    //    {
    //        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - list[i].w] + list[i].v);
    //    }
    //    for (int j = list[i].w - 1; j >= 0; j--)
    //    {
    //        dp[i][j] = dp[i - 1][j];
    //    }
    //}
    //for (int j = 0; j <= s; j++)
    //{
    //    for (int i = 1; i <= n; i++)
    //    {
    //        if (j >= list[i-1].w)
    //        {
    //            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - list[i-1].w] + list[i-1].v);
    //            cout << dp[i][j] << " ";
    //        }
    //        else
    //        {
    //            dp[i][j] = dp[i - 1][j];
    //        }

    //    }
    //    cout << endl;
    //}
    //for (int i = 1; i <= n; ++i)
    //{
    //    for (int j = 0; j <= s; ++j)
    //    {
    //        cout << dp[i][j] << " ";

    //    }

    //    cout << endl;

    //}
    int dp[1000];
    for (int i = 0; i <= s; i++) dp[i] = 0;//初始化二维数组
    for (int i = 0; i < n; i++)//循环每个物品，逆序遍历j执行状态转移方程
    {
        //for (int j = s; j >= list[i].w; j--)
        //{
        //    dp[j] = max(dp[j], dp[j - list[i].w] + list[i].v);
        //}
        for (int j = list[i].w; j <= s; j++)
        {
            dp[j] = max(dp[j], dp[j - list[i].w] + list[i].v);
        }
    }

    //printf("%d\n", dp[s]);
    for (int j = 0; j <= s; ++j)
    {
        cout << dp[j] << " ";

    }
    cout << SpendTime.GetTimeInterval() << endl;
    int temp{ 10000 };
    cout << temp << endl;
    temp = sizeof(dp);
    cout << temp << endl;
    return 0;
}