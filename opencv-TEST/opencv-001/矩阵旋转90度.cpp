#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stack>
#include <vector>
#include "cv.hpp"
using namespace cv;
using namespace std;
void changePos(int &a, int &b, int &c, int &d)
{
    int temp1,temp2;
    temp1 = b;
    b = a;
    temp2 = c;
    c = temp1;
    temp1 = d;
    d = temp2;
    a = temp1;
}
void main90()
{
    int size_ = 10;
    int nImgW = size_;
    int imgH = size_;
    cv::Mat Rol = cv::Mat::zeros(imgH, nImgW, CV_32S);

    for (int i = 0; i < nImgW; i++)
    {
        for (int j = 0; j < imgH; j++)
        {
            Rol.at<__int32>(i, j) = i*nImgW + j + 1;
        }
    }
    
    int iEnd = nImgW-1;
    int iStart = 0;
    int a, b, c, d;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    changePos(a, b, c, d);
    cout << a << endl;cout << b << endl; cout << c<< endl; cout << d << endl;
    int index = 0;
    while (true)
    {
        for (int i = iStart; i < iEnd; i++)
        {
            a = Rol.at<__int32>(iStart, i);
            b = Rol.at<__int32>(i, iEnd);
            c = Rol.at<__int32>(iEnd, iEnd - i + index);
            d = Rol.at<__int32>(iEnd - i + index, iStart);
            changePos(a, b, c, d);
            Rol.at<__int32>(iStart, i) = a;
            Rol.at<__int32>(i, iEnd) = b;
            Rol.at<__int32>(iEnd, iEnd - i + index) = c;
            Rol.at<__int32>(iEnd - i + index, iStart) = d;
        }

        iStart = iStart + 1;
        iEnd = iEnd - 1;
        index = index + 1;
        if (iStart > iEnd)
        {
            break;
        }
    }
    
    return;
}