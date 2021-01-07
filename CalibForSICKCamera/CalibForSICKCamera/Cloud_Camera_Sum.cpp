#include "InterfaceForSICK.h"
#include <Ranger3.h>
using namespace cv;
using namespace std;



void m_calibration_cloud_camera(const vector<cv::Point2f> &pts_2d_, const vector<cv::Point3f> &pts_3d_, string result, Mat cameraMatrix, Mat distCoeffs)
{
    FileStorage fswrite(result, FileStorage::WRITE);

    ////solvepnp
    //vector<Point3f> pts_3d;
    //vector<Point2f> pts_2d;

    //double x_resolution = 0.2554024;
    ////3D
    //pts_3d.push_back(cv::Point3f(1138* x_resolution -137.3054,  90 - 83, 14.591));//BOARD 左下 右下 右上 左上
    //pts_3d.push_back(cv::Point3f(1414* x_resolution -137.3054,  90 - 83, 13.558));
    //pts_3d.push_back(cv::Point3f(1411* x_resolution -137.3054,  90 - 13, 15.088));
    //pts_3d.push_back(cv::Point3f(1136* x_resolution -137.3054,  90 - 13, 15.49));

    //pts_3d.push_back(cv::Point3f(987 * x_resolution - 137.3054, 90 - 40, 17.059));//5 左下 右下 右上 左上
    //pts_3d.push_back(cv::Point3f(1022* x_resolution -137.3054,  90 - 40, 17.021));
    //pts_3d.push_back(cv::Point3f(1024* x_resolution -137.3054,  90 - 11, 16.676));
    //pts_3d.push_back(cv::Point3f(989 * x_resolution - 137.3054, 90 - 11, 16.083));

    //pts_3d.push_back(cv::Point3f(1468* x_resolution -137.3054,  90 - 76, 20.79));//10 左下 右下 右上 左上
    //pts_3d.push_back(cv::Point3f(1505* x_resolution -137.3054,  90 - 76, 21.23));
    //pts_3d.push_back(cv::Point3f(1503* x_resolution -137.3054,  90 - 47, 20.369));
    //pts_3d.push_back(cv::Point3f(1465* x_resolution -137.3054,  90 - 47, 20.714));


    ////2D
    //pts_2d.push_back(cv::Point2f(1076, 617));//BOARD 左下 右下 右上 左上
    //pts_2d.push_back(cv::Point2f(1542, 619));
    //pts_2d.push_back(cv::Point2f(1513, 243));
    //pts_2d.push_back(cv::Point2f(1093, 240));

    //pts_2d.push_back(cv::Point2f(845, 409));//5 左下 右下 右上 左上
    //pts_2d.push_back(cv::Point2f(896, 411));
    //pts_2d.push_back(cv::Point2f(914, 258));
    //pts_2d.push_back(cv::Point2f(865, 256));

    //pts_2d.push_back(cv::Point2f(1642, 607));//10 左下 右下 右上 左上
    //pts_2d.push_back(cv::Point2f(1706, 602));
    //pts_2d.push_back(cv::Point2f(1680, 435));
    //pts_2d.push_back(cv::Point2f(1620, 435));


    Mat r, rvecsMat, tvecsMat;


    //solvePnP(pts_3d, pts_2d, cameraMatrix, distCoeffs, r, tvecsMat,false,cv::SOLVEPNP_EPNP);
	
    solvePnP(pts_3d_, pts_2d_, cameraMatrix, distCoeffs, r, tvecsMat, false, cv::SOLVEPNP_EPNP);
	
	//ba todo
    cv::Rodrigues(r, rvecsMat); // r 为旋转向量形式，用 Rodrigues 公式转换为矩阵
    cout << "r" << endl << r*180.0 / 3.1415926 << endl;
    cout << "rvecsMat" << endl << rvecsMat << endl;
    cout << "tvecsMat" << endl << tvecsMat << endl;

    fswrite << "r" << r*180.0/3.1415926;
    fswrite << "rvecsMat" << rvecsMat;
    fswrite << "tvecsMat" << tvecsMat;
    fswrite.release();

}

void main()
{
    //3D-source
    SickCam::ImgT iconRange;
    iconRange.loadFromIconFile("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\3D\\calibed_3D", 1.0);
    cv::Mat rangeCALIm(iconRange.get_rows(), iconRange.get_cols(), CV_32FC1, iconRange.getData(SickCam::DataNames::RAN_CAL));
    //cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\rangeCALIm.png", rangeCALIm);
    cv::Mat rangeCALIm_FLIP;
    //cv::Mat rangeCALIm_FLIP_save, rangeCALIm_FLIP_read;
    cv::flip(rangeCALIm, rangeCALIm_FLIP, 0);//沿着X轴旋转即垂直旋转

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
    int iteration_count_ = 3;
    TransHeight2DTo3D(rangeCALIm_FLIP_thre_, pts_3d_2d_, x_resolution_, x_min_, iteration_count_, pts_3d_);
    //3D
    std::string fileName1 = "E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\HeightMap2D3D.txt";
    std::ofstream fileOutput(fileName1.c_str());   // 打开文件，建立数据流
    cv::Point2f p2D_;
    cv::Point3f p3D_;


    //2D
    vector<cv::Point2f> pts_2d_;//out_put
    int gray_threod_2D_ = 80;
    int size_threod_2D_ = 500;
    cv::Mat Sensor_8_Mat_ = cv::imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\sensor_back_cp.bmp", cv::IMREAD_GRAYSCALE);
    findCorners2D(Sensor_8_Mat_, gray_threod_2D_, size_threod_2D_, pts_2d_, true);

    for (int i = 0; i < pts_3d_2d_.size(); i++)
    {
        p2D_ = pts_3d_2d_.at(i);
        p3D_ = pts_3d_.at(i);
        //fileOutput << p3D.x << "   " << p3D.y << std::endl;
        fileOutput << pts_2d_.at(i)<<"      "<<p2D_ << "   " << p3D_ << std::endl;;

    }
    fileOutput.close(); //关闭数据流

    FileStorage fsread("caliberation_result_201109.xml", FileStorage::READ);

    Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));        // 摄像机内参数矩阵
    Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));          // 摄像机的5个畸变系数：k1,k2,p1,p2,k3
    fsread["cameraMatrix"]>> cameraMatrix;
    fsread["distCoeffs"]>> distCoeffs;
    cout << "cameraMatrix=" << endl << cameraMatrix << endl;
    cout << "distCoeffs=" << endl << distCoeffs << endl;


    m_calibration_cloud_camera(pts_2d_, pts_3d_, "caliberation_result_cloud-camera_210107.xml", cameraMatrix, distCoeffs);


    return;
}