
//#include<stdio.h>
//#include<stdlib.h>
//#include <string.h>
//#include <stack>
//#include "cv.hpp"
//using namespace cv;
//using namespace std;
//
//
//int main()
//{
//    return 0;
//}

/*
By J.A 2019.6.12
提取圆点靶标圆的中心，为了实现较好的标定手法，需要提高我们的提点的准确度
圆形在透视投影变换之后，不再是一个圆形，而是椭圆形。
一般的方法用于获取椭圆的中心，但是椭圆的中心不是圆的中心。
所以我们需要先提取四个最远端的特征点的坐标，求解H矩阵，并进行透视畸变矫正。
之后针对矫正图，调用OpenCV的函数获得圆点靶标的特征点的中心。
最后将提到的点重建到图像平面（反透视投影变换, 这样我们获得的圆心才是真正的圆心。
注：
1、	Halcon的标定板，采用一个五边形作为外框，外框是一种线特征，不会随着透视投影产生位置畸变。(实际上，外框如果是一系列棋盘格构成的也行）。
在这种情况下，我们可以先识别外框，然后依然依照上述的思想，获得特征点的坐标。据传，这也是Halcon的标定所采用的方法，由于本方法提取的坐标一开始并不是准确的，所以难免产生误差
可以预计，本方法相对于上述的方法精度低一些。但是我们可以采用迭代的思想，在变换完成求得h矩阵后，再进行之前的操作，获得更加细化的H矩阵，效率上不高，但是效果应该可以做到相当
2、 OpenCV寻找圆点标定板的函数 调用的是featuredector寻找点的中心，需要进行阈值化操作，并采用一定的过滤手段，由于我们的靶标上反射的光均匀程度不一，而且我们的相机也有一定的噪声
个人建议首先采用一定大小的高斯滤波对矫正了透视投影畸变的图案进行滤波，以使灰度值变均匀，同时也不太影响我们的中心提取。结合圆中心提取的思想，我们也可以用steger方法获得更加
精准的圆心，从而提高标定的精度
3、	在诸如相移法等一些涉及到投影仪和相机的标定过程中，我们需要能够知道特征点的具体的其他信息，这个时候采用角点靶标（张正友）的方法就不合适了，必须采用圆点靶标，从而能够获得圆
心的相位信息，提高整体测量系统的精度。
*/

//openCV 标准头文件
#include <opencv2\core.hpp>
#include <opencv2\features2d.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\calib3d.hpp>

//c++ 标准头文件
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <direct.h>
#include <io.h>

//嗯 尽管不是一个好习惯，但是我还是用了（方便&人生苦短）
using namespace std;
using namespace cv;

//一些全局变量
const int WINDOW_SIZE_HEIGHT = 61;
const int WINDOW_SIZE_WIDTH = 61;
int g_rough_center_cnt = 0;

//用于参数回调
struct Params
{
    Mat p_ori_img;
    vector<KeyPoint> point;
    string this_window_name;
};

//靶标的具体尺寸信息，注意单位全部为mm
struct Calib_Board
{
    Size spots_size;	//靶标上点的尺寸
    Size mm_size;		//毫米尺寸
    float dx;			//纵向点间距
    float dy;			//横向点间距
    float ds;			//小点直径
    float dl;			//大点直径
};

//注 本次使用的靶标是11*9的靶标，点距15mm，大圆直径7mm 小圆直径3.5mm 具体参见 GR180-11*9靶标 外形尺寸为180*150mm（注意，这个参数也用于重建我们的图像 大小为900*750)
Calib_Board board = { Size(11,9),Size(180,150),15,15,3.5,7 };

void drawCross(Mat& pattern, Point2f center, Scalar color)
{
    if (pattern.channels() == 1)
    {
        cvtColor(pattern, pattern, COLOR_GRAY2RGB);
    }
    line(pattern, Point2f(center.x + 5, center.y), Point2f(center.x - 5, center.y), color);
    line(pattern, Point2f(center.x, center.y + 5), Point2f(center.x, center.y - 5), color);
}

void drawSport(Mat& pattern, Point2f center, Scalar color)
{
    if (pattern.channels() == 1)
    {
        cvtColor(pattern, pattern, COLOR_GRAY2RGB);
    }
    circle(pattern, center, 4, color, -1);
}

//选点的回调函数
void On_pickpoints(int event, int x0, int y0, int flags, void *v_params)
{
    string outlog;
    Params* params = (Params*)v_params;	//将图像转出来
    cv::Mat ori_img = params->p_ori_img;	//浅拷贝 注意 不要用标记污染了我们的图像
    cv::Mat show_img;

    int height_2 = (WINDOW_SIZE_HEIGHT - 1) / 2;
    int width_2 = (WINDOW_SIZE_WIDTH - 1) / 2;

    if (event == CV_EVENT_LBUTTONDOWN)	//左键按下
    {
        if (params->point.size() == 4)
            params->point.clear();

        //在这个周围圈出一个方形，这个方形的大小可以指定
        Rect roi_rect = Rect(
            (x0 - width_2) < 0 ? 0 : (x0 - width_2),
            (y0 - height_2) < 0 ? 0 : (y0 - height_2),
            (x0 + width_2) >= (ori_img.cols) ? (ori_img.cols - x0) * 2 : (width_2 * 2 + 1),
            (y0 + height_2) >= (ori_img.rows) ? (ori_img.rows - y0) * 2 : (height_2 * 2 + 1)
        );
        Mat roi_img = ori_img(roi_rect).clone();
        SimpleBlobDetector::Params d_params;
        d_params.minThreshold = 20;
        d_params.maxThreshold = 150;
        d_params.filterByArea = false;
        d_params.filterByColor = false;
        d_params.filterByInertia = false;
        d_params.filterByCircularity = false;
        d_params.filterByConvexity = true;
        d_params.minConvexity = 0.9;
        d_params.maxConvexity = 1;

        Ptr<FeatureDetector> blobsDetector = SimpleBlobDetector::create(d_params);
        vector<KeyPoint> centers;
        blobsDetector->detect(roi_img, centers);

#if _DEBUG
        //绘制圆斑的中心位置
        namedWindow("circle pattern", 0);
        drawKeypoints(roi_img, centers, roi_img);
        resizeWindow("circle pattern", roi_img.cols * 4, roi_img.rows * 4);
        imshow("circle pattern", roi_img);
#endif

        //如果检测到唯一的计算点，那么就拿来当我的标志点了
        if (centers.size() == 1)
        {
            //将这个点进行平移
            centers[0].pt.x += roi_rect.x;
            centers[0].pt.y += roi_rect.y;
            params->point.push_back(centers[0]);
        }
        drawKeypoints(ori_img, params->point, show_img, Scalar(0, 0, 200));
        imshow(params->this_window_name, show_img);

        if (params->point.size() == 4)
            cout << "If you want to pick them again, just chose the first point. Or press the enter." << endl;
    }
}


void Get_All_Files(const string& path, const string& format, vector<string>& files)
{
    files.clear();
    intptr_t  hFile = 0;//文件句柄  
    struct _finddata_t fileinfo;//文件信息 
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) //文件存在
    {
        do
        {
            files.push_back(fileinfo.name);//如果不是文件夹，储存文件名
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void Save_Points2File(const string& file_name, vector<Point2f>& points)
{
    //转成Matlab可以读取的形式
    ofstream outfile;
    outfile.open(file_name);
    if (!outfile)
    {
        return;
    }
    else
    {
        for (int i = 0; i < points.size(); i++)
        {
            outfile << points[i].x << " " << points[i].y << endl;
        }
    }
}

int main()
{
    string dir_path = "test_pic";
    vector<string> file_names;
    Get_All_Files(dir_path, ".png", file_names);
    /*一个pos的角点提取过程*/
    for (int file_idx = 0; file_idx < file_names.size(); file_idx++)
    {

        /*
        数据准备工作，这一段不需要重复调用运行
        */

        vector<KeyPoint> check_points;
        Mat img;
        string windows_name;
        Params params = { img,check_points,windows_name };
        vector<Point2f> calib_points_2d(4);
        calib_points_2d[0] = Point2f(1.0*board.dx, 1.0*board.dy);
        calib_points_2d[1] = Point2f(board.spots_size.width*board.dx, 1.0*board.dy);
        calib_points_2d[2] = Point2f(board.spots_size.width*board.dx, board.spots_size.height*board.dy);
        calib_points_2d[3] = Point2f(1.0*board.dx, board.spots_size.height*board.dy);
        vector<Point2f> img_points_2d(4);
        vector<Point2f> calib_points_2d_f(4);
        vector<Point2f> circle_centers_p;
        vector<Point2f> circle_centers;
        vector<Point2f> old_circle_centers;

        /*
        首先 提取四个边角上的点 这个坐标不用过于精准，只需要能够获得就行，当然，可以做到更加的精准，这个准确度越高，效果越好
        */

        g_rough_center_cnt = 0;
        //读取图像，灰度化
        string file_name = dir_path + "/" + file_names[file_idx];
        Mat calib_img = imread(file_name, 0);

        if (calib_img.empty())
        {
            cout << "Error: Image loading failed." << endl;
            return -1;
        }
        else
        {
            cout << "Loaded the picture " + file_name + "." << endl;
        }
        Mat show_img = calib_img.clone();
        //显示图像，并创建鼠标点击的方式（回调函数）
        cout << "Please chose the four corner points on the border." << endl;

        params.point.clear();
        params.p_ori_img = calib_img.clone();
        params.this_window_name = file_name;

        namedWindow(file_name, 0);
        setMouseCallback(file_name, On_pickpoints, (void*)&params);
        resizeWindow(file_name, calib_img.cols / 2, calib_img.rows / 2);
        imshow(file_name, show_img);
        waitKey(0);		//选择完成后按回车结束

                        /*
                        矫正透视投影畸变
                        */

        cout << "Warp the calibration board." << endl;
        img_points_2d[0] = params.point[0].pt;
        img_points_2d[1] = params.point[1].pt;
        img_points_2d[2] = params.point[2].pt;
        img_points_2d[3] = params.point[3].pt;
        int factor = min(calib_img.cols / board.mm_size.width, calib_img.rows / board.mm_size.height);
        calib_points_2d[0] = Point2f(calib_points_2d[0].x*factor, calib_points_2d[0].y*factor);
        calib_points_2d[1] = Point2f(calib_points_2d[1].x*factor, calib_points_2d[1].y*factor);
        calib_points_2d[2] = Point2f(calib_points_2d[2].x*factor, calib_points_2d[2].y*factor);
        calib_points_2d[3] = Point2f(calib_points_2d[3].x*factor, calib_points_2d[3].y*factor);

        Mat rough_H = findHomography(calib_points_2d, img_points_2d);
        Mat warp_calib_img;

        warpPerspective(calib_img, warp_calib_img, rough_H, Size(board.mm_size.width*factor, board.mm_size.height*factor), cv::WARP_INVERSE_MAP | cv::INTER_CUBIC);

        /*
        提取圆点，采用openCV提供的函数,找到圆点的中心,并显示
        */

        GaussianBlur(warp_calib_img, warp_calib_img, Size(0, 0), board.ds*factor / 8);
        circle_centers_p.clear();
        circle_centers.clear();
        bool pattern_found_flag = findCirclesGrid(255 - warp_calib_img, board.spots_size, circle_centers_p, CALIB_CB_SYMMETRIC_GRID);	//注意，OpenCV的只能识别白底黑点，我们是黑底白点，可以对照进行修改
        if (pattern_found_flag)
        {
            cout << "Warp pattern found." << endl;
            /*
            这里可以针对提取出的点做一定的精化处理，如对每一个角点，采用steger方法获得更加准确的点的坐标（对OpenCV的simpleBlob实在不放心）
            或者再进行一次透视投影变换，将图像变换成更好的角度再去提点。
            */
        }
#if _DEBUG
        drawChessboardCorners(warp_calib_img, board.spots_size, circle_centers_p, pattern_found_flag);
        namedWindow("rough perspective calib board", 0);
        resizeWindow("rough perspective calib board", Size(board.mm_size.width * 3, board.mm_size.height * 3));
        imshow("rough perspective calib board", warp_calib_img);
        waitKey(0);
#endif
        /*
        再次利用H矩阵，将之前的坐标反算到图像中，并显示其在图像上的位置以检验正确性 并和一般的提取方法进行对比
        */

        for (int i = 0; i < circle_centers_p.size(); i++)
        {
            Mat p_point = (Mat_<double>(3, 1) << (double)circle_centers_p[i].x, (double)circle_centers_p[i].y, 1);
            Mat point = rough_H*p_point;
            circle_centers.push_back(Point2f(float(point.ptr<double>(0)[0] / point.ptr<double>(2)[0]), float(point.ptr<double>(1)[0] / point.ptr<double>(2)[0])));
            //绘制在图像上
            drawSport(show_img, Point2f(float(point.ptr<double>(0)[0] / point.ptr<double>(2)[0]), float(point.ptr<double>(1)[0] / point.ptr<double>(2)[0])), Scalar(200, 0, 0));
        }

        //原始方法获得点的位置
        old_circle_centers.clear();
        bool old_found = findCirclesGrid(255 - calib_img, board.spots_size, old_circle_centers, CALIB_CB_SYMMETRIC_GRID);
        if (old_found)
        {
            cout << "Original pic found." << endl;
            for (int i = 0; i < old_circle_centers.size(); i++)
            {
                drawSport(show_img, old_circle_centers[i], Scalar(0, 0, 200));
            }
        }
        imshow(file_name, show_img);
        waitKey(0);
        destroyWindow(file_name);

        /*
        可以将提取的点进行保存，输入Matlab进行处理，也可以将其直接用OpenCV进行处理。 但是OepnCV不会输出不确定度等一些信息
        */

        int length_str = file_names[file_idx].length();
        string txt_name = file_names[file_idx];
        txt_name.erase(length_str - 4, 4);
        string old_txt_path = dir_path + "/old_" + txt_name + ".txt";
        string new_txt_path = dir_path + "/" + txt_name + ".txt";
        Save_Points2File(old_txt_path, old_circle_centers);
        Save_Points2File(new_txt_path, circle_centers);
    }
}
