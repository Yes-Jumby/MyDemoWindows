#include "device_launch_parameters.h"
#include "cuda_runtime.h"
#include "cuda.h"
#include <iostream>
#include "texture_fetch_functions.h"
#define max(a,b) (a>b?a:b)
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
texture<float> t_input;
__global__ void MaxPool2d(const int height, const int pooled_height, float* top_data)
{
	int x = blockIdx.x;
	int y = blockIdx.y;
	int dx = gridDim.x;
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int dtx = blockDim.x;
	int dty = blockDim.y;
	float s = -10000.0;
	float a1, a2, a3, a4, a12, a34;
	int index2 = y*dx*dtx*dty + x*dtx*dty + ty*dtx + tx;
	int index = y*dx*height*height + x*height*height + ty*pooled_height*height + tx*pooled_height;
	int index3 = 0;
	bool b1 = 1 + 2 * ty == height;
	bool b2 = 1 + 2 * tx == height;

	if (b1&&b2)
	{
		a1 = tex1Dfetch(t_input, index);
		s = max(a1, s);
	}
	if (!b2)
	{
		a1 = tex1Dfetch(t_input, index);
		a2 = tex1Dfetch(t_input, index + 1);
		a12 = max(a1, a2);
		s = max(a12, s);
		index3 = height + 1;
	}
	if (!b1)
	{
		a3 = tex1Dfetch(t_input, index + index3);
		a4 = tex1Dfetch(t_input, index + height);
		a34 = max(a3, a4);
		s = max(a34, s);
	}
	*(top_data + index2) = s;
}
__global__ void GetThres(
	unsigned char				*IMG,
	unsigned int		cloud_size,
	float*				bounding
)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	uint stride = blockDim.x * gridDim.x;
	extern __shared__ float s_float[];

	float* max_cachex = s_float;
	int cacheIndex = threadIdx.x;
	float temp_maxx = -FLT_MAX;
	while (idx < cloud_size)
	{
		float x = (float)IMG[idx];
		if (temp_maxx < x)
		{
			temp_maxx = x;
		}
		idx += stride;

	}
	max_cachex[cacheIndex] = temp_maxx;
	__syncthreads();
	int i = blockDim.x / 2;
	while (i != 0)
	{
		if (cacheIndex < i)
		{
			if (max_cachex[cacheIndex] < max_cachex[cacheIndex + i])
			{
				max_cachex[cacheIndex] = max_cachex[cacheIndex + i];
			}
		}
		__syncthreads();
		i /= 2;
	}
	if (cacheIndex == 0)
	{
		bounding[0] = max_cachex[0]+1.0f;
	}
};


int main17()
{
	cv::Mat ima;
	ima = imread("D:\\Stereo3D\\data\\test1209\\BINOCULAR\\phase\\right\\0001.bmp", IMREAD_GRAYSCALE);
	int x_times_y_ = ima.rows*ima.cols;
	float phase_thre_;
	float *d_bounding;
	(cudaMalloc((void**)&d_bounding,1 * sizeof(float)));
	unsigned char *image_black_uchar_d_;
	cudaMalloc((void**)&image_black_uchar_d_, sizeof(unsigned char)*x_times_y_*(1));
	cudaMemcpy(image_black_uchar_d_, ima.data, sizeof(unsigned char)*x_times_y_, cudaMemcpyHostToDevice);
	GetThres << <1, 1024, sizeof(float) * 1024 >> > (image_black_uchar_d_, x_times_y_, d_bounding);
	cudaDeviceSynchronize();
	cudaPeekAtLastError();//3
	cudaMemcpy(&phase_thre_, d_bounding, 1 * sizeof(float), cudaMemcpyDeviceToHost);
	cout << "phase_thre_:" << phase_thre_ << endl;
	int deviceCount;
	cudaGetDeviceCount(&deviceCount);
	int device;
	cudaDeviceProp deviceProp;
	for (device = 0; device < deviceCount; ++device)
	{
		cudaGetDeviceProperties(&deviceProp, device);
		printf("Device %d has compute capability %d.%d.\n",
			device, deviceProp.major, deviceProp.minor);
		cout << "regsPerBlock:" << deviceProp.regsPerBlock << endl;
		cout << "maxThreadsPerBlock:" << deviceProp.maxThreadsPerBlock << endl;
		cout << "sharedMemPerBlock:" << deviceProp.sharedMemPerBlock << endl;
	}
	system("PAUSE");
	return 0;
	//cudaGetDevice();
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	const int N = 5, M = 5, H = 25, W = 25, D = 2;
	const int PH = H / D + H % D;
	const int image_size = N*M*H*W * sizeof(float);
	const int out_size = N*M*PH*PH * sizeof(float);
	float mul_by = 0.01;
	float *input, *output, *dev_input, *dev_output;


	input = new float[image_size];
	output = new float[out_size];
	for (int i = 0; i<N*M*H*W; i++)
		*(input + i) = i*mul_by;

	cudaMalloc((void**)&dev_output, out_size);
	cudaMalloc((void**)&dev_input, image_size);
	cudaBindTexture(NULL, t_input, dev_input,
		image_size);
	cudaMemcpy(dev_input, input, image_size,
		cudaMemcpyHostToDevice);

	dim3    grid(M, N);
	dim3    threads(PH, PH);
	cudaEventRecord(start, 0);
	MaxPool2d << <grid, threads >> >(H, D, dev_output);
	cudaMemcpy(output, dev_output, out_size, cudaMemcpyDeviceToHost);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime,
		start, stop);
	std::cout << "Time to generate: " << elapsedTime << "ms\n";
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	for (int i = 0; i<10; i++)
		std::cout << *(output + i) << std::endl;

	cudaFree(dev_input);
	cudaFree(dev_output);
	cudaUnbindTexture(t_input);
	delete[] output;
	delete[] input;
	system("pause");
}

/*
Time to generate: 0.128448ms
*/