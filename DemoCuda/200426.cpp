#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include < functional>  
#include "glm\glm.hpp"
using namespace std;
using namespace cv;


void main0426()
{
	double aaa = norm(Mat(Point2f(2, 2)), Mat(Point2f(0, 0)), NORM_L2);
	cout << aaa << endl;
	aaa = norm(Mat(Point2f(2, 2)), Mat(Point2f(0, 0)), NORM_L1);
	cout << aaa << endl;

	Mat m_CameraOne_Cam_Matrix;
	Mat m_CameraOne_Cam_Distortion;
	Mat m_Ori,m_Undistort;
	string XMLFile = "C:\\Users\\bz\\Desktop\\old\\DLP-3D\\Bin\\SystemParamsPre.xml";
	FileStorage fps(XMLFile, FileStorage::READ);
	fps["CameraOne_Cam_Matrix"] >> m_CameraOne_Cam_Matrix;
	fps["CameraOne_Cam_Distortion"] >> m_CameraOne_Cam_Distortion;
	fps.release();
	m_Ori = imread("D:\\Stereo3D\\data\\test1209\\0418-2pic\\1_1\\0000.bmp", IMREAD_GRAYSCALE);
	undistort(m_Ori, m_Undistort, m_CameraOne_Cam_Matrix, m_CameraOne_Cam_Distortion);
	imwrite("D:\\Stereo3D\\data\\test1209\\0418-2pic\\1_1\\0000Undistort.bmp", m_Undistort);
	Mat hell = m_Undistort - m_Ori;
	imwrite("D:\\Stereo3D\\data\\test1209\\0418-2pic\\1_1\\difference.bmp", hell);
	return;

}
//undistort(InputArray src, OutputArray dst,
//	InputArray cameraMatrix,
//	InputArray distCoeffs,
//	InputArray newCameraMatrix = noArray());