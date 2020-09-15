#include<iostream>
#include<map>
#include <memory>
using namespace std;
typedef enum PointerNames
{
    RAN_C,
    REF_C,
    SCA_C
}PtrN;
int mainmap()
{
    map<PtrN, void *> mp;
    
    std::unique_ptr<float[]>rangeOut;
    std::unique_ptr<unsigned char[]>reflectanceOut;
    rangeOut = std::make_unique<float[]>(5);
    reflectanceOut = std::make_unique<unsigned char[]>(5);
    float *pFloat = rangeOut.get();
    pFloat[0] = 100;
    pFloat[1] = 2000;
    mp.insert({ RAN_C,rangeOut.get() });
    mp.insert({ RAN_C,rangeOut.get() });
    mp.insert({ RAN_C,rangeOut.get() });
    cout << mp.count(RAN_C) << endl;
    pFloat[0] = 1;
    pFloat[1] = 200;
    pFloat = (float*)mp[RAN_C];
    for (int i = 0; i < 5; i++)
        cout << pFloat[i] << endl;
    system("PAUSE");
    return 0;
}