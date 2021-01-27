
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
//using namespace cv;
using namespace std;
cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);



#define Row  8
#define Col 4


__global__ void addKernel(int **C, int **A)
{
	int idx = threadIdx.x + blockDim.x * blockIdx.x;
	int idy = threadIdx.y + blockDim.y * blockIdx.y;
	if (idx < Col && idy < Row) {
		C[idy][idx] = A[idy][idx] + 10;
	}
}


__global__ void addKernel(int *c, const int *a, const int *b)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

__global__ void add3DKernelTHREAD(int* a,int *c)
{
    int x = threadIdx.x-1;
    int y = threadIdx.y-1;
    int z = threadIdx.z-1; 
    int iThreadIndex = threadIdx.x + threadIdx.y*blockDim.x + threadIdx.z*blockDim.x*blockDim.y;

    c[iThreadIndex * 3] = threadIdx.x - 1;
    c[iThreadIndex * 3 + 1] = threadIdx.y - 1;
    c[iThreadIndex * 3 + 2] = threadIdx.z - 1;
}
__global__ void add3DKernelBLOCK(int* a, int *c)
{
    int x = blockIdx.x - 1;
    int y = blockIdx.y - 1;
    int z = blockIdx.z - 1;
    int iBlockIndex = blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y;
    //c[cuurrentindex] = a[cuurr - 1entindex*3]+ a[cuurrentindex * 3+1]*10+ a[cuurrentindex * 3+2]*100;
    //c[cuurrentindex * 3] = a[cuurrentindex * 3];
    //c[cuurrentindex * 3+1] = a[cuurrentindex * 3 + 1];
    //c[cuurrentindex * 3+2] = a[cuurrentindex * 3 + 2];

    c[iBlockIndex * 3] = blockIdx.x - 1;
    c[iBlockIndex * 3 + 1] = blockIdx.y - 1;
    c[iBlockIndex * 3 + 2] = blockIdx.z - 1;
}
__global__ void add3DKernelTHREADBLOCK(int *c)
{
    int iBlockIndex = blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y;
    int iThreadIndex = threadIdx.x + threadIdx.y*blockDim.x + threadIdx.z*blockDim.x*blockDim.y;
    int iCurrentIndex;

    iCurrentIndex = iThreadIndex + iBlockIndex*blockDim.x*blockDim.y*blockDim.z;
    c[iCurrentIndex] = iCurrentIndex;

    
}
__global__ void add3DKernelTHREADBLOCK1(int *c)
{
	int iBlockIndex = blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y;
	int iThreadIndex = threadIdx.x + threadIdx.y*blockDim.x + threadIdx.z*blockDim.x*blockDim.y;
	int iCurrentIndex;

	iCurrentIndex = iThreadIndex + iBlockIndex*blockDim.x*blockDim.y*blockDim.z;
	c[iCurrentIndex] = iCurrentIndex;


}
__global__ void myTHREADBLOCK(int *d_in,int *d_out,int* size)
{

	int idx = blockIdx.x*blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	while (idx < 10)
	{
		if (d_in[idx] > 0 && d_in[idx] < 6)
		{
			int ind = atomicAdd(size, 1);
			d_out[ind] = d_in[idx];
		}
		
		idx += stride;
	}
}

__global__ void myTHREADBLOCK1(float(*d_GPU)[3], float (*h_GPU)[3], int SIZE)
{

	int idx = blockIdx.x*blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	while (idx < 27)
	{
		
		float *d = (float*)((char*)d_GPU + 512 * idx);
		float *h = (float*)((char*)h_GPU + 512 * idx);
		h[0] = d[0];
		h[1] = d[1];
		h[2] = d[2];
		idx += stride;
	}
}
__global__ void myTHREADBLOCK111(int **d_GPU,int*d)
{

	int idx = blockIdx.x*blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	if (idx == 1)
	{
		//int * p = d_GPU[0];
		//int * p1 = d_GPU[1];
		d[0] = 122;
		d[1] = 1222;
		d[2] = d_GPU[1][0];
		d[3] = 1;
		d[4] = 2;
	}
		

}
__global__ void Mytest(float *dev_keys, float *dev_values)
{
	//__shared__ float cache[5];
	////cache[0] = 100.0f;
	//int idx = blockIdx.x*blockDim.x + threadIdx.x;
	//int stride = blockDim.x * gridDim.x;

	//if (idx == 0)
	//{
	//	for (int i = 0; i < 5; i++)
	//	{
	//		dev_keys[i] = cache[i];
	//	}
	//}
	/*return;*/
	/*switch (idx)
	{
	case 1:
		;
		break;
	case 2:
		dev_keys[idx] = __fadd_rn(dev_values[0], dev_values[1]);
		break;
	case 3:
		dev_keys[idx] = __fadd_ru(dev_values[0], dev_values[1]);
		break;
	case 4:
		dev_keys[idx] = __fadd_rz(dev_values[0], dev_values[1]);
		break;
	default:
		break;
	}*/


}

#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/sequence.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/replace.h>
#include <thrust/count.h>
#include <thrust/functional.h>
#include <iostream>
#include <Windows.h>
#define gpuErrchk(severity_level, ans) \
    if (ans != cudaSuccess)\
    {\
        std::string func_info = FUNCTION_INFO; \
        cudaError_t err_code = ans;\
        throw ExceptionsS3D(cudaGetErrorString(err_code), func_info);\
    }
//int main(void)
//{
//	LARGE_INTEGER m_liPerfFreq = { 0 };
//	//获取每秒多少CPU Performance Tick 
//	QueryPerformanceFrequency(&m_liPerfFreq);
//	LARGE_INTEGER m_liPerfStart = { 0 };
//	QueryPerformanceCounter(&m_liPerfStart);
//	LARGE_INTEGER m_liPerfEnd = { 0 };
//	int point_cloud_size = 8000000;
//	int hashvaluearray_size = 27 * point_cloud_size;
//	int *d_hashtable;//每个点的哈希值
//	cudaMalloc((void**)&d_hashtable, point_cloud_size * sizeof(int));
//	int *d_hashtableold;//每个点的哈希值
//	cudaMalloc((void**)&d_hashtableold, point_cloud_size * sizeof(int));
//	int *d_hashindex;
//	cudaMalloc((void**)&d_hashindex, point_cloud_size * sizeof(int));
//	int* d_hashvaluearray;
//	cudaMalloc((void**)&d_hashvaluearray, hashvaluearray_size * sizeof(int));
//	// 计算CPU运行到现在的时间
//	QueryPerformanceCounter(&m_liPerfEnd);
//	int time = (((m_liPerfEnd.QuadPart - m_liPerfStart.QuadPart) * 1000) / m_liPerfFreq.QuadPart);//ms
//	printf("Pre Time Slaps:%d ms\n", time);
//	//计算hash值-排序-获取大小和起始值-创建哈希值列表-前处理-去噪
//
//	QueryPerformanceCounter(&m_liPerfStart);
//	cudaFree(d_hashtable);
//	cudaFree(d_hashindex);
//	cudaFree(d_hashtableold);
//	cudaFree(d_hashvaluearray);
//	QueryPerformanceCounter(&m_liPerfEnd);
//	time = (((m_liPerfEnd.QuadPart - m_liPerfStart.QuadPart) * 1000) / m_liPerfFreq.QuadPart);//ms
//	printf("Release Resource Time Slaps:%d ms\n", time);
//
//	QueryPerformanceCounter(&m_liPerfStart);
//	int *d_data;//每个点的哈希值
//	cudaMalloc((void**)&d_data, 30*point_cloud_size * sizeof(int));
//	// 计算CPU运行到现在的时间
//	QueryPerformanceCounter(&m_liPerfEnd);
//	time = (((m_liPerfEnd.QuadPart - m_liPerfStart.QuadPart) * 1000) / m_liPerfFreq.QuadPart);//ms
//	printf("Pre Time Slaps:%d ms\n", time);
//
//	QueryPerformanceCounter(&m_liPerfStart);
//	cudaFree(d_data);
//	QueryPerformanceCounter(&m_liPerfEnd);
//	time = (((m_liPerfEnd.QuadPart - m_liPerfStart.QuadPart) * 1000) / m_liPerfFreq.QuadPart);//ms
//	printf("Release Resource Time Slaps:%d ms\n", time);
//	system("PAUSE");
//	return 0;
//}

#define getTimeGeneral(clock_t_)  (clock_t_)*1.0/ CLOCKS_PER_SEC * 1000
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
int main111()
{
	//int deviceCount;
	//cudaGetDeviceCount(&deviceCount);
	//int device;
	//cudaDeviceProp deviceProp;
	//for (device = 0; device < deviceCount; ++device)
	//{
	//	cudaGetDeviceProperties(&deviceProp, device);
	//	printf("Device %d has compute capability %d.%d.\n",
	//		device, deviceProp.major, deviceProp.minor);
	//	cout << "regsPerBlock:" << deviceProp.regsPerBlock << endl;
	//	cout << "maxThreadsPerBlock:" << deviceProp.maxThreadsPerBlock << endl;
	//	cout << "sharedMemPerBlock:" << deviceProp.sharedMemPerBlock << endl;
	//}
	//system("PAUSE");
	//return 0;
	const int N = 5;
	float values[N] = { 1.5, 1.1, 1.1, 1.1, 1.1 };
	float keys[N] = { 0 };

	//thrust::sort_by_key(keys, keys + N, values);
	clock_t a, b;
	float * h_ = new float[50000000];
	float *dev_ = 0;
	float *dev_1 = 0;
	int count = 1000000;
	cudaMalloc((void**)&dev_, 50000000 * sizeof(float));
	cudaMemcpy(dev_, h_, 5000000 * sizeof(float), cudaMemcpyHostToDevice);
	// Allocate GPU buffers for three vectors (two input, one output)    .
	for (int i = 0; i < 10; i++)
	{
		std::cout<< std::endl << std::endl;
		{
			a = clock();
			for (int i = 0; i<10; i++)
			{
				cudaMemcpy(dev_, h_, 5000000 * sizeof(float), cudaMemcpyHostToDevice);
			}
			cudaError_t error = cudaDeviceSynchronize();
			error = cudaPeekAtLastError();
			b = clock();
			std::cout << "reconstruct time of 100 times 1:" << getTimeGeneral(b - a) << std::endl;
		}
		{
			a = clock();
			cudaMemcpy(dev_, h_, 50000000 * sizeof(float), cudaMemcpyHostToDevice);
			cudaError_t error = cudaDeviceSynchronize();
			error = cudaPeekAtLastError();
			b = clock();
			std::cout << "reconstruct time of 1 times 100:" << getTimeGeneral(b - a) << std::endl;
		}
	} 
		delete[]h_;
		cudaFree(dev_);
	//float *dev_keys = 0;
	//float *dev_values = 0;
	//float dev_c[5] = {1,2,3,4,5};
	//// Allocate GPU buffers for three vectors (two input, one output)    .
	//cudaMalloc((void**)&dev_keys, N * sizeof(float));
	//cudaMalloc((void**)&dev_values, N * sizeof(float));


	//cudaMemcpy(dev_keys, keys, N * sizeof(float), cudaMemcpyHostToDevice);
	//cudaMemcpy(dev_values, values, N * sizeof(float), cudaMemcpyHostToDevice);

	//Mytest << < 65535, 1024 >> >(dev_keys, dev_values);
	//cudaError_t error= cudaDeviceSynchronize();
	//error = cudaPeekAtLastError();
	//////cudaMemcpy(dev_c, dev_keys, N * sizeof(float), cudaMemcpyDeviceToHost);
    return 0;
}
#include <opencv2/opencv.hpp>
namespace GPU = cv::cuda;

__global__ void kernel(float *src,int rows,int cols,int channel)
{
	int idx = blockIdx.x*blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	int size = cols*rows;
	while (idx < size*channel)
	{
		//src(distorted_y,distorted_x) = 10*distorted_y+ distorted_x;
		src[idx] = 9.96;
		idx += stride;
	}
}

//int main() 
//{
//	// 首先要检查是否CUDA模块是否可用
//	//if (GPU::getCudaEnabledDeviceCount() == 0) {
//	//	cerr << "此OpenCV编译的时候没有启用CUDA模块" << endl;
//	//	return -1;
//	//}
//	int aaa[8] = { 0 };
//	int  *d_hashtable1;//每个点的哈希值
//	cudaMalloc((void**)&d_hashtable1, 8 * sizeof(int));
//	cudaMemset(d_hashtable1, 1, 8 * sizeof(int));
//	cudaMemcpy(aaa, d_hashtable1, 8 * sizeof(int), cudaMemcpyDeviceToHost);
//	cudaMemset(d_hashtable1, 255, 8 * sizeof(int));
//	float a1[8] = { 1,2,3,4,5,6,7,8 };
//	float *b = new float[8];
//	memcpy(b, a1, 32);
//	Mat temp20 = Mat(Size(4, 2), CV_32F, b);
//	delete[]b;
//	return 0;
//	Mat temp = Mat(2, 3, CV_32FC2);
//	const int rows = 16 * 50;
//	const int cols = 32 * 60;
//	const int type = CV_8UC3;
//	Mat one = Mat::ones(2, 2, CV_8UC2);
//	float a[8] = { 1,2,3,4,5,6,7,8 };
//	Mat temp2= Mat(Size(4,2), CV_32F,a);
//	Mat temp3 = Mat(2,4, CV_32F, a);
//	a[7] = 10000;
//	float *d_hashtable;//每个点的哈希值
//	cudaMalloc((void**)&d_hashtable, 8 * sizeof(float));
//	cudaMemcpy(d_hashtable, a, 8 * sizeof(float), cudaMemcpyHostToDevice);
//	GPU::GpuMat gpuMat1 = GPU::GpuMat(2, 4, CV_32FC1, d_hashtable);
//	gpuMat1.download(temp);
//	cudaMemset(d_hashtable, 1, 4 * 4);
//	gpuMat1.download(temp);
//	cuda::subtract(GPU::GpuMat(2, 4, CV_32FC1, d_hashtable), GPU::GpuMat(2, 4, CV_32FC1, d_hashtable), gpuMat1);
//	// 初始化一个黑色的GpuMat
//	/*GPU::GpuMat gpuMat(2,4, CV_32FC1, d_hashtable);*/
//	gpuMat1.download(temp);
//	cudaMemset(d_hashtable, 1, 4 * 4);
//	gpuMat1.download(temp);
//	cudaMemcpy(a, d_hashtable, 8 * sizeof(float), cudaMemcpyDeviceToHost);
//	Mat temp1 = Mat(2, 4, CV_32S);
//	memcpy(temp1.data,a,8*4);
//	temp1.convertTo(temp1, CV_32F);
//	GPU::GpuMat gpuMat;/*= GPU::GpuMat(2, 4, CV_32FC1, Scalar(0))*/;
//	gpuMat.upload(temp1);
//	//{
//	//	gpuMat = GPU::GpuMat(100, 1000, CV_32FC1, Scalar(0));
//	//}
//	//gpuMat(0, 0) = 100;
//	//cudaFree(d_hashtable);
//	//vector<Mat> abc;
//	Mat two;
//	//GPU::GpuMat gpuMat1;
//	//
//	////Mat temp/* = Mat(ROWS, COLS, CV_32FC2)*/;
//	////merge(&gpuMat[0], 2, temp);
//	//gpuMat.convertTo(gpuMat1, CV_8UC2);
//	//gpuMat.download(two);
//	//gpuMat1.download(two);
//	//kernel << <100, 100 >> >((float*)gpuMat.data,2,2,2);
//	
//	gpuMat.download(two);
//	return 0;
//}


// Helper function for using CUDA to add vectors in parallel.
cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size)
{
    int *dev_a = 0;
    int *dev_b = 0;
    int *dev_c = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    addKernel<<<1, size>>>(dev_c, dev_a, dev_b);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
    
    return cudaStatus;
}
