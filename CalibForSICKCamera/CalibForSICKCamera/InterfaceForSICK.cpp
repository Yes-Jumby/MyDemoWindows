#include "InterfaceForSICK.h"
cv::Mat convertTo3Channels(const cv::Mat& binImg)
{
    cv::Mat three_channel = cv::Mat::zeros(binImg.rows, binImg.cols, CV_8UC3);
    vector<cv::Mat> channels;
    for (int i = 0; i<3; i++)
    {
        channels.push_back(binImg);
    }
    cv::merge(channels, three_channel);
    return three_channel;
}
void DrawRectIn3Channels(const cv::Mat& binImg, vector<cv::Point2f> pts_minAreaRect_2_)
{
    line(binImg,
        cv::Point2i(pts_minAreaRect_2_.at(0).x, pts_minAreaRect_2_.at(0).y),
        cv::Point2i(pts_minAreaRect_2_.at(1).x, pts_minAreaRect_2_.at(1).y),
        cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    line(binImg,
        cv::Point2i(pts_minAreaRect_2_.at(0).x, pts_minAreaRect_2_.at(0).y),
        cv::Point2i(pts_minAreaRect_2_.at(3).x, pts_minAreaRect_2_.at(3).y),
        cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    line(binImg,
        cv::Point2i(pts_minAreaRect_2_.at(2).x, pts_minAreaRect_2_.at(2).y),
        cv::Point2i(pts_minAreaRect_2_.at(3).x, pts_minAreaRect_2_.at(3).y),
        cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    line(binImg,
        cv::Point2i(pts_minAreaRect_2_.at(2).x, pts_minAreaRect_2_.at(2).y),
        cv::Point2i(pts_minAreaRect_2_.at(1).x, pts_minAreaRect_2_.at(1).y),
        cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
}
cv::Point2f FindLineInsect(const cv::Vec4f &line1_para, const cv::Vec4f &line2_para)
{
    cv::Point2f point0;
    point0.x = line1_para[2];
    point0.y = line1_para[3];
    float k1 = line1_para[1] / line1_para[0];
    float b1 = point0.y - k1*point0.x;

    point0.x = line2_para[2];
    point0.y = line2_para[3];
    float k2 = line2_para[1] / line2_para[0];
    float b2 = point0.y - k2*point0.x;

    point0.x = (b2 - b1) / (k1 - k2);
    point0.y = k1*point0.x + b1;
    return point0;
}

void DrawLineIn3Channels(const cv::Mat& binImg, const std::vector<cv::Point> &points, const cv::Scalar &color, cv::Vec4f &line_para, bool isdraw)
{
    cv::fitLine(points, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
    std::cout << "line_para = " << line_para << std::endl;
    //获取点斜式的点和斜率
    cv::Point point0;
    point0.x = line_para[2];
    point0.y = line_para[3];
    double k = line_para[1] / line_para[0];
    //计算直线的端点(y = k(x - x0) + y0)
    cv::Point point1, point2;
    point1.x = 0;
    point1.y = k * (0 - point0.x) + point0.y;
    point2.x = binImg.cols;
    point2.y = k * (binImg.cols - point0.x) + point0.y;
    if (isdraw)
    {
        cv::line(binImg, point1, point2, color, 2, 8, 0);
    }
}

void FindEdgePoints(const cv::Mat& binImg, const int & index_,const cv::Rect &rect, vector<vector<cv::Point2i>> &point_, float ratio)
{
    point_.clear();
    int temp_;
    //上 右 下 左 
    vector<cv::Point2i> point_up_;
    for (int cols = rect.x + ratio*rect.width; cols < rect.x + (1-ratio)*rect.width; cols++)
    {
        for (int rows = rect.y; rows < rect.y + rect.height; rows++)
        {
            temp_ = binImg.at<__int32>(rows, cols);
            if (temp_ == index_)
            {
                point_up_.push_back(cv::Point2i(cols, rows));
                break;
            }
        }
    }

    vector<cv::Point2i> point_down_;
    for (int cols = rect.x + ratio*rect.width; cols < rect.x + (1 - ratio)*rect.width; cols++)
    {
        for (int rows = rect.y + rect.height; rows > rect.y; rows--)
        {
            temp_ = binImg.at<__int32>(rows, cols);
            if (temp_ == index_)
            {
                point_down_.push_back(cv::Point2i(cols, rows));
                break;
            }
        }
    }

    vector<cv::Point2i> point_left_;
    for (int rows = rect.y + ratio*rect.height; rows < rect.y + (1 - ratio)*rect.height; rows++)
    {
        for (int cols = rect.x; cols < rect.x + rect.width; cols++)
        {
            temp_ = binImg.at<__int32>(rows, cols);
            if (temp_ == index_)
            {
                point_left_.push_back(cv::Point2i(cols, rows));
                break;
            }
        }
    }

    vector<cv::Point2i> point_right_;
    for (int rows = rect.y + ratio*rect.height; rows < rect.y + (1 - ratio)*rect.height; rows++)
    {
        for (int cols = rect.x + rect.width; cols > rect.x; cols--)
        {
            temp_ = binImg.at<__int32>(rows, cols);
            if (temp_ == index_)
            {
                point_right_.push_back(cv::Point2i(cols, rows));
                break;
            }
        }
    }
    point_.push_back(point_up_);
    point_.push_back(point_right_);
    point_.push_back(point_down_);
    point_.push_back(point_left_);
}
void FindFourPoints(const cv::Mat& disImg, const int & index_, const cv::Mat& binImg, const cv::Rect &rect_edge_, vector<cv::Point2f> &point_insect, float ratio,bool isdraw)
{
    //拟合直线
    cv::Scalar color_red_line_ = cv::Scalar(0, 0, 255);
    cv::Scalar color_green_line_ = cv::Scalar(0, 255, 0);
    cv::Scalar color_white_line_ = cv::Scalar(255, 255, 255);

    vector<vector<cv::Point2i>> EdgePoint_;
    FindEdgePoints(binImg, index_,rect_edge_, EdgePoint_, ratio);

    //Mat min_region_;
    //binImg.convertTo(min_region_, CV_8U);
    //threshold(min_region_, min_region_, 0, 255, THRESH_BINARY);
    //Mat disImg;
    //disImg = convertTo3Channels(min_region_);
    //标注边界点
    if (isdraw)
    {
        for (int ii = 0; ii < EdgePoint_.size(); ii++)
        {
            for (int i = 0; i < EdgePoint_.at(ii).size(); i++)
            {
                cv::circle(disImg, EdgePoint_.at(ii).at(i), 2, color_red_line_, 2, 8, 0);
            }
        }
    }

    //拟合直线  //上 右 下 左 
    vector<cv::Vec4f> lines_para;
    for (int ii = 0; ii < EdgePoint_.size(); ii++)
    {
        cv::Vec4f line1_para;
        DrawLineIn3Channels(disImg, EdgePoint_.at(ii), color_green_line_, line1_para, isdraw);
        lines_para.push_back(line1_para);
    }
    //右上 右下 左下 左上
    point_insect.push_back(FindLineInsect(lines_para[0], lines_para[1]));
    point_insect.push_back(FindLineInsect(lines_para[1], lines_para[2]));
    point_insect.push_back(FindLineInsect(lines_para[2], lines_para[3]));
    point_insect.push_back(FindLineInsect(lines_para[3], lines_para[0]));
    for (int ii = 0; ii < point_insect.size(); ii++)
    {
        cv::circle(disImg, point_insect[ii], 6, color_white_line_, 2, 8, 0);
    }
    cv::line(disImg, point_insect[0], point_insect[1], color_green_line_, 2, 8, 0);
    cv::line(disImg, point_insect[1], point_insect[2], color_green_line_, 2, 8, 0);
    cv::line(disImg, point_insect[2], point_insect[3], color_green_line_, 2, 8, 0);
    cv::line(disImg, point_insect[3], point_insect[0], color_green_line_, 2, 8, 0);
}

void TransHeight2DTo3D(const cv::Mat& Img32f, const vector<cv::Point2f> &Height2Dpoint_, float x_resolution, float x_min, int iteration_count,vector<cv::Point3f> &Height3Dpoint_)
{
    Height3Dpoint_.clear();
    float height = Img32f.rows;
    float temp_;
    int x, y;
    int iteration_count_;
    for (int i = 0; i < Height2Dpoint_.size(); i++)
    {
        iteration_count_ = iteration_count;
        x = Height2Dpoint_.at(i).x;
        y = Height2Dpoint_.at(i).y;
        if (i % 4 == 0)
        {
            while (Img32f.at<float>(y,x) == 0)
            {
                x--;
                y++;
            }
            while (iteration_count_ != 0)
            {
                iteration_count_--;
                x--;
                y++;
            }
        }
        if (i % 4 == 1)
        {
            while (Img32f.at<float>(y, x) == 0)
            {
                x--;
                y--;
            }
            while (iteration_count_ != 0)
            {
                iteration_count_--;
                x--;
                y--;
            }
        }
        if (i % 4 == 2)
        {
            while (Img32f.at<float>(y, x) == 0)
            {
                x++;
                y--;
            }
            while (iteration_count_ != 0)
            {
                iteration_count_--;
                x++;
                y--;
            }
        }
        if (i % 4 == 3)
        {
            while (Img32f.at<float>(y, x) == 0)
            {
                x++;
                y++;
            }
            while (iteration_count_ != 0)
            {
                iteration_count_--;
                x++;
                y++;
            }
        }
        Height3Dpoint_.push_back(cv::Point3f(x * x_resolution - x_min, height - y, Img32f.at<float>(y, x)));

    }
}

void findCorners3D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_3d_2d_)
{
    //vector<Point2f> pts_3d_2d_;//out_put
    //int gray_threod_ = 160;
    //int size_threod_ = 500;
    //Mat Range3D_FLIP_8_Mat_ = imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\Range3D_FLIP_8_Mat_.bmp", IMREAD_UNCHANGED);
    //Mat blur_mat_;
    //blur(Range3D_FLIP_8_Mat_, blur_mat_, Size(3, 3));
    //Mat medianMat_;
    //medianBlur(Range3D_FLIP_8_Mat_, medianMat_, 3);
    cv::Mat binaryMat_;
    cv::threshold(Range3D_FLIP_8_Mat_, binaryMat_, gray_threod_, 255, cv::THRESH_BINARY);


    //去除最小连通域
    //查找连通域
    cv::Mat labels, stats, centroids;
    int n_comps = cv::connectedComponentsWithStats(
        binaryMat_, //二值图像
        labels,     //和原图一样大的标记图
        stats, //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
        centroids //nccomps×2的矩阵 表示每个连通区域的质心
    );
    cout << "先前轮廓数：" << n_comps << endl;
    vector<int> region_size(n_comps);

    vector<int> region_index;

    for (int i = 0; i < n_comps; i++) {
        region_size.push_back(stats.at<int>(i, cv::CC_STAT_AREA));
        cout << "轮廓大小：" << stats.at<int>(i, cv::CC_STAT_AREA) << endl;
        if (stats.at<int>(i, cv::CC_STAT_AREA) < size_threod_)
        {
            region_index.push_back(i);
        }
    }

    cv::Mat min_region_;
    min_region_ = cv::Mat::zeros(Range3D_FLIP_8_Mat_.size(), CV_8U);
    __int32 temp_;
    for (int x = 0; x < Range3D_FLIP_8_Mat_.rows; x++)
    {
        for (int y = 0; y < Range3D_FLIP_8_Mat_.cols; y++)
        {
            temp_ = labels.at<__int32>(x, y);
            if (temp_ == 0 || std::count(region_index.begin(), region_index.end(), temp_) > 0)
            {
                continue;
            }
            min_region_.at<uchar>(x, y) = 255;
        }
    }

    n_comps = cv::connectedComponentsWithStats(
        min_region_, //二值图像
        labels,     //和原图一样大的标记图
        stats, //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
        centroids //nccomps×2的矩阵 表示每个连通区域的质心
    );
    cout << "先前轮廓数：" << n_comps << endl;



    cv::Mat min_region_c3_;
    min_region_c3_ = convertTo3Channels(min_region_);
    cv::Rect rect = cv::Rect(200, 100, 300, 300);
    cv::Scalar color = cv::Scalar(0, 0, 255);
    for (int i = 1; i < n_comps; i++) {
        rect.x = stats.at<int>(i, cv::CC_STAT_LEFT);
        rect.y = stats.at<int>(i, cv::CC_STAT_TOP);
        rect.width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        rect.height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
        rectangle(min_region_c3_, rect, color, 1, cv::LINE_8);
        putText(min_region_c3_, to_string(i), cv::Point(rect.x + rect.width, rect.y + rect.height),
            CV_FONT_HERSHEY_PLAIN, 0.8, color, 1, cv::LINE_8);
        pts_3d_2d_.push_back(cv::Point2f(rect.x + rect.width, rect.y));//右上
        pts_3d_2d_.push_back(cv::Point2f(rect.x + rect.width, rect.y + rect.height));//右下
        pts_3d_2d_.push_back(cv::Point2f(rect.x, rect.y + rect.height));//左下
        pts_3d_2d_.push_back(cv::Point2f(rect.x, rect.y));//左上
    }
    imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\findCorners3D.bmp", min_region_c3_);
    cout << "findCorners3D end" << endl;
}

void findCorners2D(const cv::Mat &Range3D_FLIP_8_Mat_, int gray_threod_, int size_threod_, vector<cv::Point2f> &pts_2d_, bool IsShow)
{
    //vector<Point2f> pts_2d_;//out_put
    //int gray_threod_ = 160;
    //int size_threod_ = 500;
    //Mat Range3D_FLIP_8_Mat_ = imread("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\Range3D_FLIP_8_Mat_.bmp", IMREAD_UNCHANGED);
    cv::Mat blur_mat_;
    cv::blur(Range3D_FLIP_8_Mat_, blur_mat_, cv::Size(3, 3));
    cv::Mat medianMat_;
    cv::medianBlur(blur_mat_, medianMat_, 3);
    cv::Mat binaryMat_;
    cv::threshold(medianMat_, binaryMat_, gray_threod_, 255, cv::THRESH_BINARY);


    //去除最小连通域
    //查找连通域
    cv::Mat labels, stats, centroids;
    int n_comps = cv::connectedComponentsWithStats(
        binaryMat_, //二值图像
        labels,     //和原图一样大的标记图
        stats, //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
        centroids //nccomps×2的矩阵 表示每个连通区域的质心
    );
    cout << "先前轮廓数：" << n_comps << endl;
    vector<int> region_size(n_comps);

    vector<int> region_index;

    for (int i = 0; i < n_comps; i++) {
        region_size.push_back(stats.at<int>(i, cv::CC_STAT_AREA));
        cout << "轮廓大小：" << stats.at<int>(i, cv::CC_STAT_AREA) << endl;
        if (stats.at<int>(i, cv::CC_STAT_AREA) < size_threod_)
        {
            region_index.push_back(i);
        }
    }

    cv::Mat min_region_;
    min_region_ = cv::Mat::zeros(Range3D_FLIP_8_Mat_.size(), CV_8U);
    __int32 temp_;
    for (int x = 0; x < Range3D_FLIP_8_Mat_.rows; x++)
    {
        for (int y = 0; y < Range3D_FLIP_8_Mat_.cols; y++)
        {
            temp_ = labels.at<__int32>(x, y);
            if (temp_ == 0 || std::count(region_index.begin(), region_index.end(), temp_) > 0)
            {
                continue;
            }
            min_region_.at<uchar>(x, y) = 255;
        }
    }
    //reduced regions
    n_comps = cv::connectedComponentsWithStats(
        min_region_, //二值图像
        labels,     //和原图一样大的标记图
        stats, //nccomps×5的矩阵 表示每个连通区域的外接矩形和面积（pixel）
        centroids //nccomps×2的矩阵 表示每个连通区域的质心
    );
    cout << "先前轮廓数：" << n_comps << endl;

    //拟合直线
    cv::Mat min_Edge_c3_;
    min_Edge_c3_ = convertTo3Channels(min_region_);
    cv::Rect rect_edge_;
    cv::Scalar color_red_line_ = cv::Scalar(0, 0, 255);
    cv::Scalar color_green_line_ = cv::Scalar(0, 255, 0);
    cv::Scalar color_white_line_ = cv::Scalar(255, 255, 255);
    for (int i = 1; i < 2; i++) {
        rect_edge_.x = stats.at<int>(i, cv::CC_STAT_LEFT);
        rect_edge_.y = stats.at<int>(i, cv::CC_STAT_TOP);
        rect_edge_.width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        rect_edge_.height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
    }
    vector<cv::Point2f> point_insect_1_;
    FindFourPoints(min_Edge_c3_, 1, labels, rect_edge_, pts_2d_, 0.25, IsShow);

    for (int i = 2; i < 3; i++) {
        rect_edge_.x = stats.at<int>(i, cv::CC_STAT_LEFT);
        rect_edge_.y = stats.at<int>(i, cv::CC_STAT_TOP);
        rect_edge_.width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        rect_edge_.height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
    }
    vector<cv::Point2f> point_insect_2_;
    FindFourPoints(min_Edge_c3_, 2, labels, rect_edge_, pts_2d_, 0.30, IsShow);

    for (int i = 3; i < 4; i++) {
        rect_edge_.x = stats.at<int>(i, cv::CC_STAT_LEFT);
        rect_edge_.y = stats.at<int>(i, cv::CC_STAT_TOP);
        rect_edge_.width = stats.at<int>(i, cv::CC_STAT_WIDTH);
        rect_edge_.height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
    }
    vector<cv::Point2f> point_insect_3_;
    FindFourPoints(min_Edge_c3_, 3, labels, rect_edge_, pts_2d_, 0.25, IsShow);
    imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\min_Edge_c3_.bmp", min_Edge_c3_);

    ////minAreaRect
    //cv::Mat min_AreaRect_c3_;
    //min_AreaRect_c3_ = convertTo3Channels(min_region_);
    //vector<cv::Point2f> minAreaRect_1_,minAreaRect_2_,minAreaRect_3_;
    //for (int x = 0; x < labels.rows; x++)
    //{
    //    for (int y = 0; y < labels.cols; y++)
    //    {
    //        temp_ = labels.at<__int32>(x, y);
    //        if (temp_ == 1)
    //        {
    //            minAreaRect_1_.push_back(cv::Point2f(y, x));
    //        }
    //        if (temp_ == 2)
    //        {
    //            minAreaRect_2_.push_back(cv::Point2f(y,x));
    //        }
    //        if (temp_ == 3)
    //        {
    //            minAreaRect_3_.push_back(cv::Point2f(y, x));
    //        }
    //    }
    //}
    ////find region
    //cv::RotatedRect  RotatedRect_;
    //RotatedRect_ = minAreaRect(minAreaRect_1_);
    //vector<cv::Point2f> pts_minAreaRect_1_(4);
    //RotatedRect_.points(pts_minAreaRect_1_.data());
    ////tilt rectangle
    //DrawRectIn3Channels(min_AreaRect_c3_, pts_minAreaRect_1_);

    //RotatedRect_ = minAreaRect(minAreaRect_2_);
    //vector<cv::Point2f> pts_minAreaRect_2_(4);
    //RotatedRect_.points(pts_minAreaRect_2_.data());
    ////tilt rectangle
    //DrawRectIn3Channels(min_AreaRect_c3_, pts_minAreaRect_2_);

    //RotatedRect_ = minAreaRect(minAreaRect_3_);
    //vector<cv::Point2f> pts_minAreaRect_3_(4);
    //RotatedRect_.points(pts_minAreaRect_3_.data());
    ////tilt rectangle
    //DrawRectIn3Channels(min_AreaRect_c3_, pts_minAreaRect_3_);

    //pts_2d_.push_back(pts_minAreaRect_1_.at(3)); 
    //pts_2d_.push_back(pts_minAreaRect_1_.at(0)); 
    //pts_2d_.push_back(pts_minAreaRect_1_.at(1)); 
    //pts_2d_.push_back(pts_minAreaRect_1_.at(2));

    //pts_2d_.push_back(pts_minAreaRect_2_.at(3));
    //pts_2d_.push_back(pts_minAreaRect_2_.at(0));
    //pts_2d_.push_back(pts_minAreaRect_2_.at(1));
    //pts_2d_.push_back(pts_minAreaRect_2_.at(2));
    //                                  
    //pts_2d_.push_back(pts_minAreaRect_3_.at(3));
    //pts_2d_.push_back(pts_minAreaRect_3_.at(0));
    //pts_2d_.push_back(pts_minAreaRect_3_.at(1));
    //pts_2d_.push_back(pts_minAreaRect_3_.at(2));
    ////Rect rect_ = RotatedRect_.boundingRect2f();
    ////rectangle(min_AreaRect_c3_, rect_, Scalar(0, 0, 255), 1, LINE_8);
    //imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\min_AreaRect_c3_.bmp", min_AreaRect_c3_);

    ////up - right rectangle
    //cv::Mat min_region_c3_;
    //min_region_c3_ = convertTo3Channels(min_region_);
    //cv::Rect rect = cv::Rect(200, 100, 300, 300);
    //cv::Scalar color = cv::Scalar(0, 0, 255);
    //for (int i = 1; i < n_comps; i++) {
    //    rect.x = stats.at<int>(i, cv::CC_STAT_LEFT);
    //    rect.y = stats.at<int>(i, cv::CC_STAT_TOP);
    //    rect.width = stats.at<int>(i, cv::CC_STAT_WIDTH);
    //    rect.height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
    //    rectangle(min_region_c3_, rect, color, 1, cv::LINE_8);
    //    putText(min_region_c3_, to_string(i), cv::Point(rect.x + rect.width, rect.y + rect.height),
    //        CV_FONT_HERSHEY_PLAIN, 0.8, color, 1, cv::LINE_8);
    //    pts_2d_.push_back(cv::Point2f(rect.x + rect.width, rect.y));
    //    pts_2d_.push_back(cv::Point2f(rect.x + rect.width, rect.y + rect.height));
    //    pts_2d_.push_back(cv::Point2f(rect.x, rect.y + rect.height));//左下-右下-右上-左上
    //    pts_2d_.push_back(cv::Point2f(rect.x, rect.y));
    //}
    //imwrite("E:\\experimental_Data\\CLOUD_CAMERA\\data_20201111\\BOARD_without_mirror\\findCorners2D.bmp", min_region_c3_);
    cout << "findCorners2D end" << endl;
}
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