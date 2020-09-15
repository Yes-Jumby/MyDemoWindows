#include <algorithm>
#include <iostream>
#include "SpendTime.h"
using namespace std;
//三角问题
#define MAX 101
int D[MAX][MAX];
int n;
int maxSum[MAX][MAX];

int maindynamic()
{
    //init
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            maxSum[i][j] = -1;
        }
    }

    n = 5;
    D[1][1] = 7;
    D[2][1] = 3; D[2][2] = 8;
    D[3][1] = 8; D[3][2] = 1; D[3][3] = 0;
    D[4][1] = 2; D[4][2] = 7; D[4][3] = 4; D[4][4] = 4;
    D[5][1] = 4; D[5][2] = 5; D[5][3] = 2; D[5][4] = 6; D[5][5] = 5;

    CSpendTime SpendTime;
    SpendTime.Start();

    //for (int i = 1; i <= n; i++)
    //{
    //    maxSum[n][i] = D[n][i];
    //}
    //for (int i = n - 1; i <= n; --i)
    //{
    //    for (int j = 1; j <= i; ++j)
    //        maxSum[i][j] = max(maxSum[i+1][j], maxSum[i+1][j+1]) + D[i][j];
    //}
    //cout << n << endl;
    //for (int i = 1; i <= n; ++i)
    //{
    //    for (int j = 1; j <= i; ++j)
    //    {
    //        cout << maxSum[i][j] << " ";
    //    }
    //    cout << endl;

    //}
    //cout << maxSum[1][1] << endl;
    //空间优化
    int *suum;
    suum = D[n];
    for (int i = 1; i <= n; ++i)
    {
        cout << suum[i] << " ";

        cout << endl;

    }
     for (int i = n - 1; i >= 1; --i)
    {
         for (int j = 1; j <= i; ++j)
         {
             suum[j] = max(suum[j], suum[j + 1]) + D[i][j];
             //cout << suum[i] << " "<< D[i][j]<<" ";
         }
         cout <<"i:"<<i<< endl;
    }
    for (int i = 1; i <= n; ++i)
    {
            cout << suum[i]<< " ";

        cout << endl;

    }
    

    cout << SpendTime.GetTimeInterval() << endl;
    return 0;
}
//递归调用
//int MaxSum(int i, int j)
//{
//    if (maxSum[i][j] != -1)
//    {
//        return maxSum[i][j];
//    }
//    if (i == n)
//        return D[i][j];
//    int x = MaxSum(i + 1, j);
//    int y = MaxSum(i+1, j + 1);
//    return max(x, y) + D[i][j];
//}
//int main()
//{
//    for (int i = 0; i < MAX; i++)
//    {
//        for (int j = 0; j < MAX; j++)
//        {
//            maxSum[i][j] = -1;
//        }
//    }
//
//    n = 5;
//    D[1][1] = 7;
//    D[2][1] = 3; D[2][2] = 8;
//    D[3][1] = 8; D[3][2] = 1; D[3][3] = 0;
//    D[4][1] = 2; D[4][2] = 7; D[4][3] = 4; D[4][4] = 4;
//    D[5][1] = 4; D[5][2] = 5; D[5][3] = 2; D[5][4] = 6; D[5][5] = 5;
//    CSpendTime SpendTime;
//    SpendTime.Start();
//
//    cout << MaxSum(1, 1) << endl;
//
//    cout << SpendTime.GetTimeInterval() << endl;
//    return 0;
//}

