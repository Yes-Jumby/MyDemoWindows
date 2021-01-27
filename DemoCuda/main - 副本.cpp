#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
int FindFirstDiffNum(const vector<int> &num, vector<int> &peakValley, unsigned startPos, int flag)
{
    if (flag > 0) //找下一个最右值波峰的位置  如： 1 2 3 4 4 4 3 2  最后一个波峰的位置为5，第三个4
    {
        for (unsigned i = startPos; i < num.size() - 1; i++)
        {
            if (num[i + 1] < num[i])
            {
                peakValley[i] = 1;
                //逆序寻找此局部极值的最左端
                for (unsigned j = i - 1; j > startPos; j--)  // 可改为只取两端
                {
                    if (num[j] == num[i])
                        peakValley[j] = 1;
                    else
                        break;
                }
                return i; //返回最后一个的位置
            }
            else
            {
                continue;
            }
        }
        return 0;
    }
    else  //找下一个最右值波谷的位置  如： 4 4 4 3 2 2 5 5  最后一个波谷的位置为5，第二个2
    {
        for (unsigned i = startPos; i < num.size() - 1; i++)
        {
            if (num[i + 1] > num[i])
            {
                peakValley[i] = -1;
                for (unsigned j = i - 1; j > startPos; j--)  // 可改为只取两端
                {
                    if (num[j] == num[i])
                        peakValley[j] = -1;
                    else
                        break;
                }
                return i;
            }
            else
            {
                continue;
            }
        }
        return 0;
    }
}

// 数据中可能的极值点
//		  num: the input array, only a row/col
// peakValley: the output array, only contents 0,1;  1---peaks, 0---valley
void findPeaks(const vector<int> &num, vector<int> &peakValley)
{
    unsigned count = 0;
    int dif = 0;
    int ret = 0;

    while (count < num.size() - 1)
    {
        dif = num[count + 1] - num[count];
        if (dif == 0)
        {
            count++;
            continue;
        }

        if (dif < 0)  //以减序开始
        {
            ret = FindFirstDiffNum(num, peakValley, count, -1);
            if (ret > 0)   //重新赋值新的起始位置
                count = ret;
            else    //否则就是这一行搜索到头了
                break;
        }
        else
        {
            ret = FindFirstDiffNum(num, peakValley, count, 1);
            if (ret > 0)
                count = ret;
            else
                break;
        }
    }
}

/**
* \brief 设置输入图像
* \param[in]    vecImage 待计算MASK的图像
* \param[out]    matMask 得到的mask
* \param[in]    thod 阈值
*/
bool ComputeMaskByCodeImages(const std::vector<cv::Mat> &vecImage, cv::Mat &matMask, int thod)
{
    int iWidth = vecImage.at(0).cols;
    int iHeight = vecImage.at(0).rows;
    cv::Mat bal = vecImage.at(1);
    matMask = cv::Mat::ones(cv::Size(iWidth, iHeight), CV_8U);
    for (int i = 2; i < 24; i++)
    {
        if (i % 2 != 0)
        {
            continue;
        }
        cv::Mat Temp = cv::Mat::ones(cv::Size(iWidth, iHeight), CV_8S);
        cv::Mat Temp1;
        cv::Mat Temp2;
        vecImage.at(i + 1).convertTo(Temp1, CV_8S);
        vecImage.at(i).convertTo(Temp2, CV_8S);
        Temp = Temp1 - Temp2;


        cv::convertScaleAbs(Temp, Temp);
        for (int row = 0; row < iHeight; row++)
        {
            const uchar* current = Temp.ptr<uchar>(row);
            uchar* output = Temp.ptr<uchar>(row);
            for (int col = 0; col < iWidth; col++)
            {
                if (current[col] > thod)
                {
                    output[col] = 1;
                }
                else
                {
                    output[col] = 0;
                }
            }

        }
        matMask = matMask & Temp;
    }
    matMask = matMask * 230;
    return true;
}
/**
* \brief 设置输入图像
* \param[in]    vecImage 待计算MASK的22张图像
* \param[in]    cam_two_images 相机2拍摄的图像
*/
bool ComputeMask(const std::vector<cv::Mat> &vecImage, cv::Mat &matMask,int thod)
{
    int iCount = vecImage.size();
    int iWidth = vecImage.at(0).cols;
    int iHeight = vecImage.at(0).rows;
    //if (iCount != 22)
    //{
    //    return false;
    //}
    matMask = Mat::ones(Size(iWidth, iHeight), CV_8U);
    
    //Mat Temp = Mat::ones(Size(iWidth, iHeight), CV_32F);
    uchar a=0;
    for (int i = 0; i < iCount; i++)
    {
        if(i%2!=0)
        {
            continue;
        }
        Mat Temp = Mat::ones(Size(iWidth, iHeight), CV_8S);
        //cvAbsDiff(vecImage.at(i), vecImage.at(i+1), Temp); 
        Temp = vecImage.at(i) - vecImage.at(i+1);
        convertScaleAbs(Temp, Temp);
        //itbegin = Temp.begin<float>();
        //itend = Temp.end<float>();
        for (int row = 0; row < iHeight; row++)
        {
            const uchar* current = Temp.ptr<uchar>(row);
            uchar* output = Temp.ptr<uchar>(row);
            for (int col = 0; col < iWidth; col++)
            {
                a = current[col];
                if (current[col] > thod)
                {
                    output[col] = 1;
                }
                else
                {
                    output[col] = 0;
                }
            }
            
        }
        matMask = matMask & Temp;
    }
    return true;
}
int main(int argc, char* argv[])
{
	bilateralFilter()
    //Mat Temp1 = Mat::ones(Size(12, 12), CV_8S);
    ////cvAbsDiff(vecImage.at(i), vecImage.at(i+1), Temp); 
    //Mat Temp;
    //Temp1.convertTo(Temp,CV_8U);
    //Mat convert_decode_image_test = (Mat_<int>(3, 4) << 0, 1, 0, 0, 1, -5, 11,0, 0, 1, 0, 0);
    //Mat convert_decode_image_test1 = (Mat_<int>(3, 4) << 0, 2, 0, 0, 1, -5, 5, 0, 0, 1, 0, 0);
    //std::vector<cv::Mat> vecImage;
    //std::vector<cv::Mat> vecImage1;
    //vecImage.push_back(convert_decode_image_test);
    //vecImage.push_back(convert_decode_image_test1);
    //vecImage1.push_back(convert_decode_image_test);
    //vecImage1.push_back(convert_decode_image_test1);
    //Mat result;
    //ComputeMask(vecImage, vecImage1.at(0),1);
    //result = vecImage1.at(0);
    //result = vecImage1.at(1);
    //convertScaleAbs(convert_decode_image_test, convert_decode_image_test);

    Mat matMask = Mat::ones(cv::Size(5, 5), CV_8S);
    Mat matMask1 = Mat::ones(cv::Size(5, 5), CV_8S);
    matMask = matMask * 5;
    //matMask = matMask1 - matMask;
    Mat matMask2 = Mat::ones(cv::Size(5, 5), CV_8U);
    matMask2 = matMask1 - matMask;
    matMask2.convertTo(matMask2,CV_8U);
    int thod = -5;
    for (int row = 0; row < 5; row++)
    {
        const char* current = matMask.ptr<char>(row);
        char* output = matMask.ptr<char>(row);
        for (int col = 0; col < 5; col++)
        {
            char a = current[col];
            if (current[col] > thod)
            {
                output[col] = 1;
            }
            else
            {
                output[col] = 0;
            }
        }

    }
    uchar app = -1;
    return 0;
}

//int main(int argc, char* argv[])
//{
//    int arr[] = { 145, 168, 255, 255, 255, 234, 168, 11, 11, 15};
//    vector<int> data;
//    vector<int> peakValley(10,0);
//
//    for (int i = 0; i< sizeof(arr) / sizeof(int); i++)
//    {
//        data.push_back(arr[i]);
//    }
//
//    findPeaks(data, peakValley);
//
//    for (unsigned j = 0; j < peakValley.size(); j++)
//    {
//        cout << peakValley[j] << " ";
//    }
//    cout << endl;
//
//    return 0;
//}
//
//int main(int argc, char** argv) {
//    Mat dst;
//    Mat src(1, 30, CV_8UC1, cv::Scalar(1));;
//    src = src + 2;
//    std::vector<cv::Mat> images_;
//    vector<int> data;
//    vector<int> peakValley(src.cols, 0);
//    int temp;
//    int matSize = 10;
//    Mat Mattemp;
//    for (int i = 0; i < matSize; i++)
//    {
//        images_.push_back(src);
//    }
//    vector<int> peakValley(10, 0);
//
//
//    for (int i = 0; i < matSize; i++)
//    {
//        src = images_.at(i);
//        int cols = src.cols;
//        int rows = src.rows;
//        //曲线趋势化
//        for (int row = 0; row < rows; row++)
//        {
//            const uchar* current = src.ptr<uchar>(row);
//            data.push_back(current[0]);
//            for (int col = 1; col < cols; col++)
//            {
//                data.push_back(current[col]);
//                temp = 4 * current[col - 1] + current[col];
//                src.at<uchar>(row, col) = saturate_cast<uchar>((4 * current[col - 1] + current[col]));
//            }
//        }
//        int a =1;
//    }
//
//    dst = images_.at(9);
//
//    return 0;
//}