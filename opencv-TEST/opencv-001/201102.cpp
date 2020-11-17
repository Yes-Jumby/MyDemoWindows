#include "readAndWriteDat.h"
void main201102()
{
    std::cout << "sizeof(Cloud3D):" << sizeof(Cloud3D) << std::endl;
    CReadAndWriteDat ReadAndWriteDat_;
    bool flag =ReadAndWriteDat_.readbinToImage("E:\\370156551383600.dat");
    std::cout << flag << std::endl;
    return;
}