
//src = imread("D:\\Stereo3D\\PictureTemp\\5.jpg");
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include < functional>  
#include "glm\glm.hpp"
using namespace std;
//using namespace cv;

#define TEXT(x) "class" #x
void CalculateEpipolarCUDA(
	unsigned int pixel_id,
	float *line,
	float *fundmental_matrix,
	int cam_x,
	int cam_y
)
{
	glm::mat3 lfundmental_matrix(1.0);
	memcpy(&lfundmental_matrix[0][0], fundmental_matrix, sizeof(float) * 9);
	glm::vec3 point(0.0f);
	glm::vec3 line_out(0.f);
	float point_input[3] = { float(pixel_id % cam_x), float(pixel_id / cam_x), 1.0f };
	memcpy(&point[0], point_input, sizeof(float) * 3);
	line_out = lfundmental_matrix*point;
	memcpy(line, &line_out[0], sizeof(float) * 3);
}
float GetMidPoint(
	float* origin0,
	float* dir0,
	float* origin1,
	float* dir1,
	float* mid_point
)
{
	glm::vec3 v1(0.0);
	glm::vec3 v2(0.0);
	glm::vec3 p1(0.0);
	glm::vec3 p2(0.0);
	memcpy(&v1[0], dir0, sizeof(float) * 3);
	memcpy(&v2[0], dir1, sizeof(float) * 3);
	memcpy(&p1[0], origin0, sizeof(float) * 3);
	memcpy(&p2[0], origin1, sizeof(float) * 3);
	glm::vec3 v12 = p1 - p2;
	float v1_dot_v1 = glm::dot(v1, v1);
	float v2_dot_v2 = glm::dot(v2, v2);
	float v1_dot_v2 = glm::dot(v1, v2);
	float v12_dot_v1 = glm::dot(v12, v1);
	float v12_dot_v2 = glm::dot(v12, v2);
	float denom = v1_dot_v1 * v2_dot_v2 - v1_dot_v2 * v1_dot_v2;
	float dist = -1.0;
	if (glm::abs(denom) < 0.05) // watch out!!
	{
		dist = -1.0;
		return dist;
	}
	float s = (v1_dot_v2 / denom) * v12_dot_v2 - (v2_dot_v2 / denom) * v12_dot_v1;
	float t = -(v1_dot_v2 / denom) * v12_dot_v1 + (v1_dot_v1 / denom) * v12_dot_v2;
	dist = glm::length(p1 + s*v1 - p2 - t*v2);
	auto mid_p = glm::vec3((p1 + s*v1 + p2 + t*v2) / 2.0f);
	memcpy(mid_point, &mid_p[0], sizeof(float) * 3);
	return dist;
}

void UndistortPixel(
	unsigned int idx,
	unsigned int res_x,
	unsigned int res_y,
	float *cam_mat,
	float *dist_mat,
	float *undistorted
)
{
	{
		unsigned int distorted_x = idx%res_x;
		unsigned int distorted_y = idx / res_x;

		float k[5] = { 0.0 };
		float fx = 0.0;
		float fy = 0.0;
		float ifx = 0.0;
		float ify = 0.0;
		float cx = 0.0;
		float cy = 0.0;
		int iters = 1;
		k[0] = dist_mat[0];
		k[1] = dist_mat[1];
		k[2] = dist_mat[2];
		k[3] = dist_mat[3];
		// k[4] = dist_mat[4];
		iters = 5;
		fx = cam_mat[0];
		fy = cam_mat[4];
		ifx = 1.0 / fx;
		ify = 1.0 / fy;
		cx = cam_mat[2];
		cy = cam_mat[5];
		float x = 0.0;
		float y = 0.0;
		float x0 = 0.0;
		float y0 = 0.0;
		x = distorted_x;
		y = distorted_y;
		x0 = (x - cx)*ifx;
		x = x0;
		y0 = (y - cy)*ify;
		y = y0;
		for (int jj = 0; jj < iters; ++jj)
		{
			float r2 = x*x + y*y;
			float icdist = 1. / (1 + ((k[4] * r2 + k[1])*r2 + k[0])*r2);
			float delta_x = 2 * k[2] * x*y + k[3] * (r2 + 2 * x*x);
			float delta_y = k[2] * (r2 + 2 * y*y) + 2 * k[3] * x*y;
			x = (x0 - delta_x)*icdist;
			y = (y0 - delta_y)*icdist;
		}
		undistorted[0] = (float)(x*fx) + cx;
		undistorted[1] = (float)(y*fy) + cy;
	}
}
void GetRay(
	float* undistorted,
	float* cam_mat,
	float* cam_trans_mat,
	float* origin,
	float* dir
)
{
	glm::mat4 lcam_trans_mat(1.0);
	memcpy(&lcam_trans_mat[0][0], cam_trans_mat, sizeof(float) * 16);
	auto lorigin = lcam_trans_mat*glm::vec4(0.0, 0.0, 0.0, 1.0);
	auto ldir = glm::vec4(
		(undistorted[0] - cam_mat[2]) / cam_mat[0],
		(undistorted[1] - cam_mat[5]) / cam_mat[4],
		1.0, 0.0
	);
	ldir = lcam_trans_mat*ldir;
	ldir = glm::normalize(ldir);
	memcpy(origin, &lorigin[0], sizeof(float) * 4);
	memcpy(dir, &ldir[0], sizeof(float) * 4);
}
bool intersectionLinePlane(float P[], float P1[], float P2[], float coeffi[])
{
	float P1P2[3] = { P2[0] - P1[0],P2[1] - P1[1],P2[2] - P1[2] };
	int i = 0;
	float num, den, n;
	num = coeffi[0] * P1[0] + coeffi[1] * P1[1] + coeffi[2] * P1[2] + coeffi[3];
	den = coeffi[0] * P1P2[0] + coeffi[1] * P1P2[1] + coeffi[2] * P1P2[2];
	if (fabs(den) < 1e-5)
	{
		//parallel
		return false;
	}
	n = num / den;
	for (i = 0; i < 3; i++)
		P[i] = P1[i] + n*P1P2[i];

	return true;
}

//int main()
//{
//	glm::mat4 mat = glm::mat4(
//		1, 0, 0, 0,
//		0, 1, 0, 0,
//		0, 0, 1, 0,
//		1, 1, 1, 1
//	);
//
//
//	glm::vec4 v(1, 2, 3, 1);
//
//	/***
//	* 矩阵与向量向乘规则，遵守opengl的谁在前谁是列向量的规则
//	* 矩阵在前则矩阵看成是四个列向量，向量在后则为一个行向量
//	* 向量在前则向量看成一个列向量，矩阵在后则视为四个行向量
//	*/
//	/***
//	* 【矩阵与向量相乘，一般的用法是矩阵在左向量在右】
//	* 如下运算是把mat看作四个列向量，V看作行向量：(1*1+0*2+0*3+1*1, 0*1+1*2+0*3+1*1, 0*1+0*2+1*3+1*1, 0*1+0*2+0*3+1*1) = (2,3,4,1)
//	*/
//	auto vt = v*mat; //结果是(2,3,4,1)
//
//	//std::function< int(int)> square = [](int i) -> int { return i * i; };
//	//int bbb = square(3);
//
//	//int min_val = 10;
//	//int max_val = 1000;
//	//vector< int> vec;
//	//vec.push_back(10);
//	//vec.push_back(2);
//	//vec.push_back(90);
//	//vec.push_back(10000);
//	//vector<int>::iterator iter = vec.begin();//注意需要用const_iterator,因为容器是const类型  
//	//while (iter != vec.end())
//	//{
//	//	cout << *iter++ << " ";
//	//}
//	//int result;
//	//if (iter == vec.end())
//	//{
//	//	result = *iter;
//	//}
//	//vector<int>::iterator t = std::find_if(vec.begin(), vec.end(), [=](int i) {
//	//	return i > min_val && i < max_val;
//	//});
//	//if (t != vec.end())
//	//{
//	//	result = *t;
//	//}
//	//
//	////float p[3];
//	////float p1[3] = {1,2,3};
//	////float p2[3] = {};
//	////float coeffi[4] = {0,0,1,0};
//	////intersectionLinePlane(p, p1, p2, coeffi);
//	//int a = 0;
//	//a = a + 1 << 1;
//	//glm::vec3 x1 = glm::vec3(0, 1, 0);
//	//glm::vec3 x2 = glm::vec3(1, 0, 0);
//
//	//glm::vec3 plane_eqs = glm::cross(x1, x2);//叉乘
//	////glm::vec3 planePoint = x2;
//
//	//glm::vec3 raypoint = glm::vec3(0, 0, 2);//起始点
//	//glm::vec3 raydir = glm::vec3(1, 0, 1);//方向
//
//	//float denominator = glm::dot(plane_eqs, (raydir));//分母-点乘
//	//float numerator = -glm::dot(plane_eqs, (raypoint));//分子-点乘
//
//	////float lambda = abs(numerator / denominator);
//	//float lambda = (numerator / denominator);
//	//glm::vec3 pt = lambda * raydir;
//	//pt = pt + /*(abs(denominator)/ denominator)**/raypoint;
//
//	//glm::mat4 lcam_trans_mat(1.0);
//	//auto lorigin = lcam_trans_mat*glm::vec4(9.0, 5.0, 3.0, 1.0);//相机坐标系转世界坐标系 原点
//
//	//float origin0[3] = {0,0,0};
//	//float dir0[3] = { 1,0,0 };
//	//float origin1[3] = { 0,0,100 };
//	//float dir1[3] = { 0,1,0 };
//	//float mid_point[3] = {-1,-1,-1};
//	//float dist = GetMidPoint(
//	//	origin0,
//	//	dir0,
//	//	origin1,
//	//	dir1,
//	//	mid_point
//	//);
//	return 0;
//}

class T5Base {
public:
    T5Base() :value(55) {}
    virtual ~T5Base() {}
    void test1() { cout << "T5Base test1..." << endl; }
protected:
    int value;
};

class T5Derived : private T5Base {
public:
    using T5Base::test1;
    using T5Base::value;
    void test2() { cout << "value is " << value << endl; }
};
struct my
{
    my()
    {
        p = new char[100000];
    }
    char *p;
    int a;
};
#define  STRINGIFY(x) #x 
#define  TOSTRING(x) STRINGIFY(x) 
#define  FUNCTION_INFO "\nFunction Name: " __FUNCTION__
#define  FUNCTION_INFO __FILE__ "\nPosition: " TOSTRING(__LINE__) "\nFunction Name: " __FUNCTION__

struct Cloud3D
{
	Cloud3D()
		:width(0), height(1), cloud_size(0), channel(4),
		expose(0), minx(0), miny(0), minz(0), dx(0), dy(0),
		timestamp(nullptr), timestamp_size(0), device_message(nullptr), device_message_size(0), data(nullptr)
	{
	}
	~Cloud3D() {}
	void Destroy()
	{
		if (data != nullptr)
		{
			delete[]data;
			data = nullptr;
		}
		if (timestamp != nullptr)
		{
			delete[]timestamp;
			timestamp = nullptr;
		}
		if (device_message != nullptr)
		{
			delete[]device_message;
			device_message = nullptr;
		}

	}


	int width;
	int height;
	int cloud_size;
	int channel;
	int expose;
	float minx;
	float miny;
	float minz;
	float maxx;
	float maxy;
	float maxz;
	float dx;
	float dy;
	char* timestamp;
	int timestamp_size;
	char* device_message;
	int device_message_size;
	//PointCloudType point_type;
	float* data; //x,y,z,gray,x,y,z,gray,x...
};

int add(int a, int b)
{
	return a + b;
}
//using namespace cv;
//int main()
//{
//	vector<int>vec;
//	vec.resize(10,999);
//cout << "Draw Chess OpenCV!" << endl;
//char* filename = "E:\\1.png";
//char* filename2 = "E:\\1.png";
//IplImage* imgRGB = cvLoadImage(filename);
//IplImage* imgGrey = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
//
//if (imgGrey == NULL) {//image validation
//	cout << "No valid image input." << endl;
//	char c = getchar();
//	return 1;
//}

////-------find chessboard corners--------------
//int corner_row = 7;//interior number of row corners.(this can be countered by fingers.)
//int corner_col = 7;//interior number of column corners.
//int corner_n = corner_row*corner_col;
//CvSize pattern_size = cvSize(corner_row, corner_col);
//// CvPoint2D32f* corners=new CvPoint2D32f[corner_n];
//CvPoint2D32f corners[49];
//int corner_count;
//
////vector<Point2f> pointBuf;
////Size size(4,2);
////bool found = false;
//Mat gray, rgb;
//gray = imread("E:\\1.png", IMREAD_GRAYSCALE);
//rgb = imread("E:\\0001.bmp");
////found = findCirclesGrid(gray, size, pointBuf);
//////found = findCirclesGrid( img1,boardSize, pointBuf,cv::CALIB_CB_SYMMETRIC_GRID,cv::SimpleBlobDetector::create());
////
////	cv::drawChessboardCorners(rgb, size, cv::Mat(pointBuf),found);
////
////
////imwrite("E:\\2.png", rgb);
//int found = cvFindChessboardCorners(//returning non-zero means sucess.
//	imgGrey,// 8-bit single channel greyscale image.
//	pattern_size,//how many INTERIOR corners in each row and column of the chessboard.
//	corners,//an array where the corner locations can be recorded.
//	&corner_count,// optional, if non-NULL, its a point to an integer where the nuber of corners found can be recorded.
//				  // CV_CALIB_CB_ADAPTIVE_THRESH|CV_CALIB_CB_FILTER_QUADS// check page 382-383.
//	0
//);
//cout << "corner_count = " << corner_count;
////-------Draw the corner pattern-------
//cvDrawChessboardCorners(
//	imgRGB,
//	pattern_size,
//	corners,
//	corner_count,
//	found
//);
//cvSaveImage("E:\\2.png", imgRGB);
////to summary a bit of findings.
//cout << "found=" << found << endl;
//cout << "x=" << corners[1].x;
//cout << ",y=" << corners[1].y << endl;
//
////cvNamedWindow("Find and Draw ChessBoard", 0);
////cvShowImage("Find and Draw ChessBoard", imgRGB);
//
//cvWaitKey(0);
////
////cvReleaseImage(&imgGrey);
////cvReleaseImage(&imgRGB);
//cvDestroyWindow("Find and Draw ChessBoard");
//
//return 0;
//}

#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <Eigen/Dense>
//int main()
//{
//
//	Eigen::Matrix4f transform(Eigen::Matrix4f::Identity()*9);
//	std::cout << "Matrix4f" << std::endl << transform << std::endl;
//	Eigen::Affine3f tra_aff(transform);
//	std::cout << "tra_aff.rotation()" << std::endl << tra_aff.rotation() << std::endl;
//	std::cout << "tra_aff.translation()" << std::endl << tra_aff.translation() << std::endl;
//
//	Eigen::Matrix<float, 3, 3>model_eigDx;
//	model_eigDx << 5, 0, 0, 0, 6, 0, 0, 0,999;
//	cout << "model_eigDx " << endl << model_eigDx << endl;
//	Eigen::Matrix<float, 3, 1> model_centroid_;
//	model_centroid_ << 1, 2, 3;
//	Eigen::Matrix<float, 4, 4> p2w_model(Eigen::Matrix<float, 4, 4>::Identity());//单位阵
//	//	Eigen::Matrix4f p2w_model(Eigen::Matrix4f::Identity());
//	p2w_model.block<3, 3>(0, 0) = model_eigDx.transpose();
//	cout << "p2w_model " << endl << p2w_model << endl;
//	p2w_model.block<3, 1>(0, 3) = -1.f*(p2w_model.block<3, 3>(0, 0)*model_centroid_);
//	cout << "p2w_model " << endl << p2w_model << endl;
//	return 0;
//	Eigen::Vector2f line_t(2, 2);
//	line_t.normalize();
//	double result = log(exp(10.0));
//	Eigen::Vector4f line_pt(2, 2, 0, 0);
//	Eigen::Vector4f line_dir(2,0,0,0);
//	//line_dir[0] = 9;
//	line_dir.normalize();
//	Eigen::Vector4f line_cross = (line_pt).cross3(line_dir);
//	double sss = line_cross.norm();
//	double sqr_distance = line_cross.squaredNorm();
//	double a = 2, b = 2;//以2为底的对数函数 
//	for (b = 2; b <= 16; b = b + 2)
//	{
//		cout << "b=" << b << "时，以2为底的对数函数=" << log(b) / log(a) << endl;
//	}
//	Eigen::Vector3f line1(0,2,0);
//	Eigen::Vector3f line2(2,0,0);
//	Eigen::Vector3f p2(0,0,2);
//	Eigen::Vector3f coefficients = line1.cross(line2);
//	// Normalize
//	coefficients.normalize();
//	double ss = -1 * (coefficients.template head<3>().dot(p2.matrix()));
//	Eigen::Array2d p0(4,2);
//	Eigen::Array2d p1(1, 4);
//	Eigen::Array2d dy1dy2 = p0 / p1;
//	bool aa = (dy1dy2[0] != dy1dy2[1]);
//	Eigen::Vector3f p1p0(1,0,0);
//	Eigen::Vector3f p2p0(0,1,0);
//	Eigen::Vector3f p00(0, 1, 1);
//	Eigen::Vector3f p1p2= p1p0.cross(p2p0);
//	Eigen::Vector3f p2p1 = p2p0.cross(p1p0);
//	double d = p1p2.dot(p00);
//
//	//Eigen::Matrix3d m1;
//	//m1 << 1, 0, 0, 0, 1, 0, 0, 0, 1;
//
//	//cout << "m1  " << m1 << endl;
//	//cout << "m1 transpose " << m1.transpose() << endl;
//	//cout << "m1 conjugate " << m1.conjugate() << endl;
//	//cout << "m1 adjoint " << m1.adjoint() << endl;
//	//Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver1(m1.transpose()*m1);
//	//cerr << "eigen value " << eigen_solver1.eigenvalues() << endl;
//	//cerr << "eigen vector " << eigen_solver1.eigenvectors() << endl;
//
//
//	Eigen::Matrix<double, 4, 1> centroid;
//	centroid.setZero();
//	Eigen::Matrix4f MyMatrix;
//	MyMatrix.setZero();
//	Eigen::Matrix3f My3fMatrix;
//	//My3fMatrix<<-2, 1, 1, 0, 2, 0, -4, 1, 3;
//	My3fMatrix << -1, -4, 1, -4, 3, 0, 1, 0, 2;
//	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigen_solver(My3fMatrix);
//	cout << "My3fMatrix  " << My3fMatrix << endl;
//	cerr << "eigen value " << eigen_solver.eigenvalues() << endl;
//	cerr << "eigen vector " << eigen_solver.eigenvectors() << endl;
//
//
//	Eigen::Matrix3d A;
//	A << -1, 1, 0, -4, 3, 0, 1, 0, 2;
//	cout << "Here is a 3x3 matrix, A:" << endl << A << endl << endl;
//	Eigen::EigenSolver<Eigen::Matrix3d> es(A);
//
//	//Eigen::Matrix3d D = es.eigenvalues();
//	//Eigen::Matrix3d V = es.eigenvectors();
//	cout << "The pseudo-eigenvalue matrix D is:" << endl << es.eigenvalues() << endl;
//	cout << "The pseudo-eigenvector matrix V is:" << endl << es.eigenvectors() << endl;
//	//cout << "Finally, V * D * V^(-1) = " << endl << es.eigenvectors() * es.eigenvalues() * es.eigenvectors().inverse() << endl;
//
//
//	Eigen::Matrix3d D = es.pseudoEigenvalueMatrix();
//	Eigen::Matrix3d V = es.pseudoEigenvectors();
//	cout << "The pseudo-eigenvalue matrix D is:" << endl << D << endl;
//	cout << "The pseudo-eigenvector matrix V is:" << endl << V << endl;
//	return 0;
//}

//#include <iostream>
//#include <cstdlib>
//using namespace std;
//struct Student {
//	int id;
//	float gpa;//平均分
//};
//template <class T>
//class Store {//类模板，实现对任意类型数据进行存取
//private:
//	T item;//item用于存放任意类型的数据
//	bool haveValue;//haveValue标记item是否已被存入内容
//public://成员函数用来操作数据成员
//	Store();//构造函数
//	T &getElem();
//	void putElem(const T &x);//存入数据函数
//};
//
//template <class T>//以下是类成员函数模板
//Store<T>::Store() :haveValue(false) {}//构造函数用来初始化私有数据成员
//template <class T>
//T &Store<T>::getElem() {//注意写法
//						//如试图提取未初始化的数据，则终止程序
//	if (!haveValue) {
//		cout << "No item present!" << endl;
//		exit(1);//使程序完全退出，返回到操作系统
//	}
//	return item;//返回item中存放的数据
//}
//template <class T>
//void Store<T>::putElem(const T &x) {
//	//将haveValue的值置为TRUE，表示item中已存入数组
//	haveValue = true;
//	item = x;//将x存入item
//}
//
//
//int main()
//{
//	Store<int> s1, s2;
//	s1.putElem(3);
//	s2.putElem(-4);
//	cout << s1.getElem() << " " << s2.getElem() << endl;
//
//	Student g = { 1000,23 };
//	Store<Student> s3;
//	s3.putElem(g);
//	cout << "The student id is " << s3.getElem().id << endl;
//	Store<double> d;
//	d.putElem(98.989);
//	cout << "Retrieving object D...";
//	cout << d.getElem() << endl;
//	//d未初始化。执行函数D.getelem()导致程序终止
//	return 0;
//}

//#include<iostream>
//
//template <class T>
//void Swap(T &a, T &b);
//
//int main(void)
//{
//	using std::cout;
//
//	int i = 10, j = 20;
//
//	cout << "i,j = " << i << ", " << j << ".\n";
//	cout << "Using compiler-generated int swapper:\n";
//	Swap(i, j);
//	cout << "Now i, j = " << i << ", " << j << ".\n";
//
//	double x = 24.5, y = 81.7;
//	cout << "x, y = " << x << ". " << y << ".\n";
//	cout << "Using compiler-generated int swapper:\n";
//	Swap(x, y);
//	cout << "Now x, y = " << x << ", " << y << ".\n";
//
//	return 0;
//}
//template <class T>
//void Swap(T &a, T &b)
//{
//	T temp;
//	temp = a;
//	a = b;
//	b = temp;
//}


//int main(int argc, char** argv) 
//{
//	//Cloud3D a[2];
//	//a[0].channel = 1;
//	//a[1].channel = 2;
//	//printf("%d-------%p---- %p\n", sizeof(Cloud3D),&a[0],&a[1]);
//	//Cloud3D *p = a;
//	//int chan = p->channel;
//	//p++;
//	//chan = p->channel;
//	//return 0;
//	////三维数组
//	//int arr[2][2][2] = { 1,2,3,4,5,6,7,8 };
//	//printf("&arr %p\n", arr);
//	//for (int i = 0; i < 2; i++)
//	//{
//	//	for (int j = 0; j < 2; j++)
//	//	{
//	//		for (int k = 0; k < 2; k++)
//	//		{
//	//			printf("&arr[%d][%d][%d] = %d---- %p\n", i, j,k, arr[i][j][k], &arr[i][j][k]);
//	//		}
//	//	}
//	//}
//	//int* p = (int*)arr;
//	//int* p1;
//	//for (int i = 0; i < 8; i++)
//	//{
//	//	p1 = p + i;
//	//	printf("%d---- %p---- %p\n", p[i], &p[i], p1);
//	//}
//	//system("PAUSE");
//	//return 0;
//
//	////char数据
//	//int(*pfun1)(char*, int);
//	//int a = sizeof(pfun1);
//	//char arr[3][4] = { 'A','A','A','A','A','A','A','A','A','A','A','A', };
//	//printf("&arr %p\n", arr);
//	//int i = 0;
//	//for (i = 0; i < 3; i++)
//	//{
//	//	int j = 0;
//	//	for (j = 0; j < 4; j++)
//	//	{
//	//		printf("&arr[%d][%d] = %c---- %p\n", i, j, arr[i][j], &arr[i][j]);
//	//	}
//	//}
//	//char* p = (char*)arr;
//	//char* p1 = p;
//	//for (int i = 0; i < 12; i++)
//	//{
//	//	p1 = p + i;
//	//	printf("%c---- %p\n", p[i], p1);
//
//	//}
//	//system("PAUSE");
//	//return 0;
//
//	////二维数组
//	//int arr[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12};
//	//printf("&arr %p\n", arr);
//	//int i = 0;
//	//for (i = 0; i < 3; i++)
//	//{
//	//	int j = 0;
//	//	for (j = 0; j < 4; j++)
//	//	{
//	//		printf("&arr[%d][%d] = %d---- %p\n", i, j, arr[i][j] ,&arr[i][j]);
//	//	}
//	//}
//	//int* p = (int*)arr;
//	//int* p1 = p;
//	//for (int i = 0; i < 12; i++)
//	//{
//	//	p1 = p + i;
//	//	printf("%d---- %p\n", p[i], p1);
//	//	
//	//}
//	//system("PAUSE");
//	//return 0;
//
//	//int a = 1;
//	//int *p1 = &a;
//	//cout << "int " << sizeof(p1) << endl;
//	//float b = 1.23;
//	//float *p2 = &b;
//	//cout << "float " << sizeof(p2) << endl;
//	//double c = 1.3456;
//	//double *p3 = &c;
//	//cout << "double " << sizeof(p3) << endl;
//	//system("pause");
//	//return 0;
//
//	//Cloud3D a1;
//	//Cloud3D a2;
//	//a2.data = (float*)0x0000001;
//	//	a1 = a2;
// //   std::map<std::string, double> double_param_map_;
// //   double_param_map_["MYNAME"] = 9.0;
// //   cout << double_param_map_["MYNAME"];
//
//	//std::string func_info = __FUNCTION__;
//	//func_info = __FILE__;
//	//func_info = __LINE__;
//	//func_info = __DATE__;
//	//func_info = __TIME__;
//	//func_info = __TIMESTAMP__;
//	//func_info = FUNCTION_INFO;
//
//
//    /*Mat data_ = Mat::zeros(1, 13, CV_8UC3);
//    data_.at<uchar>(0, 0) = 123;
//    data_.at<uchar>(0, 1) = 124;
//    data_.at<uchar>(0, 2) = 333;
//    Vec3b aaa = data_.at<Vec3b>(0, 0);
//    uchar a = aaa[0];
//    uchar b = aaa[1];
//    uchar c = aaa[2];
//    int d = a;
//    unsigned char u = 1;
//    for (int i = 0; i < 20; i++)
//    {
//        u = u << 1;
//        cout << (short)u <<"   "<<i<<endl;
//    }
//    string classaaa = TEXT(aaa);
//    cout << TEXT(aaa) << endl;
//
//    T5Derived MYD;
//    MYD.test1();
//    MYD.test2();
//    MYD.value = 10;
//    MYD.test2();*/
//
//    //waitKey(0);
//    return 0;
//}

class my1111
{
public:
	my1111()
	{
		i++;
		cout << "+++++++++++++++" <<i<< endl;
		
	};
	~my1111()
	{
		i--;
		cout << "---------------" << i << endl;
		
	};
public:
	static int i;
};
int my1111::i = 0;


class b
{
public:
	b() :myarray{nullptr},nh(1000) { myinit(); }
	virtual~b();

protected:
	void myinit()
	{
		printf("base init\n");
	}
private:
	int *myarray[4];
	int nh;
};
b::~b()
{
	printf("base deconstruct\n");
}
class a : public b
{
public:
	a() { myinit(); }
	~a()
	{
		printf("children deconstruct\n");
	};
protected:
	void myinit()
	{
		printf("children init\n");
	}
private:
};
#include <memory>
int main11111()
{
	float a1, b1;
	a1 = 2.356190000;
	b1 = 2.356190000;
	if (a1 > b1)
	{
		a1 = 100.0;//p1
	}
	else
	{
		a1 = 1000.0;
	}
	b * p;
	p = new a();
	delete p;
	std::shared_ptr<b> re_method_p_;
	re_method_p_ = std::make_shared<a>();
	re_method_p_.reset();
	re_method_p_ = std::make_shared<a>();
	re_method_p_ = std::make_shared<a>();
	return 0;
}
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <memory>
//using namespace cv;
//#define PI 3.1416
//int main()
//{
//	int aa[8] = { 0 };
//	memset(aa, 1, 8 * 4);
//	memset(aa, 9999, 8 * 4);
//	memset(aa, 255, 8 * 4);
//	memset(aa, 256, 8 * 4);
//	unsigned char p = 256;
//	a bbb;
//	std::shared_ptr<my1111> re_method_p_;
//	re_method_p_ = std::make_shared<my1111>();
//	re_method_p_.reset();
//	re_method_p_ = std::make_shared<my1111>();
//	re_method_p_ = std::make_shared<my1111>();
//	return 0;
//	vector<Mat> abc;
//	Mat Basicmat = Mat(1, 10, CV_32FC1);
//	for (int j = 0; j < 10; j++)
//	{
//		Basicmat.at<float>(0, j) = j;
//	}
//	abc.clear();
//	abc.push_back(Basicmat.clone());
//	abc.push_back(Basicmat.clone());
//	Mat temp/* = Mat(ROWS, COLS, CV_32FC2)*/;
//	merge(&abc[0], 2, temp);
//	Mat PhaseTemp;
//	multiply(temp, temp, PhaseTemp);//矩阵每个数字相乘
//
//
//
//
//
//	float fs = 100;
//	float icount = 8;
//	float frequency[256] = { 0 };
//	float ftime[256];
//	float F1 = 15;
//	float F2 = 30;
//	float x[8] = {2,3,8,9,12,4,8,10};
//
//	Mat in = Mat::eye(cv::Size(8, 1), CV_32FC1);
//	Mat out;
//	memcpy(in.data, x, sizeof(float) * 8);
//	//dft(in,out, DFT_COMPLEX_OUTPUT);
//	//dft(out, in, DFT_INVERSE + DFT_REAL_OUTPUT + DFT_SCALE);
//	dft(in, out, DFT_COMPLEX_OUTPUT);
//	Mat result;
//	multiply(out, out, result);
//	//dct(out, in, DFT_INVERSE + DFT_REAL_OUTPUT + DFT_SCALE);
//
//	float real[256] = {0};
//	float imag[256] = {0};
//	float absf[256] = { 0 };
//	float degree[256] = { 0 };
//	float C[256] = {0};
//	float Re_real[256] = { 0 };
//	float Re_imag[256] = { 0 };
//	float Re_x[256] = { 0 };
//	//FFT
//	//for (int i = 0; i < icount; i++)
//	//{
//	//	frequency[i] = i*fs/icount;
//	//	ftime[i] = i / fs;
//	//	x[i] = sin(2 * PI*F1*ftime[i]) + sin(2 * PI*F2*ftime[i]);
//
//	//}
//	
//	for (int i = 0; i < icount; i++)
//	{
//		for (int j = 0; j < icount; j++)
//		{
//			real[i]= real[i]+ x[j] * cos(2 * PI*i*j / icount);
//			imag[i] = imag[i] - x[j] * sin(2 * PI*i*j / icount);
//			C[i] = C[i] + 2 * x[j]*cos(PI / (2 * icount)*i*(2 * j + 1));
//		}
//	}
//	for (int i = 0; i < icount; i++)
//	{
//		absf[i] = sqrt(real[i]* real[i]+ imag[i]* imag[i]);
//		degree[i] = atan2(imag[i], real[i]);
//	}
//	//IFFT
//	for (int i = 0; i < icount; i++)
//	{
//		for (int j = 0; j < icount; j++)
//		{
//			Re_real[i] = Re_real[i]+1 / icount*(cos(2*PI*i*j / icount)*real[i]- sin(2 * PI*i*j / icount)*imag[i]);
//			Re_imag[i] = Re_imag[i]+1 / icount*(sin(2 * PI*i*j / icount)*real[i] + cos(2 * PI*i*j / icount)*imag[i]);
//			
//		}
//		Re_x[i] = sqrt(Re_real[i] * Re_real[i] + Re_imag[i] * Re_imag[i]);
//	}
//
//	return 0;
//	glm::vec4 ldir = glm::vec4(1,2,3,4);
//	ldir = glm::normalize(ldir);
//	double rad = tan(PI / 4);
//	Mat me = Mat::eye(cv::Size(3, 3), CV_32FC1);
//	Mat he = Mat::zeros(cv::Size(4, 4), CV_32FC1);
//	for (int i = 0; i < he.rows-1; i++)
//		for (int j = 0; j < he.cols-1; j++)
//			he.at<float>(i, j) = me.at<float>(i, j);
//	he.at<float>(0, 3) = 100;
//	he.at<float>(1, 3) = 100;
//	he.at<float>(2, 3) = 100;
//
//
//	float kernel[] = { -1,5 };
//	Mat KernelX = Mat(1, 2, CV_32FC1, kernel).clone();
//	Mat KernelY = Mat(2, 1, CV_32FC1, kernel).clone();
//	Mat WarpPhase = Mat(5, 1, CV_32FC1, 4).clone();;
//	int fy = 1;
//	int fx = 5;
//	Mat ImageX;
//	repeat(WarpPhase, fy, fx, ImageX);
//	Mat divid = WarpPhase / 3;
//	divide(WarpPhase, divid, WarpPhase);
//	divide(4, divid, WarpPhase);
//	Mat DeltaX;
//	filter2D(WarpPhase, DeltaX, -1, KernelX, Point(0, 0), 0, BORDER_REPLICATE);
//	Mat VarA;
//	threshold(DeltaX, VarA, PI, -2 * PI, THRESH_BINARY); 
//	threshold(DeltaX, VarA, PI, -2 * PI, THRESH_BINARY_INV);
//	
//	return 0;
//}

#include <iostream> 
using namespace std;

//class Base
//{
//public:
//	virtual void f(float x) { cout << "Base::f(float) " << x << endl; }
//	void g(float x) { cout << "Base::g(float) " << x << endl; }
//	void h(float x) { cout << "Base::h(float) " << x << endl; }
//};
//
//class Derived : public Base
//{
//public:
//	void f(float x) { cout << "Derived::f(float) " << x << endl; }
//	void g(int x) { cout << "Derived::g(int) " << x << endl; }
//	void h(float x) { cout << "Derived::h(float) " << x << endl; }
//};
//
//int main(void)
//{
//	Derived d;
//	Base b;
//	Base *pbb = &b;
//	Base *pb = &d;
//	Derived *fd = &d;
//	// Good : behavior depends solely on type of the object
//	pbb->f(3.14f); //Derived::f(float) 3.14
//	pb->f(3.14f); //Derived::f(float) 3.14
//	fd->f(3.14f); //Derived::f(float) 3.14
//
//				  // Bad : behavior depends on type of the pointer
//	pb->g(3.14f); //Base::g(float) 3.14
//	fd->g(3.14f); //Derived::g(int) 3
//
//				  // Bad : behavior depends on type of the pointer
//	pb->h(3.14f); //Base::h(float) 3.14
//	fd->h(3.14f); //Derived::h(float) 3.14
//
//	system("pause");
//	return 0;
//}

//#include <iostream>
//#include <thread>
//#include <future>
//
//void initiazer(std::promise<double>* promObj, std::promise<double>* promObj0) {
//	std::cout << "Inside Thread" << std::endl;
//	double b = 0;
//	promObj->set_value(3825);
//	for (int i = 0; i < 1000000; i++)
//	{
//		for (int j = 0; j < 1000; j++)
//		{
//			b = b + 1.0;
//		}
//	}
//	promObj0->set_value(b);
//}
//
//int main() {
//	std::promise<double> promiseObj[2];
//	std::future<double> futureObj[2];
//	futureObj[0] = promiseObj[0].get_future();
//	futureObj[1] = promiseObj[1].get_future();
//	//std::cout << futureObj.get() << std::endl;
//	std::thread th(initiazer, &promiseObj[0], &promiseObj[1]);
//	std::cout << futureObj[0].get() << std::endl;
//	std::cout << futureObj[1].get() << std::endl;
//	th.join();
//
//	return 0;
//}
template<typename _Tp> static inline _Tp* MyalignPtr(_Tp* ptr, int n = (int)sizeof(_Tp))
{
	return (_Tp*)(((size_t)ptr + n - 1) & -n);//(((bits) + 31) / 32 * 4)
}
#define CV_MALLOC_ALIGN 32
void* MyfastMalloc(size_t size)
{
	uchar* udata = (uchar*)malloc(size + sizeof(void*) + CV_MALLOC_ALIGN);//size + 8 + 32
	if (!udata)
		return nullptr;
	printf("udata:0x%x\n", udata);
	printf("(uchar**)udata + 1:0x%x\n", (uchar**)udata + 1);
	uchar** adata = MyalignPtr((uchar**)udata + 1, CV_MALLOC_ALIGN);
	printf("adata:0x%x\n", adata);
	adata[-1] = udata;
	printf("adata[-1]:0x%x\n", adata[-1]);
	//cout << "udata:" << udata << endl;
	return adata;
}

void fastFree(void* ptr)
{
	if (ptr)
	{
		uchar* udata = ((uchar**)ptr)[-1];
		CV_DbgAssert(udata < (uchar*)ptr && ((uchar*)ptr - udata) <= (ptrdiff_t)(sizeof(void*) + CV_MALLOC_ALIGN));
		free(udata);
	}
}

#include <iostream>
#include <string>
#include <stdio.h>
#include <memory>
#include<bitset>
using namespace cv;
#define PI 3.1416
void mytest(int ptr,int n)
{
	cout << (((size_t)ptr + n - 1) & -n) << std::endl;
	cout << (((size_t)ptr + n - 1) /n*n) << std::endl;
}
int main11(int argc, char* argv[])
{
	//cout << bitset<64>(atoi(argv[1])) << endl;
	//cout << bitset<64>(-atoi(argv[1])) << endl;
	//cout << sizeof(CV_MALLOC_ALIGN) << std::endl;
	//mytest(atoi(argv[1]), 32);
	////void* ppp = MyfastMalloc((size_t)20);
	//int *p = new int[10];
	Mat	MyMat = Mat::ones(5, 5, CV_8U);
	MyMat.at<uchar>(2, 2) = 2;
	normalize(MyMat, MyMat, 0, 255, NORM_MINMAX);
	MyMat.convertTo(MyMat, CV_8UC1);
	MyMat.convertTo(MyMat, CV_16UC1);
	//imwrite(SaveImagePath + "\\HeightCPU8.tif", temp);
	Mat Dist;
	cvtColor(MyMat, MyMat, COLOR_GRAY2BGR);
	imwrite("..\\x64\\Chessboard8C3.bmp", MyMat);
	cvtColor(MyMat, MyMat, COLOR_BGR2GRAY);
	MyMat.convertTo(MyMat, CV_16U);
	cvtColor(MyMat, MyMat, COLOR_GRAY2BGR);
	imwrite("..\\x64\\Chessboard16C3.bmp", MyMat);
	imwrite("..\\x64\\Chessboard16C3.tif", MyMat);
	cvtColor(MyMat, MyMat, COLOR_BGR2GRAY);
	MyMat.convertTo(MyMat, CV_32F);
	cvtColor(MyMat, MyMat, COLOR_GRAY2BGR);
	imwrite("..\\x64\\Chessboard32SC3.bmp", MyMat);
	imwrite("..\\x64\\Chessboard32SC3.tif", MyMat);
	cvtColor(MyMat, MyMat, COLOR_BGR2GRAY);
	Mat READDDD;
	READDDD = imread("..\\x64\\Chessboard32SC3.tif",-1);
	READDDD = imread("..\\x64\\Chessboard16C3.tif",-1);
	int dims[3] = { 5,3, 1 };
	Mat src(3, dims, CV_32S, Scalar_<int>(1));
	cout << "step[0]:" << src.step[0] << endl;
	cout << "step[1]:" << src.step[1] << endl;
	cout << "step[2]:" << src.step[2] << endl;
	cout << "size[0]:" << src.size[0] << endl;
	cout << "size[1]:" << src.size[1] << endl;
	cout << "size[2]:" << src.size[2] << endl;
	src.at<int>(0, 0, 0) = 1001;
	cout << "src.at<short>(0, 0, 0);:" << src.at<int>(0, 0, 0) << endl;
	int * sp = (int *)src.data;

	cout << "sizeof(void*):" << sizeof(void*) << endl;
	cout << "src[0]:" << sp[0] << endl;
	cout << "src[1]:" << sp[1] << endl;
	cout << "src[2]:" << sp[2] << endl;
	cout << "src[3]:" << sp[3] << endl;

	cout << "src.type:" << src.type() << endl;
	cout << "src.depth:" << src.depth() << endl;
	return 0;
}




 int getIndex(int arr[], int low, int high)
 {
	// 基准数据
	int tmp = arr[low];
	while (low < high) {
		// 当队尾的元素大于等于基准数据时,向前挪动high指针
		while (low < high && arr[high] >= tmp) {
			high--;
		}
		// 如果队尾元素小于tmp了,需要将其赋值给low
		arr[low] = arr[high];
		// 当队首元素小于等于tmp时,向前挪动low指针
		while (low < high && arr[low] <= tmp) {
			low++;
		}
		// 当队首元素大于tmp时,需要将其赋值给high
		arr[high] = arr[low];
		//cout << arr[0]<<"	"<< arr[1] << "	" << arr[2] << "	" << arr[3] << endl;
	}
	
	// 跳出循环时low和high相等,此时的low或high就是tmp的正确索引位置
	// 由原理部分可以很清楚的知道low位置的值并不是tmp,所以需要将tmp赋值给arr[low]
	arr[low] = tmp;
	cout << arr[0] << "	" << arr[1] << "	" << arr[2] << "	" << arr[3] << "	" << arr[4] << "	" << arr[5] << "	" << arr[6] << "	" << arr[7] << "	" << arr[8] << endl;
	return low; // 返回tmp的正确位置
}
 void quickSort(int arr[], int low, int high) {

	 if (low < high) {
		 // 找寻基准数据的正确索引
		 int index = getIndex(arr, low, high);
		 cout << index /*<< "	" << arr[1] << "	" << arr[2] << "	" << arr[3]*/ << endl;
		 // 进行迭代对index之前和之后的数组进行相同的操作使整个数组变成有序
		 quickSort(arr, 0, index - 1);
		 quickSort(arr, index + 1, high);
	 }

 }

 void quickSort1(int a[], int left, int right) 
 {
	 if (left > right)//递归基
		 return;

	 int i, j, temp;
	 temp = a[left]; //temp中存的就是基准数
	 i = left;
	 j = right;
	 while (i != j) 
	 { //顺序很重要，要先从右边开始找
		 while (a[j] >= temp && i < j)
		 {
			 j--;
		 }
			 
		 while (a[i] <= temp && i < j)//再找右边的
		 {
			 i++;
		 }
			 
		 if (i < j)//交换两个数在数组中的位置
		 {
			 swap(a[i], a[j]);
		 }
	 }
	 cout << a[0] << "	" << a[1] << "	" << a[2] << "	" << a[3] << "	" << a[4] << "	" << a[5]<< endl;
	 //最终将基准数归位
	 a[left] = a[i];
	 a[i] = temp;
	 quickSort1(a,left, i - 1);//继续处理左边的，这里是一个递归的过程
	 quickSort1(a,i + 1, right);//继续处理右边的 ，这里是一个递归的过程
 }

 void main00000() 
 {
	 

	 int arr[6] = {3,6,9,2,4,5};
	 //quickSort(arr, 0, 8);
	 quickSort1(arr, 0, 5);
	 cout << arr[0] << "	" << arr[1] << "	" << arr[2] << "	" << arr[3] << "	" << arr[4] << "	" << arr[5] << "	" << arr[6] << "	" << arr[7] << "	" << arr[8] << endl;
	 int b = 0;
	 return;
 }
