#include "opencv.hpp"

#include <iostream>
#include <fstream> 
#include <io.h>  
#include <string>  
#include<vector>
#include <Ranger3.h>
using namespace cv;
using namespace std;
void main¶ÁÈ¡±£´æÍ¼Æ¬()
{
    //3D
    // ------ Convert
    SickCam::ImgT iconRange;
    iconRange.loadFromIconFile("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\3D\\calibed_3D", 1.0);
    cv::Mat rangeCALIm(iconRange.get_rows(), iconRange.get_cols(), CV_32FC1, iconRange.getData(SickCam::DataNames::RAN_CAL));
    //cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm.png", rangeCALIm);
    cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm.bmp", rangeCALIm);
    cv::Mat rangeCALIm_FLIP;
    //cv::Mat rangeCALIm_FLIP_save, rangeCALIm_FLIP_read;
    cv::flip(rangeCALIm, rangeCALIm_FLIP, 0);//ÑØ×ÅXÖáÐý×ª¼´´¹Ö±Ðý×ª
                                             //cv::normalize(rangeCALIm_FLIP, rangeCALIm_FLIP_save, 0, 1.0, cv::NORM_MINMAX);
                                             //rangeCALIm_FLIP_read = imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP.png", IMREAD_UNCHANGED);
                                             //cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP.png", rangeCALIm_FLIP_save);
    cv::Mat rangeCALIm_FLIP_depth_(rangeCALIm_FLIP.rows, rangeCALIm_FLIP.cols, CV_8UC4, rangeCALIm_FLIP.data);
    cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP_depth_.bmp", rangeCALIm_FLIP_depth_);
    cv::Mat rangeCALIm_FLIP_depth_read_, rangeCALIm_FLIP_depth_read_1_;
    rangeCALIm_FLIP_depth_read_ = imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP_depth_.bmp", IMREAD_UNCHANGED);
    rangeCALIm_FLIP_depth_read_.convertTo(rangeCALIm_FLIP_depth_read_1_, CV_32FC1);
    cv::Mat rangeCAL(rangeCALIm_FLIP_depth_read_.rows, rangeCALIm_FLIP_depth_read_.cols, CV_32FC1, rangeCALIm_FLIP_depth_read_.data);
    double mind, maxd;
    cv::minMaxLoc(rangeCALIm_FLIP, &mind, &maxd);
    cout << "MIN:" << mind << endl;
    cout << "MAX:" << maxd << endl;


    cv::Mat rangeCALIm_FLIP_8, rangeCALIm_FLIP_8_bin;
    rangeCALIm_FLIP.convertTo(rangeCALIm_FLIP_8, CV_8UC1, 255.0 / maxd);
    cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP_8.bmp", rangeCALIm_FLIP_8);

    cv::minMaxLoc(rangeCALIm_FLIP_8, &mind, &maxd);
    cout << "MIN:" << mind << endl;
    cout << "MAX:" << maxd << endl;
    cv::threshold(rangeCALIm_FLIP_8, rangeCALIm_FLIP_8_bin, 151, 255, THRESH_BINARY);

    SickCam::ImgT iconSensor;
    iconSensor.loadFromIconFile("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\2D\\1", 1.0);
    cv::Mat rangeSEN(iconSensor.get_rows(), iconSensor.get_cols(), CV_8UC1, iconSensor.getData(SickCam::DataNames::SEN));
    cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\sensor_back.bmp", rangeSEN);

    cv::Mat dst;
    cv::blur(rangeSEN, dst, Size(3, 3), Point(-1, -1));
    cv::copyMakeBorder(rangeSEN, dst, 2, 2, 2, 2, BORDER_DEFAULT);

    return;
}