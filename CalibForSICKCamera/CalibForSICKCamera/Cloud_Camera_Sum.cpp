#include "InterfaceForSICK.h"
#include <Ranger3.h>
using namespace cv;
using namespace std;

#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include "ceres/rotation.h"
#include <chrono>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<fstream>
#include<math.h>
using namespace std;
double sumVector(vector<double> x)
{
    double sum = 0.0;
    for (int i = 0; i<x.size(); ++i)
    {
        sum += x[i];
    }
    return sum / x.size();
}
// 代价函数的计算模型
struct Resection
{
    Resection(double X, double Y, double Z, double x, double y,
        double fx, double fy, double cx, double cy,
        double *lensDistort) :_X(X), _Y(Y), _Z(Z), observed_x_(x), observed_y_(y)
        , fx_(fx), fy_(fy), cx_(cx), cy_(cy), lensDistort_(lensDistort) {
        //P_W_[0] = _X;
        //P_W_[1] = _Y;
        //P_W_[2] = _Z;
    }
    // 残差的计算
    template <typename T>
    bool operator() (const T* const camPose, T* residual) const     // 残差
    {
        T AngleAxis[3] = { camPose[0],camPose[1],camPose[2] };
        const T P_W_[3] = {(T)_X,(T)_Y,(T)_Z};
        T P_C_[3];
        ceres::AngleAxisRotatePoint(AngleAxis, P_W_, P_C_);
        P_C_[0] = P_C_[0] + camPose[3];
        P_C_[1] = P_C_[1] + camPose[4];
        P_C_[2] = P_C_[2] + camPose[5];

        // Compute the center of distortion. The sign change comes from
        // the camera model that Noah Snavely's Bundler assumes, whereby
        // the camera coordinate system has a negative z axis.

        T xp = P_C_[0] / P_C_[2];
        T yp = P_C_[1] / P_C_[2];

        // Apply second and fourth order radial distortion.
        T l1 = T(lensDistort_[0]);
        T l2 = T(lensDistort_[1]);
        T r2 = xp*xp + yp*yp;
        T distortion = 1.0 + r2  * (l1 + l2  * r2);

        // Compute final projected point position.
        T xp_undistort_ = distortion * xp;
        T yp_undistort_ = distortion * yp;

        T predicted_x = fx_ * xp_undistort_ + cx_;
        T predicted_y = fy_ * yp_undistort_ + cy_;

        // The error is the difference between the predicted and observed position.
        residual[0] = predicted_x - T(observed_x_);
        residual[1] = predicted_y - T(observed_y_);

        return true; //千万不要写成return 0,要写成return true
    }
private:
    const double _X, _Y, _Z;
     //double P_W_[3];
    const double observed_x_, observed_y_;
    const double   fx_, fy_, cx_, cy_;
    const double *lensDistort_;
};
/*
@输入找到的2D图角点和3D图角点，PNP找到初值，ceres对初值进行优化
*/
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
    cout << "PNP" << endl;
    cout << "r" << endl << r*180.0 / 3.1415926 << endl;
    cout << "rvecsMat" << endl << rvecsMat << endl;
    cout << "tvecsMat" << endl << tvecsMat << endl;

    fswrite << "PNP_r" << r*180.0/3.1415926;
    fswrite << "PNP_rvecsMat" << rvecsMat;
    fswrite << "PNP_tvecsMat" << tvecsMat;


    cout << "开始评价标定结果………………" << endl;
    double total_err = 0.0;            // 所有图像的平均误差的总和 
    double err = 0.0;                  // 每幅图像的平均误差
    double totalErr = 0.0;
    double totalPoints = 0.0;
    vector<Point2f> image_points_pro;     // 保存重新计算得到的投影点
    vector<vector<Point3f>> object_points_seq;
    object_points_seq.push_back(pts_3d_);

    projectPoints(object_points_seq[0], r, tvecsMat, cameraMatrix, distCoeffs, image_points_pro);   //通过得到的摄像机内外参数，对角点的空间三维坐标进行重新投影计算

    err = norm(Mat(pts_2d_), Mat(image_points_pro), NORM_L2);

    totalErr += err*err;//SSE
    totalPoints += object_points_seq[0].size();

    err /= object_points_seq[0].size();

    //ceres
    double camPose[6] = { r.at<double>(0, 0),r.at<double>(1, 0),r.at<double>(2, 0), 
        tvecsMat.at<double>(0, 0), tvecsMat.at<double>(1, 0), tvecsMat.at<double>(2, 0)};
    for (int i = 0; i < 6; i++)
    {
        cout << camPose[i] << endl;
    }
    
    double fx_ = cameraMatrix.at<double>(0, 0);
    double fy_ = cameraMatrix.at<double>(1, 1);
    double cx_ = cameraMatrix.at<double>(0, 2);
    double cy_ = cameraMatrix.at<double>(1, 2);
    double lensDistort[4] = { distCoeffs.at<double>(0,0),distCoeffs.at<double>(0,1), distCoeffs.at<double>(0,2), distCoeffs.at<double>(0,3)};
    ceres::Problem problem;
    try
    {
        for (int i = 0; i<pts_3d_.size(); ++i)
        {
            ceres::CostFunction *costfunction = new ceres::AutoDiffCostFunction<Resection, 2, 6>(new Resection(pts_3d_.at(i).x, pts_3d_.at(i).y, pts_3d_.at(i).z, 
                                                                                                pts_2d_.at(i).x, pts_2d_.at(i).y, 
                                                                                                fx_,fy_,cx_,cy_,
                                                                                                lensDistort));
            //将残差方程和观测值加入到problem,nullptr表示核函数为无，
            problem.AddResidualBlock(costfunction, nullptr, camPose);
        }
    }
    catch (...)
    {
        cout << "costFunction error" << endl;
    }

    // 配置求解器
    ceres::Solver::Options options;     // 这里有很多配置项可以填
    options.linear_solver_type = ceres::DENSE_QR;  // 增量方程如何求解
    options.minimizer_progress_to_stdout = true;   // 输出到cout
                                                   //    options.max_num_iterations=25;
    ceres::Solver::Summary summary;                // 优化信息
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    ceres::Solve(options, &problem, &summary);  // 开始优化
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

    // 输出结果
    cout << summary.BriefReport() << endl;

    //save data
    r.at<double>(0, 0) = camPose[0];
    r.at<double>(1, 0) = camPose[1];
    r.at<double>(2, 0) = camPose[2];
    tvecsMat.at<double>(0, 0) = camPose[3];
    tvecsMat.at<double>(1, 0) = camPose[4];
    tvecsMat.at<double>(2, 0) = camPose[5];
                                                      //ba todo
    cv::Rodrigues(r, rvecsMat); // r 为旋转向量形式，用 Rodrigues 公式转换为矩阵
    cout << "CERES" << endl;
    cout << "r" << endl << r*180.0 / 3.1415926 << endl;
    cout << "rvecsMat" << endl << rvecsMat << endl;
    cout << "tvecsMat" << endl << tvecsMat << endl;

    fswrite << "CERES_r" << r*180.0 / 3.1415926;
    fswrite << "CERES_rvecsMat" << rvecsMat;
    fswrite << "CERES_tvecsMat" << tvecsMat;
    fswrite << "CERES_InitialCost" << summary.initial_cost;
    fswrite << "CERES_FinalCost" << summary.final_cost;;
    fswrite.release();

}
/*
@读取3D图和2D图，分别找到2D图角点和3D图角点，PNP找到初值，ceres对初值进行优化
*/
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


    m_calibration_cloud_camera(pts_2d_, pts_3d_, "caliberation_result_cloud-camera_210111_min_Edge_.xml", cameraMatrix, distCoeffs);


    return;
}