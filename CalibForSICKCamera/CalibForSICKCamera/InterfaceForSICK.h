#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <io.h>  
using namespace std;
//using namespace cv;
/*
@主要生成3通道mat
*/
cv::Mat convertTo3Channels(const cv::Mat& binImg);
/*
@在3通道mat上画矩形
*/
void DrawRectIn3Channels(const cv::Mat& binImg, vector<cv::Point2f> pts_minAreaRect_2_);
/*
@寻找两直线交点
*/
cv::Point2f FindLineInsect(const cv::Vec4f &line1_para, const cv::Vec4f &line2_para);
/*
@在3通道mat上画直线
*/
void DrawLineIn3Channels(const cv::Mat& binImg, const std::vector<cv::Point> &points, const cv::Scalar &color,cv::Vec4f &line_para,bool isdraw = false);
/*
@找边上的角点
*/
void FindEdgePoints(const cv::Mat& binImg, const int & index_, const cv::Rect &rect, vector<vector<cv::Point2i>> &point_,float ratio = 0.25);
/*
@找四角的角点
*/
void FindFourPoints(const cv::Mat& disImg, const int & index_, const cv::Mat& binImg, const cv::Rect &rect, vector<cv::Point2f> &point_insect, float ratio = 0.25,bool isdraw = false);
/*
@2D高度图到3D真实点的映射
*/
void TransHeight2DTo3D(const cv::Mat& Img32f, const vector<cv::Point2f> &Height2Dpoint_, float x_resolution,float x_min, int iteration_count, vector<cv::Point3f> &Height3Dpoint_);
/*
@在3D图上找角点
*/
void findCorners3D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_3d_2d_);
/*
@在2D图上找角点
*/
void findCorners2D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_2d_, bool IsShow);
/*
@param File_Directory 为文件夹目录
@param FileType 为需要查找的文件类型
@param FilesName 为存放文件名的容器
*/
void getFilesName1(string &File_Directory, string &FileType, vector<string>&FilesName);
