#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <functional>
//find line
using namespace cv;
using namespace std;
int main11221(int argc, char** argv) {
    Mat src_gray,stats, centroids, img_color, img_gray;
    src_gray = imread("D:\\Stereo3D\\data\\DemoIMG\\sensor.bmp", -1);

    blur(src_gray, src_gray, Size(3, 3), Point(-1, -1));
    threshold(src_gray, src_gray,100,255, cv::THRESH_BINARY);
    Mat labels;
    int n_comps = cv::connectedComponentsWithStats(
        src_gray, //二值图像
        labels,     //和原图一样大的标记图
        stats, //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
        centroids //nccomps×2的矩阵 表示每个连通区域的质心
    );
    cout << "轮廓数" << n_comps << endl;
    //去除过小区域，初始化颜色表
    vector<cv::Vec3b> colors(n_comps);
    colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black
    vector<int> region_size(n_comps);

    
    for (int i = 0; i < n_comps; i++) {
        region_size.push_back(stats.at<int>(i, cv::CC_STAT_AREA));
        cout << "轮廓大小：" << stats.at<int>(i, cv::CC_STAT_AREA) << endl;
    }
    sort(region_size.begin(), region_size.end(), greater<int>());
    int size_threod = region_size.at(1)*0.8;
    cout << size_threod << endl;
    for (int i = 1; i < n_comps; i++) 
    {
        colors[i] = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
        cout << "轮廓大小：" << stats.at<int>(i, cv::CC_STAT_AREA) << endl;
        if (stats.at<int>(i, cv::CC_STAT_AREA) < size_threod)
            colors[i] = cv::Vec3b(0, 0, 0); // small regions are painted with black too.
    }

    //按照label值，对不同的连通域进行着色
    img_color = cv::Mat::zeros(src_gray.size(), CV_8UC3);
    for (int y = 0; y < img_color.rows; y++)
        for (int x = 0; x < img_color.cols; x++)
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= n_comps);
            img_color.at<cv::Vec3b>(y, x) = colors[label];
        }

    //统计降噪后的连通区域
    cv::cvtColor(img_color, img_gray, cv::COLOR_BGR2GRAY);
    cv::threshold(img_gray, img_gray, 1, 255, cv::THRESH_BINARY);


    n_comps = cv::connectedComponentsWithStats(img_gray, labels, stats, centroids);
    cout << "轮廓数" << n_comps << endl;


    //Mat labels_8, labels_8_bin;
    //labels.convertTo(labels_8, CV_8UC1,10/*, 255.0 / maxd*/);
    //cv::threshold(labels_8, labels_8_bin, 0, 255, THRESH_BINARY);


    //double mind, maxd;
    //cv::minMaxLoc(labels, &mind, &maxd);
    //Mat labels_8, labels_8_bin;
    //labels.convertTo(labels_8, CV_8UC1,10/*, 255.0 / maxd*/);
    //cv::threshold(labels_8, labels_8_bin, 0, 255, THRESH_BINARY);
    //cout << "MIN:" << mind << endl;
    //cout << "MAX:" << maxd << endl;
    //cout << "轮廓数" << n_comps << endl;
    //Mat src_color;
    //src_color= Mat::zeros(src_gray.size(), CV_8UC3);
    //for (int x = 0; x < src_color.rows; x++)
    //{
    //    for (int y = 0; y < src_color.cols; y++)
    //    {
    //        int label = labels.at<__int16>(x, y);//注意labels是CV_16U类型
    //        if (label == 0)
    //        {
    //            src_color.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
    //            continue;
    //        }
    //        src_color.at<Vec3b>(x, y)[0] = (label * 10 * 10 * 10) % 255;
    //        src_color.at<Vec3b>(x, y)[1] = (label * 10 * 10) % 255;
    //        src_color.at<Vec3b>(x, y)[2] = (label * 10) % 255;
    //    }
    //}
    //cv::imwrite("D:\\Stereo3D\\data\\DemoIMG\\sensor_color.bmp", src_color);

    //Canny(src_gray, canny_output, 20, 100 * 2, 3, false);
    //findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));


    ////矩形 凸包
    //vector<vector<Point>> convexs(contours.size());
    //vector<Rect> Rects(contours.size());
    //vector<int> convexs_size;
    //for (size_t i = 0; i < contours.size(); i++) {
    //    convexHull(contours[i], convexs[i], false, true);
    //    Rects[i] = boundingRect(convexs[i]);
    //    convexs_size.push_back(contours.at(i).size());
    //}
    //sort(convexs_size.begin(), convexs_size.end(), greater<int>());
    //for (size_t i = 0; i < contours.size(); i++) {
    //    cout << convexs_size.at(i)<<endl;
    //}



    //int size_threod = (convexs_size.at(0) + convexs_size.at(1)) / 3;
    //cout << size_threod << endl;

    //dst = Mat::zeros(src.size(), CV_8UC3);
    //dst1 = Mat::zeros(src.size(), CV_8UC3);
    //dst2 = Mat::zeros(src.size(), CV_8UC3);
    //Mat ImageContours = Mat::zeros(src.size(), CV_8UC1);
    //RNG rng(12345);
    //for (size_t i = 0; i < contours.size(); i++) {
    //    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    //    drawContours(dst, contours, i, color, 2, 8, hierachy, 0, Point(0, 0));
    //    drawContours(dst, convexs, i, color, 2, LINE_8, empty, 0, Point(0, 0));

    //    drawContours(dst1, convexs, i, color, 2, LINE_8, empty, 0, Point(0, 0));

    //    if(contours.at(i).size()>size_threod)
    //    drawContours(ImageContours, contours, i, Scalar(255), -1, 8);

    //    cv::rectangle(dst2, Rects[i], cv::Scalar(0,0,255));
    //}
    return 0;
}

//int main(int argc, char** argv) {
//    Mat src, src_gray, dst, dst1, dst2;
//    src = imread("D:\\Stereo3D\\data\\DemoIMG\\sensor.bmp");
//    src_gray = imread("D:\\Stereo3D\\data\\DemoIMG\\sensor.bmp", -1);
//
//    Mat canny_output;
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierachy;
//    vector<Vec4i> empty(0);
//    cv::blur(src_gray, src_gray, Size(3, 3), Point(-1, -1));
//    threshold(src_gray, src_gray, 100, 255, cv::THRESH_BINARY);
//
//    Mat labels;
//    int n_comps = connectedComponents(src_gray, labels, 4, CV_16U);
//
//    double mind, maxd;
//    cv::minMaxLoc(labels, &mind, &maxd);
//    Mat labels_8, labels_8_bin;
//    labels.convertTo(labels_8, CV_8UC1, 10/*, 255.0 / maxd*/);
//    cv::threshold(labels_8, labels_8_bin, 0, 255, THRESH_BINARY);
//    cout << "MIN:" << mind << endl;
//    cout << "MAX:" << maxd << endl;
//    cout << "轮廓数" << n_comps << endl;
//    Mat src_color;
//    src_color = Mat::zeros(src_gray.size(), CV_8UC3);
//    for (int x = 0; x < src_color.rows; x++)
//    {
//        for (int y = 0; y < src_color.cols; y++)
//        {
//            int label = labels.at<__int16>(x, y);//注意labels是CV_16U类型
//            if (label == 0)
//            {
//                src_color.at<Vec3b>(x, y) = Vec3b(255, 255, 255);
//                continue;
//            }
//            src_color.at<Vec3b>(x, y)[0] = (label * 10 * 10 * 10) % 255;
//            src_color.at<Vec3b>(x, y)[1] = (label * 10 * 10) % 255;
//            src_color.at<Vec3b>(x, y)[2] = (label * 10) % 255;
//        }
//    }
//    cv::imwrite("D:\\Stereo3D\\data\\DemoIMG\\sensor_color.bmp", src_color);
//
//    Canny(src_gray, canny_output, 20, 100 * 2, 3, false);
//    findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//
//    //矩形 凸包
//    vector<vector<Point>> convexs(contours.size());
//    vector<Rect> Rects(contours.size());
//    vector<int> convexs_size;
//    for (size_t i = 0; i < contours.size(); i++) {
//        convexHull(contours[i], convexs[i], false, true);
//        Rects[i] = boundingRect(convexs[i]);
//        convexs_size.push_back(contours.at(i).size());
//    }
//    sort(convexs_size.begin(), convexs_size.end(), greater<int>());
//    for (size_t i = 0; i < contours.size(); i++) {
//        cout << convexs_size.at(i) << endl;
//    }
//
//
//
//    int size_threod = (convexs_size.at(0) + convexs_size.at(1)) / 3;
//    cout << size_threod << endl;
//
//    dst = Mat::zeros(src.size(), CV_8UC3);
//    dst1 = Mat::zeros(src.size(), CV_8UC3);
//    dst2 = Mat::zeros(src.size(), CV_8UC3);
//    Mat ImageContours = Mat::zeros(src.size(), CV_8UC1);
//    RNG rng(12345);
//    for (size_t i = 0; i < contours.size(); i++) {
//        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//        drawContours(dst, contours, i, color, 2, 8, hierachy, 0, Point(0, 0));
//        drawContours(dst, convexs, i, color, 2, LINE_8, empty, 0, Point(0, 0));
//
//        drawContours(dst1, convexs, i, color, 2, LINE_8, empty, 0, Point(0, 0));
//
//        if (contours.at(i).size()>size_threod)
//            drawContours(ImageContours, contours, i, Scalar(255), -1, 8);
//
//        cv::rectangle(dst2, Rects[i], cv::Scalar(0, 0, 255));
//    }
//    return 0;
//}