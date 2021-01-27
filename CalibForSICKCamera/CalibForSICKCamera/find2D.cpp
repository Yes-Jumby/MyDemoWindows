#include "InterfaceForSICK.h"
/*
@≤‚ ‘‘⁄2DÕº…œ’“Ω«µ„
*/
int main2D(int argc, char** argv) {

    vector<cv::Point2f> pts_2d_;//out_put
    int gray_threod_2D_ = 80;
    int size_threod_2D_ = 500;
    cv::Mat Sensor_8_Mat_ = cv::imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\sensor_back_cp.bmp", cv::IMREAD_GRAYSCALE);
    findCorners2D(Sensor_8_Mat_, gray_threod_2D_, size_threod_2D_, pts_2d_,true);
    return 0;
}