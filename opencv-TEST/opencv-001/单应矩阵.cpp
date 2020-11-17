#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

struct userdata {
	Mat im;
	vector<Point2f> points;
};

const int cornerpoint_size = 5;
void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		userdata *data = ((userdata *)data_ptr);
		circle(data->im, Point(x, y), 3, Scalar(0, 255, 255), 5, CV_AA);
		imshow("Image", data->im);
		if (data->points.size() < cornerpoint_size)
		{
			data->points.push_back(Point2f(x, y));
		}
	}

}

///**********
//【题目】编写复制一棵二叉树的递归算法。
//二叉链表类型定义：
//typedef char TElemType; // 设二叉树的元素为char类型
//typedef struct BiTNode {
//  TElemType data;
//    struct BiTNode  *lchild, *rchild;
//	} BiTNode, *BiTree;
//	**********/
//void CopyBiTree(BiTree T, BiTree &TT)
///* 递归复制二叉树T得到TT */
//{
//	if (T == NULL)
//		return;
//	else {
//		TT = (BiTree)malloc(sizeof(BiTNode));
//		TT->data = T->data;
//		CopyBiTree(T->lchild, TT->lchild);
//		CopyBiTree(T->rchild, TT->rchild);
//	}

int main(int argc, char** argv)
{
    Mat im_1 = imread("D:\\下载\\extra\\range-1.tiff",-1);//替换的照片
    Mat im_2 = imread("D:\\下载\\extra\\range-2.tiff",-1);//替换的照片
    cv::Mat senIm3;
    cv::Mat senIm(2560, 832, CV_8UC1);
    std::vector<cv::Mat> vSenImg(3, senIm);
    cv::merge(vSenImg, senIm3);
	int* b = nullptr;
	int* c = *&b; 

	// Read in the image.
	//Mat im_src = imread("first-image.jpg");
	Mat im_src = imread("E:\\test_PIC\\model.jpg");//替换的照片
	Size size = im_src.size();

	// Create a vector of points.
	vector<Point2f> pts_src;//左上 右上 右下 左下
	pts_src.push_back(Point2f(0, 0));
	pts_src.push_back(Point2f(size.width - 1, 0));
	pts_src.push_back(Point2f(size.width - 1, size.height - 1));
	pts_src.push_back(Point2f(0, size.height - 1));
    pts_src.push_back(Point2f(size.width/2 - 1, size.height/2 - 1));



	// Destination image
	//Mat im_dst = imread("times-square.jpg");
	Mat im_dst = imread("E:\\test_PIC\\origin.png");


	// Set data for mouse handler
	Mat im_temp = im_dst.clone();
	userdata data;
	data.im = im_temp;


	//show the image
	imshow("Image", im_temp);

	cout << "Click on four corners of a billboard and then press ENTER" << endl;
	//set the callback function for any mouse event
	setMouseCallback("Image", mouseHandler, &data);
	waitKey(0);

	Mat H = findHomography(pts_src, data.points, 0);
	Mat logo;
	warpPerspective(im_src, logo, H, im_dst.size());

	//阈值化
	Mat logo1;
	threshold(logo, logo1, 0, 255, THRESH_BINARY_INV);

	im_dst.copyTo(logo, logo1);//把im_dst和logo1做 与 运算后再和logo相加
	//im_dst.copyTo(logo);//把im_dst和logo1做 与 运算后再和logo相加
	imwrite("final.jpg", logo);

	// Display image.

	imshow("Image", logo);

	waitKey(0);

	return 0;
}
