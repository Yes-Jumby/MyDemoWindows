#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stack>
#include "cv.hpp"
using namespace cv;
using namespace std;
//定义结点状态
enum  PixelType
{
	CODE_UNDEFINED=0,//默认值
	CODE_TARGET,//目标值
};

void getRound4(int idxtem[], int idx, int nImgW, int imgH)
{
	idxtem[0] = idx - 1;
	idxtem[1] = idx + 1;
	idxtem[2] = idx - nImgW;
	idxtem[3] = idx + nImgW;
}
int colorReplace(uchar *pImg, int nImgW, int imgH, int
	nStartX, int nStartY, uchar cRepColor)
{
	stack<int>travel, piont;//存储遍历点
	int *pPixelType = (int *)malloc(sizeof(int)*nImgW*imgH);//存储点的状态
	memset(pPixelType, 0, sizeof(int)*nImgW*imgH);

	//初始位置
	int currentX, currentY;
	currentX = nStartX - 1;
	currentY = nStartY - 1;
	int idx;
	int idxtem[4];
	uchar tarValue;
	idx = currentX + currentY*nImgW;
	if (idx<0 || idx>nImgW*imgH)
	{
		return -1;
	}
	tarValue = pImg[idx];
	piont.push(idx);
	pPixelType[idx] = (int)CODE_TARGET;
	getRound4(idxtem, idx, nImgW, imgH);
	for (int i = 0; i < 4; i++)
	{
		if (idxtem[i]>=0 && idxtem[i]<nImgW*imgH)
		{
			travel.push(idxtem[i]);;
		}
	}
	//遍历所有邻域
	while (!travel.empty())
	{
		idx = travel.top();
		travel.pop();
		if (pImg[idx] == tarValue)
		{
			getRound4(idxtem, idx, nImgW, imgH);
			for (int i = 0; i < 4; i++)
			{
				if (idxtem[i] >= 0 && idxtem[i] < nImgW*imgH)
				{
					//防止重复引用
					if (pPixelType[idxtem[i]] == 0)
					{
						travel.push(idxtem[i]);
					}
				}
			}
			//防止重复引用
			if (pPixelType[idx] == 0)
			{
				pPixelType[idx] = (int)CODE_TARGET;
				piont.push(idx);
			}
		}
	}
	free(pPixelType);
	while (!piont.empty())
	{
		pImg[piont.top()] = cRepColor;
		piont.pop();
	}
	return 0;
}
void main2004211()
{
	int size_ = 10;
	cv::Mat Rol = cv::Mat::ones(size_, size_, CV_8S);
	for (int i = 0; i < Rol.cols; i++)
	{
		for(int j = 0; j < Rol.rows; j++)
		{ 
			if (i == 0 || j == 0 || i == Rol.cols - 1 || j == Rol.rows - 1)
			{
				Rol.at<uchar>(i, j) = 0;
			}
		}
	}
	Rol.at<uchar>(5, 6) = 100;
	Rol.at<uchar>(6, 6) = 100;
	Rol.at<uchar>(7, 6) = 100;

	Rol.at<uchar>(6, 5) = 100;
	Rol.at<uchar>(6, 6) = 100;
	Rol.at<uchar>(6, 7) = 100;

	colorReplace(Rol.data, size_, size_, 7, 6, 122);
	return;
}