#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <io.h>  
using namespace std;
//using namespace cv;
/*
@��Ҫ����3ͨ��mat
*/
cv::Mat convertTo3Channels(const cv::Mat& binImg);
/*
@��3ͨ��mat�ϻ�����
*/
void DrawRectIn3Channels(const cv::Mat& binImg, vector<cv::Point2f> pts_minAreaRect_2_);
/*
@Ѱ����ֱ�߽���
*/
cv::Point2f FindLineInsect(const cv::Vec4f &line1_para, const cv::Vec4f &line2_para);
/*
@��3ͨ��mat�ϻ�ֱ��
*/
void DrawLineIn3Channels(const cv::Mat& binImg, const std::vector<cv::Point> &points, const cv::Scalar &color,cv::Vec4f &line_para,bool isdraw = false);
/*
@�ұ��ϵĽǵ�
*/
void FindEdgePoints(const cv::Mat& binImg, const int & index_, const cv::Rect &rect, vector<vector<cv::Point2i>> &point_,float ratio = 0.25);
/*
@���ĽǵĽǵ�
*/
void FindFourPoints(const cv::Mat& disImg, const int & index_, const cv::Mat& binImg, const cv::Rect &rect, vector<cv::Point2f> &point_insect, float ratio = 0.25,bool isdraw = false);
/*
@2D�߶�ͼ��3D��ʵ���ӳ��
*/
void TransHeight2DTo3D(const cv::Mat& Img32f, const vector<cv::Point2f> &Height2Dpoint_, float x_resolution,float x_min, int iteration_count, vector<cv::Point3f> &Height3Dpoint_);
/*
@��3Dͼ���ҽǵ�
*/
void findCorners3D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_3d_2d_);
/*
@��2Dͼ���ҽǵ�
*/
void findCorners2D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_2d_, bool IsShow);
/*
@param File_Directory Ϊ�ļ���Ŀ¼
@param FileType Ϊ��Ҫ���ҵ��ļ�����
@param FilesName Ϊ����ļ���������
*/
void getFilesName1(string &File_Directory, string &FileType, vector<string>&FilesName);
