#include "opencv.hpp"

#include <iostream>
#include <fstream> 
#include <io.h>  
#include <string>  
#include<vector>
#include <Ranger3.h>
using namespace cv;
using namespace std;

/*
@param File_Directory 为文件夹目录
@param FileType 为需要查找的文件类型
@param FilesName 为存放文件名的容器
*/
void getFilesName1(string &File_Directory, string &FileType, vector<string>&FilesName)
{
    string buffer = File_Directory + "\\*" + FileType;

    _finddata_t c_file;   // 存放文件名的结构体

    long long hFile;//http://www.mamicode.com/info-detail-2204262.html
    hFile = _findfirst(buffer.c_str(), &c_file);   //找第一个文件命

    if (hFile == -1L)   // 检查文件夹目录下存在需要查找的文件
        printf("No %s files in current directory!\n", FileType);
    else
    {
        string fullFilePath;
        do
        {
            fullFilePath.clear();

            //名字
            fullFilePath = File_Directory + "\\" + c_file.name;

            FilesName.push_back(fullFilePath);

        } while (_findnext(hFile, &c_file) == 0);  //如果找到下个文件的名字成功的话就返回0,否则返回-1  
        _findclose(hFile);
    }
}

void m_calibration_cloud_camera(vector<string> &FilesName, string result, Size board_size, Size square_size, Mat cameraMatrix, Mat distCoeffs)
{
    FileStorage fswrite(result, FileStorage::WRITE);

    cout << "开始提取角点………………" << endl;
    int image_count = 0;           // 图像数量 
    Size image_size;                                                // 图像的尺寸 
    int imag_bad = 0;
    vector<Point2f> image_points;                                   // 缓存每幅图像上检测到的角点
    vector<vector<Point2f>> image_points_seq;                       // 保存检测到的所有角点

    for (int i = 0; i < FilesName.size(); i++)
    {
        image_count++;

        // 用于观察检验输出
        //cout << "image_count = " << image_count << endl;
        Mat imageInput = imread(FilesName[i]);
        if (image_count == 1)  //读入第一张图片时获取图像宽高信息
        {
            image_size.width = imageInput.cols;
            image_size.height = imageInput.rows;
            cout << "image_size.width = " << image_size.width << endl;
            cout << "image_size.height = " << image_size.height << endl;
        }

        /* 提取角点 */
        bool ok = findChessboardCorners(imageInput, board_size, image_points, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        if (0 == ok)
        {
            imag_bad++;
            cout << "第" << image_count << "张照片提取角点失败，请删除后，重新标定！" << FilesName[i] << imag_bad << endl; //找不到角点
                                                                                                      /*imshow("失败照片", imageInput);
                                                                                                      waitKey(0);*/
        }
        else
        {
            Mat view_gray;
            //cout << "imageInput.channels()=" << imageInput.channels() << endl;
            cvtColor(imageInput, view_gray, CV_RGB2GRAY);

            /* 亚像素精确化 */
            //find4QuadCornerSubpix(view_gray, image_points, Size(5, 5)); //对粗提取的角点进行精确化
            cv::cornerSubPix(view_gray, image_points, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 20, 0.01));

            image_points_seq.push_back(image_points);  //保存亚像素角点

                                                       /* 在图像上显示角点位置 */
            //vector<Point2f> image_points_;
            //for (int i = 0; i < image_points.size(); i++)
            //{
            //    
            //    image_points_.push_back(image_points.at(i));
            //    drawChessboardCorners(view_gray, board_size, image_points_, true);

            //    imshow("Camera Calibration", view_gray);//显示图片
            //    waitKey(10);//暂停0.1S    
            //}
            drawChessboardCorners(view_gray, board_size, image_points, true);

            imshow("Camera Calibration", view_gray);//显示图片
            waitKey(10);//暂停0.1S     
        }
    }
    //solvepnp
    vector<Point3f> pts_3d;
    vector<Point2f> pts_2d;

    double x_resolution = 0.2554024;
    //3D
    pts_3d.push_back(cv::Point3f(1138* x_resolution -137.3054,  90 - 83, 14.591));//BOARD 左下 右下 右上 左上
    pts_3d.push_back(cv::Point3f(1414* x_resolution -137.3054,  90 - 83, 13.558));
    pts_3d.push_back(cv::Point3f(1411* x_resolution -137.3054,  90 - 13, 15.088));
    pts_3d.push_back(cv::Point3f(1136* x_resolution -137.3054,  90 - 13, 15.49));

    pts_3d.push_back(cv::Point3f(987 * x_resolution - 137.3054, 90 - 40, 17.059));//5 左下 右下 右上 左上
    pts_3d.push_back(cv::Point3f(1022* x_resolution -137.3054,  90 - 40, 17.021));
    pts_3d.push_back(cv::Point3f(1024* x_resolution -137.3054,  90 - 11, 16.676));
    pts_3d.push_back(cv::Point3f(989 * x_resolution - 137.3054, 90 - 11, 16.083));

    pts_3d.push_back(cv::Point3f(1468* x_resolution -137.3054,  90 - 76, 20.79));//10 左下 右下 右上 左上
    pts_3d.push_back(cv::Point3f(1505* x_resolution -137.3054,  90 - 76, 21.23));
    pts_3d.push_back(cv::Point3f(1503* x_resolution -137.3054,  90 - 47, 20.369));
    pts_3d.push_back(cv::Point3f(1465* x_resolution -137.3054,  90 - 47, 20.714));


    //2D
    pts_2d.push_back(cv::Point2f(1076, 617));//BOARD 左下 右下 右上 左上
    pts_2d.push_back(cv::Point2f(1542, 619));
    pts_2d.push_back(cv::Point2f(1513, 243));
    pts_2d.push_back(cv::Point2f(1093, 240));

    pts_2d.push_back(cv::Point2f(845, 409));//5 左下 右下 右上 左上
    pts_2d.push_back(cv::Point2f(896, 411));
    pts_2d.push_back(cv::Point2f(914, 258));
    pts_2d.push_back(cv::Point2f(865, 256));

    pts_2d.push_back(cv::Point2f(1642, 607));//10 左下 右下 右上 左上
    pts_2d.push_back(cv::Point2f(1706, 602));
    pts_2d.push_back(cv::Point2f(1680, 435));
    pts_2d.push_back(cv::Point2f(1620, 435));


    Mat r, rvecsMat, tvecsMat;


    solvePnP(pts_3d, pts_2d, cameraMatrix, distCoeffs, r, tvecsMat,false,cv::SOLVEPNP_EPNP);
	
	
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
    //3D
    // ------ Convert
    SickCam::ImgT iconRange;
    iconRange.loadFromIconFile("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\3D\\calibed_3D", 1.0);
    cv::Mat rangeCALIm(iconRange.get_rows(), iconRange.get_cols(), CV_32FC1, iconRange.getData(SickCam::DataNames::RAN_CAL));
    cv::Mat rangeCALIm_FLIP;
    cv::flip(rangeCALIm, rangeCALIm_FLIP, 0);
    double mind, maxd;
    cv::minMaxLoc(rangeCALIm_FLIP, &mind, &maxd);
    cout << "MIN:" << mind << endl;
    cout << "MAX:" << maxd << endl;


    cv::Mat rangeCALIm_FLIP_8, rangeCALIm_FLIP_8_bin;
    rangeCALIm_FLIP.convertTo(rangeCALIm_FLIP_8, CV_8UC1,255.0/ maxd);
    cv::minMaxLoc(rangeCALIm_FLIP_8, &mind, &maxd);
    cout << "MIN:" << mind << endl;
    cout << "MAX:" << maxd << endl;
    cv::threshold(rangeCALIm_FLIP_8, rangeCALIm_FLIP_8_bin,151,255, THRESH_BINARY);

    SickCam::ImgT iconSensor;
    iconSensor.loadFromIconFile("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\2D\\1", 1.0);
    cv::Mat rangeSEN(iconSensor.get_rows(), iconSensor.get_cols(), CV_8UC1, iconSensor.getData(SickCam::DataNames::SEN));
    cv::imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\sensor_back.bmp", rangeSEN);

    cv::Mat dst;
    cv::blur(rangeSEN, dst, Size(3, 3), Point(-1, -1));
    cv::copyMakeBorder(rangeSEN, dst,2,2,2,2, BORDER_DEFAULT);
    //2D
    string File_Directory1 = "E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror";   //文件夹目录1

    string FileType = ".bmp";    // 需要查找的文件类型

    vector<string>FilesName1;    //存放文件名的容器

    getFilesName1(File_Directory1, FileType, FilesName1);   // 标定所用图像文件的路径


    Size board_size = Size(11, 8);                         // 标定板上每行、列的角点数 
    Size square_size = Size(5, 5);                       // 实际测量得到的标定板上每个棋盘格的物理尺寸，单位mm

    FileStorage fsread("caliberation_result_201109.xml", FileStorage::READ);

    Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));        // 摄像机内参数矩阵
    Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));          // 摄像机的5个畸变系数：k1,k2,p1,p2,k3
    fsread["cameraMatrix"]>> cameraMatrix;
    fsread["distCoeffs"]>> distCoeffs;
    cout << "cameraMatrix=" << endl << cameraMatrix << endl;
    cout << "distCoeffs=" << endl << distCoeffs << endl;


    m_calibration_cloud_camera(FilesName1, "caliberation_result_cloud-camera_201117.xml", board_size, square_size, cameraMatrix, distCoeffs);


    return;
}