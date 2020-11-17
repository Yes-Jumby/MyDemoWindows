#include "opencv.hpp"

#include <iostream>
#include <fstream> 
#include <io.h>  
#include <string>  
#include<vector>

using namespace cv;
using namespace std;

/*
@param File_Directory Ϊ�ļ���Ŀ¼
@param FileType Ϊ��Ҫ���ҵ��ļ�����
@param FilesName Ϊ����ļ���������
*/
void getFilesName(string &File_Directory, string &FileType, vector<string>&FilesName)
{
	string buffer = File_Directory + "\\*" + FileType;

	_finddata_t c_file;   // ����ļ����Ľṹ��

	long long hFile;//http://www.mamicode.com/info-detail-2204262.html
	hFile = _findfirst(buffer.c_str(), &c_file);   //�ҵ�һ���ļ���

	if (hFile == -1L)   // ����ļ���Ŀ¼�´�����Ҫ���ҵ��ļ�
		printf("No %s files in current directory!\n", FileType);
	else
	{
		string fullFilePath;
		do
		{
			fullFilePath.clear();

			//����
			fullFilePath = File_Directory + "\\" + c_file.name;

			FilesName.push_back(fullFilePath);

		} while (_findnext(hFile, &c_file) == 0);  //����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1  
		_findclose(hFile);
	}
}

void m_calibration(vector<string> &FilesName, string result,Size board_size, Size square_size, Mat &cameraMatrix, Mat &distCoeffs, vector<Mat> &rvecsMat, vector<Mat> &tvecsMat)
{
	//ofstream fout(result);                       // ����궨������ļ� 

    FileStorage fswrite(result, FileStorage::WRITE);

	cout << "��ʼ��ȡ�ǵ㡭����������" << endl;
	int image_count = 0;           // ͼ������ 
	Size image_size;                                                // ͼ��ĳߴ� 
    int imag_bad = 0;
	vector<Point2f> image_points;                                   // ����ÿ��ͼ���ϼ�⵽�Ľǵ�
	vector<vector<Point2f>> image_points_seq;                       // �����⵽�����нǵ�

	for (int i = 0; i < FilesName.size(); i++)
	{
		image_count++;

		// ���ڹ۲�������
		//cout << "image_count = " << image_count << endl;
		Mat imageInput = imread(FilesName[i]);
		if (image_count == 1)  //�����һ��ͼƬʱ��ȡͼ������Ϣ
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			cout << "image_size.width = " << image_size.width << endl;
			cout << "image_size.height = " << image_size.height << endl;
		}

		/* ��ȡ�ǵ� */
		bool ok = findChessboardCorners(imageInput, board_size, image_points, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
		if (0 == ok)
		{
            imag_bad++;
			cout << "��" << image_count << "����Ƭ��ȡ�ǵ�ʧ�ܣ���ɾ�������±궨��" << FilesName[i]<<imag_bad << endl; //�Ҳ����ǵ�
			/*imshow("ʧ����Ƭ", imageInput);
			waitKey(0);*/
		}
		else
		{
			Mat view_gray;
			//cout << "imageInput.channels()=" << imageInput.channels() << endl;
			cvtColor(imageInput, view_gray, CV_RGB2GRAY);

			/* �����ؾ�ȷ�� */
			//find4QuadCornerSubpix(view_gray, image_points, Size(5, 5)); //�Դ���ȡ�Ľǵ���о�ȷ��
			cv::cornerSubPix(view_gray, image_points, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 20, 0.01));


            //vector<Point2f> image_points_;
            //for (int i = 0; i < image_points.size(); i++)
            //{
            //    
            //    image_points_.push_back(image_points.at(i));
            //    drawChessboardCorners(view_gray, board_size, image_points_, true);

            //    imshow("Camera Calibration", view_gray);//��ʾͼƬ
            //    waitKey(10);//��ͣ0.1S    
            //}

			image_points_seq.push_back(image_points);  //���������ؽǵ�

													   /* ��ͼ������ʾ�ǵ�λ�� */
			drawChessboardCorners(view_gray, board_size, image_points, true);

			imshow("Camera Calibration", view_gray);//��ʾͼƬ
			waitKey(10);//��ͣ0.1S     
		}
	}
	cout << "�ǵ���ȡ��ɣ�����" << imag_bad<< endl;


	/*������ά��Ϣ*/
	vector<vector<Point3f>> object_points_seq;                     // ����궨���Ͻǵ����ά����
    image_count = image_count - imag_bad;
    vector<Point3f> object_points;
    for (int i = 0; i < board_size.height; i++)//[7 7]
    {
        for (int j = 0; j < board_size.width; j++)
        {
            Point3f realPoint;
            /* ����궨�������������ϵ��z=0��ƽ���� */
            realPoint.x = i*square_size.width;
            realPoint.y = j*square_size.height;//square_size ʵ�ʲ����õ��ı궨����ÿ�����̸������ߴ磬��λmm
            realPoint.z = 0;
            object_points.push_back(realPoint);
        }
    }
	for (int t = 0; t < image_count; t++)
	{
		object_points_seq.push_back(object_points);
	}
    cout << "object_points������" << endl;
	/* ���б궨���� */
	double err_first = calibrateCamera(object_points_seq, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, CV_CALIB_FIX_K3);
    fswrite << "err_first" << err_first;
	cout << "�궨��ɣ�����" << endl;

    cout << "��ʼ���涨����������������" << endl;
    fswrite << "cameraMatrix"<<cameraMatrix;
    fswrite << "distCoeffs"<<distCoeffs;
	//����궨���    
    cout << "��ͶӰ���1��" << err_first << "����" << endl << endl;
    cout << "����ڲ�������" << endl;
    cout << cameraMatrix << endl << endl;
    cout << "����ϵ����\n";
    cout << distCoeffs << endl << endl << endl;


    cout << "��ʼ���۱궨���������������" << endl;
    double total_err = 0.0;            // ����ͼ���ƽ�������ܺ� 
    double err = 0.0;                  // ÿ��ͼ���ƽ�����
    double totalErr = 0.0;
    double totalPoints = 0.0;
    vector<Point2f> image_points_pro;     // �������¼���õ���ͶӰ��

    for (int i = 0; i < image_count; i++)
    {

        projectPoints(object_points_seq[i], rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points_pro);   //ͨ���õ������������������Խǵ�Ŀռ���ά�����������ͶӰ����

        err = norm(Mat(image_points_seq[i]), Mat(image_points_pro), NORM_L2);

        totalErr += err*err;
        totalPoints += object_points_seq[i].size();

        err /= object_points_seq[i].size();
       /* fout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;*/
        cout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
        total_err += err;
    }
    //fout << "��ͶӰ���2��" << sqrt(totalErr / totalPoints) << "����" << endl << endl;
    //fout << "��ͶӰ���3��" << total_err / image_count << "����" << endl << endl;
    cout << "��ͶӰ���2��" << sqrt(totalErr / totalPoints) << "����" << endl << endl;
    cout << "��ͶӰ���3��" << total_err / image_count << "����" << endl << endl;

    Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
	for (int i = 0; i < image_count; i++)
	{
        cout << "��" << i + 1 << "��ͼ�����ת������" << endl;
        cout << rvecsMat[i]*180/3.1415926 << endl;
        cout << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
        cout << tvecsMat[i] << endl << endl;

		/* ����ת����ת��Ϊ���Ӧ����ת���� */
		Rodrigues(rvecsMat[i], rotation_matrix);
        cout << "��" << i + 1 << "��ͼ�����ת����" << endl;
        cout << rotation_matrix << endl;
        
	}
	cout << "��������ɱ��棡����" << endl;
	//fout << endl;
 //   fout.close();
    fswrite.release();
}

void m_undistort(vector<string> &FilesName, Size image_size, Mat &cameraMatrix, Mat &distCoeffs)
{

	Mat mapx = Mat(image_size, CV_32FC1);   //X ������ӳ�����
	Mat mapy = Mat(image_size, CV_32FC1);   //Y ������ӳ�����
	Mat R = Mat::eye(3, 3, CV_32F);
	cout << "�������ͼ��" << endl;
	string imageFileName;                  //У����ͼ��ı���·��
	stringstream StrStm;
	string temp;

	for (int i = 0; i < FilesName.size(); i++)
	{
		Mat imageSource = imread(FilesName[i]);

		Mat newimage = imageSource.clone();

		//����һ��ʹ��initUndistortRectifyMap��remap�����������ʵ��
		//initUndistortRectifyMap(cameraMatrix,distCoeffs,R, Mat(),image_size,CV_32FC1,mapx,mapy);
		//  remap(imageSource,newimage,mapx, mapy, INTER_LINEAR);

		//������������Ҫת������ķ�ʽ��ʹ��undistort����ʵ��
		undistort(imageSource, newimage, cameraMatrix, distCoeffs);

		StrStm << i + 1;
		StrStm >> temp;
		imageFileName = "������ͼ��//" + temp + "_d.jpg";
		imwrite(imageFileName, newimage);

		StrStm.clear();
		imageFileName.clear();
	}
	std::cout << "�������" << endl;
}

void main111111()
{
	string File_Directory1 = "C:\\imagesave\\201109\\2";   //�ļ���Ŀ¼1

	string FileType = ".png";    // ��Ҫ���ҵ��ļ�����

	vector<string>FilesName1;    //����ļ���������

	getFilesName(File_Directory1, FileType, FilesName1);   // �궨����ͼ���ļ���·��


	Size board_size = Size(11, 8);                 //        // �궨����ÿ�С��еĽǵ��� 
	Size square_size = Size(5, 5);          //65 65             // ʵ�ʲ����õ��ı궨����ÿ�����̸������ߴ磬��λmm

	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));        // ������ڲ�������
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));          // �������5������ϵ����k1,k2,p1,p2,k3
	vector<Mat> rvecsMat;                                          // �������ͼ�����ת������ÿһ��ͼ�����ת����Ϊһ��mat
	vector<Mat> tvecsMat;                                          // �������ͼ���ƽ��������ÿһ��ͼ���ƽ������Ϊһ��mat

	m_calibration(FilesName1, "caliberation_result_201110.xml",board_size, square_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat);

	//m_undistort(FilesName1, image_size, cameraMatrix, distCoeffs);

	return;
}