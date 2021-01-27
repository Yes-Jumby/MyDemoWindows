// CUDA runtime �� + CUBLAS ��
#include "cuda_runtime.h"
#include "cublas_v2.h"
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
// ������Ծ����ά��
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
	// ����״̬����
	cublasStatus_t status;
	 //���ڴ��п��ٿռ�
	float *h_A, *h_B, *h_C;    //�洢���Դ��еľ���
	h_A = (float*)malloc(sizeof(float)*B_ROW*B_COL);
	h_B = (float*)malloc(sizeof(float)*B_ROW*B_COL);
	h_C = (float*)malloc(sizeof(float)*A_ROW*B_COL);

	//0.414321288604656	0.325286165381830	0.324780957273329	0.325031346860598	0.325142287794897
	// Ϊ����������Ԫ�ظ��� 0-10 ��Χ�ڵ������
	for (int i = 0; i<A_ROW*A_COL; i++) {
		h_A[i] = (float)(rand() % 10 + 1);
	}
	for (int i = 0; i<B_ROW*B_COL; i++) {
		h_B[i] = (float)(rand() % 10 + 1);
	}
	// ��ӡ�����Եľ���
	cout << "���� A :" << endl;
	for (int i = 0; i<A_ROW*A_COL; i++) {
		cout << h_A[i] << " ";
		if ((i + 1) % A_COL == 0) cout << endl;
	}
	cout << endl;
	cout << "���� B :" << endl;
	for (int i = 0; i<B_ROW*B_COL; i++) {
		cout << h_B[i] << " ";
		if ((i + 1) % B_COL == 0) cout << endl;
	}
	cout << endl;

	float *d_A, *d_B, *d_C;    //�洢���Դ��еľ���
	cudaMalloc((void**)&d_A, sizeof(float)*A_ROW*A_COL); //���Դ��п��ٿռ�
	cudaMalloc((void**)&d_B, sizeof(float)*B_ROW*B_COL);
	cudaMalloc((void**)&d_C, sizeof(float)*A_ROW*B_COL);

	cublasHandle_t handle;
	cublasCreate(&handle);
	cudaMemcpy(d_A, h_A, sizeof(float)*A_ROW*A_COL, cudaMemcpyHostToDevice); //���ݴ��ڴ濽�����Դ�
	cudaMemcpy(d_B, h_B, sizeof(float)*B_ROW*B_COL, cudaMemcpyHostToDevice);

	float a = 1, b = 0;
	cublasSgemm(
		handle,
		CUBLAS_OP_T,   //����A�����Բ�����ת�ã���������
		CUBLAS_OP_T,   //����B�����Բ�����ת�ã���������
		A_ROW,          //����A��C������2448
		B_COL,          //����B��C������2448
		A_COL,          //A��������B���������˴�Ҳ��ΪB_ROW,һ����2448
		&a,             //alpha��ֵ
		d_A,            //�����ΪA
		A_COL,          //A��leading dimension����ʱѡ��ת�ã��������ȣ���leading dimensionΪA������
		d_B,            //�Ҿ���ΪB
		B_COL,          //B��leading dimension����ʱѡ��ת�ã��������ȣ���leading dimensionΪB������
		&b,             //beta��ֵ
		d_C,            //�������C
		A_ROW           //C��leading dimension��C����һ���������ȣ���leading dimensionΪC������
	);
	//��ʱ�õ��Ľ������C=AB,������C�ǰ������ȣ��ʴ�ʱ�õ���CӦ������ȷ�����ת��
	std::cout << "��������ת�� ( (A*B)��ת�� )��" << std::endl;


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