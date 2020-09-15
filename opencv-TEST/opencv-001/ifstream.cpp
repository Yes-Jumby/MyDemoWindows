#include <chrono>
#include <iostream>
#include "readAndWriteDat.h"
#include "SpendTime.h"
using namespace std;
int mainiostream()
{
    CReadAndWriteDat ReadAndWriteDat;
    CSpendTime SpendTime;
    //ReadAndWriteDat.readbinToCloud1("D://myDat.dat");
    int size = 1000000;
    SpendTime.Start();
    ReadAndWriteDat.writeToCloudslow("E://temp//slow.txt", size);

    cout << SpendTime.GetTimeInterval() << endl;;

    SpendTime.Start();
    ReadAndWriteDat.writeToCloudfast("E://temp//fast.txt", size);
    cout << SpendTime.GetTimeInterval() << endl;;
	return 0;
}



