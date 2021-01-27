// CUDA runtime 库 + CUBLAS 库
#include "cuda_runtime.h"
#include "cublas_v2.h"
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
// 定义测试矩阵的维度
int const A_ROW = 3;
int const A_COL = 1;
int const B_ROW = 1;
int const B_COL = 3;

int main11222221()
{

	Mat X = Mat::ones(2, 2448, CV_32F);
	for (int i = 0; i < 2448; i++)
	{
		X.at<float>(0, i)=i+1;
	}
	X = X.t();
	Mat COFFFFF = X*((X.t()*X).inv())*X.t();//
	// 定义状态变量
	cublasStatus_t status;
	 //在内存中开辟空间
	float *h_A, *h_B, *h_C;    //存储于显存中的矩阵
	h_A = (float*)malloc(sizeof(float)*B_ROW*B_COL);
	h_B = (float*)malloc(sizeof(float)*B_ROW*B_COL);
	h_C = (float*)malloc(sizeof(float)*A_ROW*B_COL);

	//0.414321288604656	0.325286165381830	0.324780957273329	0.325031346860598	0.325142287794897
	// 为待运算矩阵的元素赋予 0-10 范围内的随机数
	for (int i = 0; i<A_ROW*A_COL; i++) {
		h_A[i] = (float)(rand() % 10 + 1);
	}
	for (int i = 0; i<B_ROW*B_COL; i++) {
		h_B[i] = (float)(rand() % 10 + 1);
	}
	// 打印待测试的矩阵
	cout << "矩阵 A :" << endl;
	for (int i = 0; i<A_ROW*A_COL; i++) {
		cout << h_A[i] << " ";
		if ((i + 1) % A_COL == 0) cout << endl;
	}
	cout << endl;
	cout << "矩阵 B :" << endl;
	for (int i = 0; i<B_ROW*B_COL; i++) {
		cout << h_B[i] << " ";
		if ((i + 1) % B_COL == 0) cout << endl;
	}
	cout << endl;

	float *d_A, *d_B, *d_C;    //存储于显存中的矩阵
	cudaMalloc((void**)&d_A, sizeof(float)*A_ROW*A_COL); //在显存中开辟空间
	cudaMalloc((void**)&d_B, sizeof(float)*B_ROW*B_COL);
	cudaMalloc((void**)&d_C, sizeof(float)*A_ROW*B_COL);

	cublasHandle_t handle;
	cublasCreate(&handle);
	cudaMemcpy(d_A, h_A, sizeof(float)*A_ROW*A_COL, cudaMemcpyHostToDevice); //数据从内存拷贝到显存
	cudaMemcpy(d_B, h_B, sizeof(float)*B_ROW*B_COL, cudaMemcpyHostToDevice);

	float a = 1, b = 0;
	cublasSgemm(
		handle,
		CUBLAS_OP_T,   //矩阵A的属性参数，转置，按行优先
		CUBLAS_OP_T,   //矩阵B的属性参数，转置，按行优先
		A_ROW,          //矩阵A、C的行数2448
		B_COL,          //矩阵B、C的列数2448
		A_COL,          //A的列数，B的行数，此处也可为B_ROW,一样的2448
		&a,             //alpha的值
		d_A,            //左矩阵，为A
		A_COL,          //A的leading dimension，此时选择转置，按行优先，则leading dimension为A的列数
		d_B,            //右矩阵，为B
		B_COL,          //B的leading dimension，此时选择转置，按行优先，则leading dimension为B的列数
		&b,             //beta的值
		d_C,            //结果矩阵C
		A_ROW           //C的leading dimension，C矩阵一定按列优先，则leading dimension为C的行数
	);
	//此时得到的结果便是C=AB,但由于C是按列优先，故此时得到的C应该是正确结果的转置
	std::cout << "计算结果的转置 ( (A*B)的转置 )：" << std::endl;


	cudaMemcpy(h_C, d_C, sizeof(float)*A_ROW*B_COL, cudaMemcpyDeviceToHost);
	for (int i = 0; i<A_ROW*B_COL; ++i) {
		std::cout << h_C[i] << " ";
		if ((i + 1) % B_COL == 0) std::cout << std::endl;
	}
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	free(h_A);
	free(h_B);
	free(h_C);
	return 0;
}