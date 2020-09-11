//extern "C"https://github.com/CannyLab/tsne-cuda/issues/18
//void runCudaPart();
#include "cudacu/kernel.h"
int main()
{
    getDeviceInfo();
    runCudaPart();
}
