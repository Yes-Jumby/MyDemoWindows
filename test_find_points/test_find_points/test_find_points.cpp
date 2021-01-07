
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
��ȡԲ��б�Բ�����ģ�Ϊ��ʵ�ֽϺõı궨�ַ�����Ҫ������ǵ�����׼ȷ��
Բ����͸��ͶӰ�任֮�󣬲�����һ��Բ�Σ�������Բ�Ρ�
һ��ķ������ڻ�ȡ��Բ�����ģ�������Բ�����Ĳ���Բ�����ġ�
����������Ҫ����ȡ�ĸ���Զ�˵�����������꣬���H���󣬲�����͸�ӻ��������
֮����Խ���ͼ������OpenCV�ĺ������Բ��б������������ġ�
����ᵽ�ĵ��ؽ���ͼ��ƽ�棨��͸��ͶӰ�任, �������ǻ�õ�Բ�Ĳ���������Բ�ġ�
ע��
1��	Halcon�ı궨�壬����һ���������Ϊ��������һ������������������͸��ͶӰ����λ�û��䡣(ʵ���ϣ���������һϵ�����̸񹹳ɵ�Ҳ�У���
����������£����ǿ�����ʶ�����Ȼ����Ȼ����������˼�룬�������������ꡣ�ݴ�����Ҳ��Halcon�ı궨�����õķ��������ڱ�������ȡ������һ��ʼ������׼ȷ�ģ���������������
����Ԥ�ƣ�����������������ķ������ȵ�һЩ���������ǿ��Բ��õ�����˼�룬�ڱ任������h������ٽ���֮ǰ�Ĳ�������ø���ϸ����H����Ч���ϲ��ߣ�����Ч��Ӧ�ÿ��������൱
2�� OpenCVѰ��Բ��궨��ĺ��� ���õ���featuredectorѰ�ҵ�����ģ���Ҫ������ֵ��������������һ���Ĺ����ֶΣ��������ǵİб��Ϸ���Ĺ���ȳ̶Ȳ�һ���������ǵ����Ҳ��һ��������
���˽������Ȳ���һ����С�ĸ�˹�˲��Խ�����͸��ͶӰ�����ͼ�������˲�����ʹ�Ҷ�ֵ����ȣ�ͬʱҲ��̫Ӱ�����ǵ�������ȡ�����Բ������ȡ��˼�룬����Ҳ������steger������ø���
��׼��Բ�ģ��Ӷ���߱궨�ľ���
3��	���������Ʒ���һЩ�漰��ͶӰ�Ǻ�����ı궨�����У�������Ҫ�ܹ�֪��������ľ����������Ϣ�����ʱ����ýǵ�б꣨�����ѣ��ķ����Ͳ������ˣ��������Բ��б꣬�Ӷ��ܹ����Բ
�ĵ���λ��Ϣ������������ϵͳ�ľ��ȡ�
*/

//openCV ��׼ͷ�ļ�
#include <opencv2\core.hpp>
#include <opencv2\features2d.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\calib3d.hpp>

//c++ ��׼ͷ�ļ�
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <direct.h>
#include <io.h>

//�� ���ܲ���һ����ϰ�ߣ������һ������ˣ�����&������̣�
using namespace std;
using namespace cv;

//һЩȫ�ֱ���
const int WINDOW_SIZE_HEIGHT = 61;
const int WINDOW_SIZE_WIDTH = 61;
int g_rough_center_cnt = 0;

//���ڲ����ص�
struct Params
{
    Mat p_ori_img;
    vector<KeyPoint> point;
    string this_window_name;
};

//�б�ľ���ߴ���Ϣ��ע�ⵥλȫ��Ϊmm
struct Calib_Board
{
    Size spots_size;	//�б��ϵ�ĳߴ�
    Size mm_size;		//���׳ߴ�
    float dx;			//�������
    float dy;			//�������
    float ds;			//С��ֱ��
    float dl;			//���ֱ��
};

//ע ����ʹ�õİб���11*9�İб꣬���15mm����Բֱ��7mm СԲֱ��3.5mm ����μ� GR180-11*9�б� ���γߴ�Ϊ180*150mm��ע�⣬�������Ҳ�����ؽ����ǵ�ͼ�� ��СΪ900*750)
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

//ѡ��Ļص�����
void On_pickpoints(int event, int x0, int y0, int flags, void *v_params)
{
    string outlog;
    Params* params = (Params*)v_params;	//��ͼ��ת����
    cv::Mat ori_img = params->p_ori_img;	//ǳ���� ע�� ��Ҫ�ñ����Ⱦ�����ǵ�ͼ��
    cv::Mat show_img;

    int height_2 = (WINDOW_SIZE_HEIGHT - 1) / 2;
    int width_2 = (WINDOW_SIZE_WIDTH - 1) / 2;

    if (event == CV_EVENT_LBUTTONDOWN)	//�������
    {
        if (params->point.size() == 4)
            params->point.clear();

        //�������ΧȦ��һ�����Σ�������εĴ�С����ָ��
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
        //����Բ�ߵ�����λ��
        namedWindow("circle pattern", 0);
        drawKeypoints(roi_img, centers, roi_img);
        resizeWindow("circle pattern", roi_img.cols * 4, roi_img.rows * 4);
        imshow("circle pattern", roi_img);
#endif

        //�����⵽Ψһ�ļ���㣬��ô���������ҵı�־����
        if (centers.size() == 1)
        {
            //����������ƽ��
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
    intptr_t  hFile = 0;//�ļ����  
    struct _finddata_t fileinfo;//�ļ���Ϣ 
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) //�ļ�����
    {
        do
        {
            files.push_back(fileinfo.name);//��������ļ��У������ļ���
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void Save_Points2File(const string& file_name, vector<Point2f>& points)
{
    //ת��Matlab���Զ�ȡ����ʽ
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
    /*һ��pos�Ľǵ���ȡ����*/
    for (int file_idx = 0; file_idx < file_names.size(); file_idx++)
    {

        /*
        ����׼����������һ�β���Ҫ�ظ���������
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
        ���� ��ȡ�ĸ��߽��ϵĵ� ������겻�ù��ھ�׼��ֻ��Ҫ�ܹ���þ��У���Ȼ�������������ӵľ�׼�����׼ȷ��Խ�ߣ�Ч��Խ��
        */

        g_rough_center_cnt = 0;
        //��ȡͼ�񣬻ҶȻ�
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
        //��ʾͼ�񣬲�����������ķ�ʽ���ص�������
        cout << "Please chose the four corner points on the border." << endl;

        params.point.clear();
        params.p_ori_img = calib_img.clone();
        params.this_window_name = file_name;

        namedWindow(file_name, 0);
        setMouseCallback(file_name, On_pickpoints, (void*)&params);
        resizeWindow(file_name, calib_img.cols / 2, calib_img.rows / 2);
        imshow(file_name, show_img);
        waitKey(0);		//ѡ����ɺ󰴻س�����

                        /*
                        ����͸��ͶӰ����
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
        ��ȡԲ�㣬����openCV�ṩ�ĺ���,�ҵ�Բ�������,����ʾ
        */

        GaussianBlur(warp_calib_img, warp_calib_img, Size(0, 0), board.ds*factor / 8);
        circle_centers_p.clear();
        circle_centers.clear();
        bool pattern_found_flag = findCirclesGrid(255 - warp_calib_img, board.spots_size, circle_centers_p, CALIB_CB_SYMMETRIC_GRID);	//ע�⣬OpenCV��ֻ��ʶ��׵׺ڵ㣬�����Ǻڵװ׵㣬���Զ��ս����޸�
        if (pattern_found_flag)
        {
            cout << "Warp pattern found." << endl;
            /*
            ������������ȡ���ĵ���һ���ľ����������ÿһ���ǵ㣬����steger������ø���׼ȷ�ĵ�����꣨��OpenCV��simpleBlobʵ�ڲ����ģ�
            �����ٽ���һ��͸��ͶӰ�任����ͼ��任�ɸ��õĽǶ���ȥ��㡣
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
        �ٴ�����H���󣬽�֮ǰ�����귴�㵽ͼ���У�����ʾ����ͼ���ϵ�λ���Լ�����ȷ�� ����һ�����ȡ�������жԱ�
        */

        for (int i = 0; i < circle_centers_p.size(); i++)
        {
            Mat p_point = (Mat_<double>(3, 1) << (double)circle_centers_p[i].x, (double)circle_centers_p[i].y, 1);
            Mat point = rough_H*p_point;
            circle_centers.push_back(Point2f(float(point.ptr<double>(0)[0] / point.ptr<double>(2)[0]), float(point.ptr<double>(1)[0] / point.ptr<double>(2)[0])));
            //������ͼ����
            drawSport(show_img, Point2f(float(point.ptr<double>(0)[0] / point.ptr<double>(2)[0]), float(point.ptr<double>(1)[0] / point.ptr<double>(2)[0])), Scalar(200, 0, 0));
        }

        //ԭʼ������õ��λ��
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
        ���Խ���ȡ�ĵ���б��棬����Matlab���д���Ҳ���Խ���ֱ����OpenCV���д��� ����OepnCV���������ȷ���ȵ�һЩ��Ϣ
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
