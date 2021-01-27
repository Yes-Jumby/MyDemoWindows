#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;
int main2()
{
	Mat src = imread("D:/Stereo3D/data/test1209/BINOCULAR/0318/3/0000.bmp");
	Mat gray, binary, dist;
	Mat result = Mat::zeros(src.rows, src.cols, CV_8UC1);
	int w = src.cols;
	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	distanceTransform(binary, dist, DIST_L1, DIST_MASK_PRECISE);
	dist = dist / 10;
	vector<Point>ypts;
	vector<Point>xpts;
	Vec4f lines;
	Vec4f ls;
	for (int row = 0; row < dist.rows; row++)
	{
		int cx = 0;
		int cy = 0;
		float max_d = 0;
		for (int col = 0; col < dist.cols; col++)
		{
			float d = dist.at<float>(row, col);
			if (d > max_d)
			{
				max_d = d;
				cx = col;
				cy = row;
			}
		}
		result.at<uchar>(cy, cx) = 255;
		Point p(cx, cy);
		ypts.push_back(p);

	}
	for (int col = 0; col < gray.cols; col++)
	{
		int cx = 0;
		int cy = 0;
		float max_d = 0;
		for (int row = 0; row < gray.rows; row++)
		{
			float d = dist.at<float>(row, col);
			if (d > max_d)
			{
				max_d = d;
				cx = col;
				cy = row;
			}
		}
		result.at<uchar>(cy, cx) = 255;
		Point p1(cx, cy);
		xpts.push_back(p1);

	}
	fitLine(ypts, lines, DIST_L1, 0, 0.01, 0.01);
	fitLine(xpts, ls, DIST_L1, 0, 0.01, 0.01);
	float vx = lines[0];
	float vy = lines[1];
	float x = lines[2];
	float y = lines[3];
	int y1 = int((-x*vy / vx) + y);
	int y2 = int((w - x)*vy / vx + y);
	float vxs = ls[0];
	float vys = ls[1];
	float xs = ls[2];
	float ys = ls[3];
	int y1s = int((-xs*vys / vxs) + ys);
	int y2s = int((w - xs)*vys / vxs + ys);
	line(src, Point((w - 1), y2), Point(0, y1), Scalar(255, 0, 0), 1);
	line(src, Point((w - 1), y2s), Point(0, y1s), Scalar(0, 0, 255), 1);
	waitKey();
	return 0;
}
