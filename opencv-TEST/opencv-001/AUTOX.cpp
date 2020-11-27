//#include <iostream>
//#include <algorithm>
//using namespace std;
//struct rect_
//{
//    float x_min_;
//    float x_max_;
//    float y_min_;
//    float y_max_;
//};
//int main() {
//    rect_ rect1;
//    rect_ rect2;
//    float a, b;
//    cin >> a >> b;
//    rect1.x_max_ = a;
//    rect1.x_min_ = a;
//    rect1.y_max_ = b;
//    rect1.y_min_ = b;
//    cin >> a >> b;
//    rect1.x_max_=max(a, rect1.x_max_);
//    rect1.x_min_ = min(a, rect1.x_min_);
//    rect1.y_max_ = max(b, rect1.y_max_);
//    rect1.y_min_ = min(b, rect1.y_min_);
//    cin >> a >> b;
//    rect1.x_max_ = max(a, rect1.x_max_);
//    rect1.x_min_ = min(a, rect1.x_min_);
//    rect1.y_max_ = max(b, rect1.y_max_);
//    rect1.y_min_ = min(b, rect1.y_min_);
//    cin >> a >> b;
//    rect1.x_max_ = max(a, rect1.x_max_);
//    rect1.x_min_ = min(a, rect1.x_min_);
//    rect1.y_max_ = max(b, rect1.y_max_);
//    rect1.y_min_ = min(b, rect1.y_min_);
//
//    cin >> a >> b;
//    rect2.x_max_ = a;
//    rect2.x_min_ = a;
//    rect2.y_max_ = b;
//    rect2.y_min_ = b;
//    cin >> a >> b;
//    rect2.x_max_ = max(a, rect2.x_max_);
//    rect2.x_min_ = min(a, rect2.x_min_);
//    rect2.y_max_ = max(b, rect2.y_max_);
//    rect2.y_min_ = min(b, rect2.y_min_);
//    cin >> a >> b;
//    rect2.x_max_ = max(a, rect2.x_max_);
//    rect2.x_min_ = min(a, rect2.x_min_);
//    rect2.y_max_ = max(b, rect2.y_max_);
//    rect2.y_min_ = min(b, rect2.y_min_);
//    cin >> a >> b;
//    rect2.x_max_ = max(a, rect2.x_max_);
//    rect2.x_min_ = min(a, rect2.x_min_);
//    rect2.y_max_ = max(b, rect2.y_max_);
//    rect2.y_min_ = min(b, rect2.y_min_);
//
//    bool flag = ((min(rect1.x_max_, rect2.x_max_) > max(rect1.x_min_, rect2.x_min_))
//        &&
//        (min(rect1.y_max_, rect2.y_max_) > max(rect1.y_min_, rect2.y_min_)));
//    if (flag)
//    {
//        cout << "YES";
//    }
//    else
//    {
//        cout << "NO";
//    }
//    return 0;
//}

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stack>
#include <vector>
#include "cv.hpp"
using namespace cv;
using namespace std;
//定义结点状态--关键就是记录下 未知点访问与否的状态  回溯法的精髓
//enum  PixelType
//{
//    CODE_UNDEFINED = 0,//默认值
//    CODE_TARGET,//目标值
//};

void getRound4_(int idxtem[], int idx, int nImgW, int imgH)
{
    idxtem[0] = idx - 1;
    idxtem[1] = idx + 1;
    idxtem[2] = idx - nImgW;
    idxtem[3] = idx + nImgW;
}
bool colorReplace_(uchar *pImg, int *pPixelType, int nImgW, int imgH, int
    nStartX, int nStartY, int CODE_TARGET, vector<int> &_per_size)
{
    stack<int>travel, piont;//存储遍历点
                            //初始位置
    int currentX, currentY;
    currentX = nStartX;
    currentY = nStartY;
    int idx;
    int idxtem[4];
    uchar tarValue = 1;
    idx = currentX + currentY*nImgW;
    if (idx<0 || idx>nImgW*imgH)
    {
        return -1;
    }
    if (pImg[idx] == 0 || pPixelType[idx] != 0)
    {
        return false;
    }
    //tarValue = pImg[idx];
    piont.push(idx);
    pPixelType[idx] = (int)CODE_TARGET;//记录 以防止重复记录
    getRound4_(idxtem, idx, nImgW, imgH);
    for (int i = 0; i < 4; i++)
    {
        if (idxtem[i] >= 0 && idxtem[i]<nImgW*imgH)
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
            getRound4_(idxtem, idx, nImgW, imgH);
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
    _per_size.push_back(piont.size());
    //free(pPixelType);
    while (!piont.empty())
    {
        pImg[piont.top()] = CODE_TARGET;
        piont.pop();
    }
    return true;;
}
void mainHHHHH()
{
    vector<int> _per_size;
    int size_ = 10;
    int nImgW = 12;
    int imgH = 10;
    cv::Mat Rol = cv::Mat::zeros(imgH, nImgW, CV_8S);

    int *pPixelType = (int *)malloc(sizeof(int)*nImgW*imgH);//存储点的状态
    memset(pPixelType, 0, sizeof(int)*nImgW*imgH);
    //for (int i = 0; i < Rol.cols; i++)
    //{
    //    for (int j = 0; j < Rol.rows; j++)
    //    {
    //        if (i == 0 || j == 0 || i == Rol.cols - 1 || j == Rol.rows - 1)
    //        {
    //            Rol.at<uchar>(i, j) = 0;
    //        }
    //    }
    //}
    Rol.at<uchar>(0, 0) = 1;

    Rol.at<uchar>(5, 6) = 1;
    Rol.at<uchar>(6, 6) = 1;
    Rol.at<uchar>(7, 6) = 1;
    Rol.at<uchar>(6, 5) = 1;
    Rol.at<uchar>(6, 6) = 1;
    Rol.at<uchar>(6, 7) = 1;

    cv::Mat mymat;
    mymat = Rol;
    int sizeTarget = 1;
    for (int i = 0; i < nImgW; i++)
    {
        for (int j = 0; j < imgH; j++)
        {
            if (colorReplace_(Rol.data, pPixelType, nImgW, imgH, i, j, sizeTarget, _per_size))
            {
                sizeTarget++;
            }
        }
    }
    cout << sizeTarget--;
    free(pPixelType);
    return;
}