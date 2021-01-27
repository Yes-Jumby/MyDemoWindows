#include <iostream>
#include "time.h"
#include "cv.hpp"
#include "cudaarithm.hpp"
#include "cudafilters.hpp"
using namespace cv;
using namespace std;
string getLCS(string str1, string str2) {
	//vector<vector<int> > record(str1.length(), vector<int>(str2.length()));
	int **record = (int **)malloc(sizeof(int *) * str1.length());
	for (int i = 0; i < str1.length(); ++i)
	{
		record[i] = (int *)malloc(sizeof(int) * str2.length());
	}

	int maxLen = 0, maxEnd = 0;
	for (int i = 0; i < static_cast<int>(str1.length()); ++i)
		for (int j = 0; j < static_cast<int>(str2.length()); ++j) 
		{
			if (str1[i] == str2[j]) 
			{
				if (i == 0 || j == 0) 
				{
					record[i][j] = 1;
				}
				else 
				{
					record[i][j] = record[i - 1][j - 1] + 1;
				}
			}
			else 
			{
				record[i][j] = 0;
			}


			if (record[i][j] > maxLen) 
			{
				maxLen = record[i][j];
				maxEnd = i; //若记录i(j),则最后获取LCS时是取str1(str2)的子串
			}
		}
	for (int i = 0; i < 5; ++i)
		free(record[i]);
	free(record);
	return str1.substr(maxEnd  - maxLen+1, maxLen);
}

int main0421()
{
	cout << getLCS("12365","365")<< endl;
	clock_t a;
	int size_ = 5000;
	int testtimes = 10;
	cv::Mat Rol = cv::Mat::ones(size_, size_, CV_32F);
	//Rol.at<float>(0, 0) = 1;
	//Rol.at<float>(0, 1) = 2;
	//Rol.at<float>(1, 0) = 3;
	//Rol.at<float>(1, 1) = 4;
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
	cout << clock() - a << endl;
	cv::Mat RolP = cv::Mat(cv::Size(2 * Rol.cols, 2 * Rol.rows), Rol.type(), cv::Scalar(0));

	a = clock();
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
	cout << clock() - a << endl;

	//cuda::GpuMat GRol;
	//cuda::GpuMat GHresultImage;
	//cuda::GpuMat GC;
	//cuda::GpuMat GVresultImage;
	//GRol.upload(Rol);
	//for (int mytimes = 0; mytimes < testtimes; mytimes++)
	//{
	//	cuda::flip(Rol, GHresultImage, 1);
	//	cuda::hconcat(Rol, GHresultImage, GHresultImage);
	//	cuda::flip(GHresultImage, GVresultImage, 0);
	//	cuda::vconcat(GHresultImage, GVresultImage, GC);
	//}

	return 0;
}