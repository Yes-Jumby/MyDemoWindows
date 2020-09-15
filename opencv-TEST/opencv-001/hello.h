#pragma once
#include <algorithm>
#include <iostream>
#include "SpendTime.h"
using namespace std;

int main0000()
{
    CSpendTime SpendTime;
    SpendTime.Start();

    cout << SpendTime.GetTimeInterval() << endl;
    return 0;
}