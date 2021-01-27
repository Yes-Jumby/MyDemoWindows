#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <afx.h>
using namespace std;
using namespace cv;
int main()
{
	Mat rgb = imread("C:\\Users\\bz\\Desktop\\œ‡“∆¬Î\\1.jpg");
	Mat gray = imread("C:\\Users\\bz\\Desktop\\œ‡“∆¬Î\\1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat rgb1 = imread("C:\\Users\\bz\\Desktop\\œ‡“∆¬Î\\2.jpg");
	Mat gray1 = imread("C:\\Users\\bz\\Desktop\\œ‡“∆¬Î\\2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	return 0;
	CString FilePath;
	CString FileFullName;
	string FilePathName;
	Mat Image;
	CFileFind FF;
	FilePath = "D:/Stereo3D/data/test1209/BINOCULAR/0226/gray/left";
	FilePath += "/*.bmp";
	bool ret = FF.FindFile(FilePath);
	while (ret)
	{
		ret = FF.FindNextFile();
		if (!FF.IsDirectory() && !FF.IsDots())
		{
			FileFullName = FF.GetFilePath();
			//FilePathName = FileFullName.GetBuffer();
			FilePathName=(CStringA)FileFullName;
			cout << FilePathName << endl;
			//Image = imread(FilePathName, CV_LOAD_IMAGE_GRAYSCALE);
		}
	}
	FF.Close();
	//

	return 0;
}
