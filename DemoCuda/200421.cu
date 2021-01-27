#include <iostream>
#include "time.h"
#include "cv.hpp"
#include "cudaarithm.hpp"
#include "cudafilters.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuda_profiler_api.h"
using namespace cv;
using namespace std;

__global__ void Continuation(cuda::PtrStepSz<float1> input, cuda::PtrStepSz<float1> output,int size,uint cols,uint rows)
{
	uint idx = blockIdx.x*blockDim.x + threadIdx.x;
	uint stride = blockDim.x * gridDim.x;
	while (idx < size)
	{
		int distorted_x = idx%cols;//width
		int distorted_y = idx / cols;//height
		output(distorted_y, distorted_x) = input(distorted_y, distorted_x);
		output(distorted_y, 2 * cols - 1 - distorted_x) = input(distorted_y, distorted_x);
		output(2 * rows - 1 - distorted_y, distorted_x) = input(distorted_y, distorted_x);
		output(2 * rows - 1 - distorted_y, 2 * cols - 1 - distorted_x) = input(distorted_y, distorted_x);
		idx += stride;
	}
}
int main()
{
	clock_t a; 
	int size_ = 1000;
	int testtimes = 10;
	for (int aaa = 1; aaa < 11; aaa++)
	{
		size_ = aaa * 500;
		cout << "Mat Size" << size_ << endl;
		cv::Mat Rol = cv::Mat::ones(size_, size_, CV_32F);
		Rol.at<float>(0, 0) = 1;
		Rol.at<float>(0, 1) = 2;
		Rol.at<float>(1, 0) = 3;
		Rol.at<float>(1, 1) = 4;
		cv::Mat HresultImage;
		cv::Mat C;
		cv::Mat VresultImage;
		a = clock();
		for (int mytimes = 0; mytimes < testtimes; mytimes++)
		{
			cv::flip(Rol, HresultImage, 1);
			cv::hconcat(Rol, HresultImage, HresultImage);
			cv::flip(HresultImage, VresultImage, 0);
			cv::vconcat(HresultImage, VresultImage, C);
		}
		cout << "Opencv cpu库函数" << clock() - a << endl;
		a = clock();
		cv::Mat RolP = cv::Mat(cv::Size(2 * Rol.cols, 2 * Rol.rows), Rol.type(), cv::Scalar(0));
		for (int mytimes = 0; mytimes < testtimes; mytimes++)
		{
			for (int i = 0; i < Rol.cols; ++i)
			{
				for (int j = 0; j < Rol.rows; ++j)
				{
					RolP.at<float>(j, i) = Rol.at<float>(j, i);
					RolP.at<float>(j, 2 * Rol.cols - 1 - i) = Rol.at<float>(j, i);
					RolP.at<float>(2 * Rol.rows - 1 - j, i) = Rol.at<float>(j, i);
					RolP.at<float>(2 * Rol.rows - 1 - j, 2 * Rol.cols - 1 - i) = Rol.at<float>(j, i);
				}
			}
		}
		cout << "自写CPU函数" << clock() - a << endl;

		a = clock();
		cuda::GpuMat GRol;
		GRol.upload(Rol);
		cuda::GpuMat GRolP(cv::Size(2 * Rol.cols, 2 * Rol.rows), Rol.type(), Scalar(0, 0, 0));
		int size = Rol.cols*Rol.rows;
		for (int mytimes = 0; mytimes < testtimes; mytimes++)
		{
			Continuation << <(size + 1023) / 1024, 1024 >> > (GRol, GRolP, size, Rol.cols, Rol.rows);
			cudaDeviceSynchronize();
		}
		cout << "自写GPU函数" << clock() - a << endl;
		cout << endl << endl;
		Mat temp;
		GRolP.download(temp);
	}
	
	
	
	return 0;
}