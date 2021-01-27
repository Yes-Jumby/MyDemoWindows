#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
using namespace cv;

int main1(int argc, char** argv) {
	Mat src = imread("D:/1.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char INPUT_T[] = "input image";
	char OUTPUT_T[] = "histogram demo";
	namedWindow(INPUT_T, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_T, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_T, src);

	// 分通道显示
	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	//imshow("single channel demo", bgr_planes[0]);

	// 计算直方图
	int histSize = 256;
	float range[] = { 0, 256 };
	const float *histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);

	// 归一化
	int hist_h = 400;
	int hist_w = 512;
	int bin_w = hist_w / histSize;
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());//映射到  【0, hist_h】
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

	Point p1 = Point(0, 0);
	Point p2;
	p2.x = 400;
	p2.y = 400;
	Scalar color = Scalar(0, 0, 255);
	line(histImage, p1, p2, color, 1, LINE_AA);

	// render histogram chart
	for (int i = 1; i < histSize; i++) {
		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);

		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);

		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow(OUTPUT_T, histImage);

	waitKey(0);
	return 0;
}