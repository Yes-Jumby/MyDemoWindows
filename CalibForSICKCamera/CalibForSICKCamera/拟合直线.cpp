#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <fstream>
//find line
using namespace cv;
using namespace std;
int mainNHZX(int argc, char** argv) {

    Mat src, src_gray, dst,dst1;
    src = imread("D:\\Stereo3D\\data\\DemoIMG\\ProcessIdentifi.bmp");
    src_gray = imread("D:\\Stereo3D\\data\\DemoIMG\\ProcessIdentifi.bmp",-1);
    if (!src.data) {
        printf("could not load image...\n");
        return -1;
    }
    std::ofstream outfile;
    std::stringstream ss;
    outfile.open("D:\\Stereo3D\\data\\DemoIMG\\ProcessIdentifi.txt", std::ios::ate | std::ios::binary);
    if (!outfile)
    {
        return false;
    }
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss.precision(3);
    int idx = 0;
    for (int x = 0; x < src_gray.cols; x++)
    {
        for (int y = 0; y < src_gray.rows; y++)
        {
            if (src_gray.at<uchar>(y, x) > 0)
            {
                ss << x << " " << y << "\n";
            }
        }
    }


    outfile << ss.str();
    outfile.close();

    //Canny(src, src_gray, 150, 200);
    cvtColor(src_gray, dst, CV_GRAY2BGR);
    cvtColor(src_gray, dst1, CV_GRAY2BGR);
    imshow("edge image", src_gray);
    //cvtColor(src_gray, dst, CV_GRAY2BGR);
    //src.copyTo(dst);
    //src.copyTo(dst1);

    vector<Vec2f> lines;
    HoughLines(src_gray, lines, 1, CV_PI / 180, 150, 0, 0);
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0]; // 极坐标中的r长度
        float theta = lines[i][1]; // 极坐标中的角度
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        // 转换为平面坐标的四个点
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dst, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
    }

    
    vector<Vec4f> plines;
    HoughLinesP(src_gray, plines, 1, CV_PI / 180.0, 120, 100, 10);
    Scalar color = Scalar(0, 0, 255);
    for (size_t i = 0; i < plines.size(); i++) {
    Vec4f hline = plines[i];
    line(dst1, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 1, LINE_AA);
    }
    //imshow(OUTPUT_TITLE, dst);
    //waitKey(0);
    return 0;
}