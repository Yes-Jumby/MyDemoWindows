#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <io.h>  
using namespace std;
//using namespace cv;
cv::Mat convertTo3Channels(const cv::Mat& binImg);
void DrawRectIn3Channels(const cv::Mat& binImg, vector<cv::Point2f> pts_minAreaRect_2_);
cv::Point2f FindLineInsect(const cv::Vec4f &line1_para, const cv::Vec4f &line2_para);
void DrawLineIn3Channels(const cv::Mat& binImg, const std::vector<cv::Point> &points, const cv::Scalar &color,cv::Vec4f &line_para,bool isdraw = false);
void FindEdgePoints(const cv::Mat& binImg, const int & index_, const cv::Rect &rect, vector<vector<cv::Point2i>> &point_,float ratio = 0.25);
void FindFourPoints(const cv::Mat& disImg, const int & index_, const cv::Mat& binImg, const cv::Rect &rect, vector<cv::Point2f> &point_insect, float ratio = 0.25,bool isdraw = false);
void TransHeight2DTo3D(const cv::Mat& Img32f, const vector<cv::Point2f> &Height2Dpoint_, float x_resolution,float x_min, int iteration_count, vector<cv::Point3f> &Height3Dpoint_);
void findCorners3D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_3d_2d_);
void findCorners2D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_2d_, bool IsShow);
/*
@param File_Directory 为文件夹目录
@param FileType 为需要查找的文件类型
@param FilesName 为存放文件名的容器
*/
void getFilesName1(string &File_Directory, string &FileType, vector<string>&FilesName);
