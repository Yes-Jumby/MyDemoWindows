#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <fstream>
//find line
using namespace cv;
using namespace std;
int mainfantui(int argc, char** argv) {

    vector<Point3f> pts_3d_world;
    vector<Point2f> pts_2d_pixel;
    vector<Point2f> pts_2d_world;
    //3D
    for (int i = 0; i < 12; i++)
    {
        if (i % 2 == 0)
        {
            pts_3d_world.push_back(cv::Point3f(i * 30, 0, 0));
            pts_2d_world.push_back(cv::Point2f(i * 30,  0));
        }
        else
        {
            pts_3d_world.push_back(cv::Point3f(i * 30, 0, 30));
            pts_2d_world.push_back(cv::Point2f(i * 30, 30));
        }
    }
    //3D
    std::string fileName1 = "D:\\Stereo3D\\data\\DemoIMG\\interSec3D.txt";
    std::ofstream fileOutput(fileName1.c_str());   // ���ļ�������������
    cv::Point3f p3D;
    for (int i = 0; i < 12; i++)
    {
        p3D = pts_3d_world.at(i);
        fileOutput << p3D.x << "   " << p3D.y << "   " << p3D.z << std::endl;
    }
    fileOutput.close(); //�ر�������

    //2D
    std::string fileName = "D:\\Stereo3D\\data\\DemoIMG\\interSec.txt";
    std::ifstream fileInput(fileName.c_str());   // ���ļ�������������
    std::string lineStr;
    std::stringstream sstr;
    float x;
    float y;
    int i = 1;
    while (std::getline(fileInput, lineStr))    // ��ȡһ��
    {
        sstr << lineStr;                          // ����ȡ������ѹ�뵽 sstr
        sstr >> x >> y;        //  ʹ��sringsream �������
        std::cout << "line " << i << " " << x << " " << y << std::endl;
        i++;
        sstr.clear();          // this is important. ע�⽫stringsream������գ�����һֱΪ��һ��
        pts_2d_pixel.push_back(cv::Point2f(x, y));
    }
    fileInput.close(); //�ر�������

    

    Mat r, rvecsMat, tvecsMat;
    Mat cameraMatrix, distCoeffs;
    vector<vector<Point2f>> image_points_seq;
    vector<vector<Point3f>> object_points_seq;
    image_points_seq.push_back(pts_2d_pixel);
    object_points_seq.push_back(pts_3d_world);
    //double err_first = calibrateCamera(object_points_seq, image_points_seq, cv::Size(2560, 832), cameraMatrix, distCoeffs, rvecsMat, tvecsMat, CV_CALIB_FIX_K1|CV_CALIB_RATIONAL_MODEL| CV_CALIB_ZERO_TANGENT_DIST);
    //solvePnP(pts_3d_world, pts_2d_pixel, cameraMatrix, distCoeffs, r, tvecsMat, false, cv::SOLVEPNP_UPNP);
    //cameraMatrix = initCameraMatrix2D(object_points_seq, image_points_seq, cv::Size(2560, 832));
    Mat H = findHomography(pts_2d_world, pts_2d_pixel, 0);
    cout << H << endl << endl;;
    vector<Point2f> pts_2d_dest;
    //cv::Mat m_unPersctiveMat = cv::getPerspectiveTransform(pts_2d_world, pts_2d_pixel); 
    perspectiveTransform(pts_2d_world, pts_2d_dest, H);

    double  err = norm(Mat(pts_2d_dest), Mat(pts_2d_pixel), NORM_L2);
    cout << H << endl << endl;;
    cout <<"SSE:"<< err*err << endl << endl;;
    cout << "RSSE:" << err*err/12 << endl << endl;;
    return 0;
}