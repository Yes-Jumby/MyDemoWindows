#include "InterfaceForSICK.h"
void main拟合()
{
    //创建一个用于绘制图像的空白图
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);

    //输入拟合点
    std::vector<cv::Point> points;
    points.push_back(cv::Point(48, 58));
    points.push_back(cv::Point(105, 98));
    points.push_back(cv::Point(155, 160));
    points.push_back(cv::Point(212, 220));
    points.push_back(cv::Point(248, 260));
    points.push_back(cv::Point(320, 300));
    points.push_back(cv::Point(350, 360));
    points.push_back(cv::Point(412, 400));

    std::vector<cv::Point> points1;
    points1.push_back(cv::Point(640-48, 58));
    points1.push_back(cv::Point(640-105, 98));
    points1.push_back(cv::Point(640-155, 160));
    points1.push_back(cv::Point(640-212, 220));
    points1.push_back(cv::Point(640-248, 260));
    points1.push_back(cv::Point(640-320, 300));
    points1.push_back(cv::Point(640-350, 360));
    points1.push_back(cv::Point(640-412, 400));
    cv::Scalar color_line1_ = cv::Scalar(0, 0, 255);
    cv::Scalar color_line2_ = cv::Scalar(0, 255, 0);
    cv::Scalar color_white_ = cv::Scalar(255, 255, 255);
    //将拟合点绘制到空白图上
    for (int i = 0; i < points.size(); i++)
    {
        cv::circle(image, points[i], 5, color_line1_, 2, 8, 0);
        cv::circle(image, points1[i], 5, color_line2_, 2, 8, 0);
    }
    cv::Vec4f line1_para;
    DrawLineIn3Channels(image, points, color_line1_,line1_para);
    cv::Vec4f line2_para;
    DrawLineIn3Channels(image, points1, color_line2_,line2_para);
    cv::Point2f point_insect = FindLineInsect(line1_para, line2_para);
    std::cout << "point_insect = " << point_insect << std::endl;
    cv::circle(image, point_insect, 6, color_white_, 2, 8, 0);
    cv::imshow("image", image);
    cv::waitKey(0);
    return;
}