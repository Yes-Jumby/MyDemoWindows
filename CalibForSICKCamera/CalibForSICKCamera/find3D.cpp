#include "InterfaceForSICK.h"
#include <Ranger3.h>

/*
@������3Dͼ���ҽǵ�
*/
int main3D(int argc, char** argv) {

    //3D-source
    SickCam::ImgT iconRange;
    iconRange.loadFromIconFile("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\3D\\calibed_3D", 1.0);
    cv::Mat rangeCALIm(iconRange.get_rows(), iconRange.get_cols(), CV_32FC1, iconRange.getData(SickCam::DataNames::RAN_CAL));
    //cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm.png", rangeCALIm);
    cv::Mat rangeCALIm_FLIP;
    //cv::Mat rangeCALIm_FLIP_save, rangeCALIm_FLIP_read;
    cv::flip(rangeCALIm, rangeCALIm_FLIP, 0);//����X����ת����ֱ��ת

    double mind, maxd;
    cv::minMaxLoc(rangeCALIm_FLIP, &mind, &maxd);
    cout << "MIN:" << mind << endl;
    cout << "MAX:" << maxd << endl;
    cv::Mat rangeCALIm_FLIP_thre_;
    cv::threshold(rangeCALIm_FLIP, rangeCALIm_FLIP_thre_, 15.0, maxd, cv::THRESH_TOZERO);

    cv::Mat rangeCALIm_FLIP_8, rangeCALIm_FLIP_8_bin;
    rangeCALIm_FLIP_thre_.convertTo(rangeCALIm_FLIP_8, CV_8UC1, 255.0 / maxd);
    cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP_8.bmp", rangeCALIm_FLIP_8);

    vector<cv::Point2f> pts_3d_2d_;//out_put
    int gray_threod_3D_ = 0;
    int size_threod_3D_ = 500;
    //cv::Mat Range3D_FLIP_8_Mat_ = cv::imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm_FLIP_8.bmp", cv::IMREAD_UNCHANGED);
    findCorners3D(rangeCALIm_FLIP_8, gray_threod_3D_, size_threod_3D_, pts_3d_2d_);

    //transfer to 3D truth
    vector<cv::Point3f> pts_3d_;//out_put
    float x_resolution_ = iconRange.getC_scaleX();
    float x_min_ = iconRange.getC_lower_bound_x();
    int iteration_count_ = 3 ;
    TransHeight2DTo3D(rangeCALIm_FLIP_thre_, pts_3d_2d_, x_resolution_, x_min_, iteration_count_, pts_3d_);
    //3D
    std::string fileName1 = "E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\HeightMap2D3D.txt";
    std::ofstream fileOutput(fileName1.c_str());   // ���ļ�������������
    cv::Point2f p2D_;
    cv::Point3f p3D_;
    for (int i = 0; i < pts_3d_2d_.size(); i++)
    {
        p2D_ = pts_3d_2d_.at(i);
        p3D_ = pts_3d_.at(i);
        //fileOutput << p3D.x << "   " << p3D.y << std::endl;
        fileOutput << p2D_ <<"  "<< p3D_ << std::endl;;

    }
    fileOutput.close(); //�ر�������


    return 0;
}