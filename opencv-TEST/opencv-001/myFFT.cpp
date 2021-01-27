#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include "cv.hpp"
#include "cudaarithm.hpp"
#include "cudafilters.hpp"
using namespace cv;
using namespace std;
#define PI 3.1416
#define COUNT_SUM 128           //数据点数
int main()
{
    float fs = 100;//采样频率
    float frequency[COUNT_SUM] = { 0 };
    float ftime[COUNT_SUM];
    float F1 = 15;
    float F2 = 40;
    float x[COUNT_SUM] = {0};
    
    //Mat in = Mat::eye(cv::Size(8, 1), CV_32FC1);
    //Mat out;
    //memcpy(in.data, x, sizeof(float) * 8);
    ////dft(in,out, DFT_COMPLEX_OUTPUT);
    ////dft(out, in, DFT_INVERSE + DFT_REAL_OUTPUT + DFT_SCALE);
    //dft(in, out, DFT_COMPLEX_OUTPUT);
    //Mat result;
    //multiply(out, out, result);
    ////dct(out, in, DFT_INVERSE + DFT_REAL_OUTPUT + DFT_SCALE);
    
    float real[COUNT_SUM] = {0};
    float imag[COUNT_SUM] = {0};
    float absf[COUNT_SUM] = { 0 };
    float degree[COUNT_SUM] = { 0 };
    
    float Re_real[COUNT_SUM] = { 0 };
    float Re_imag[COUNT_SUM] = { 0 };
    float Re_FFT_x[COUNT_SUM] = { 0 };
    float Re_COS_x[COUNT_SUM] = { 0 };

    float f_ratio = 1.0 / COUNT_SUM;

    float C[COUNT_SUM] = { 0 };
    float C1[COUNT_SUM] = { 0 };
    float C2[COUNT_SUM] = { 0 };
    float C3[COUNT_SUM] = { 0 };
    float C4[COUNT_SUM] = { 0 };
    //FFT
    for (int i = 0; i < COUNT_SUM; i++)
    {
    	frequency[i] = i*fs* f_ratio;
    	ftime[i] = i / fs;
    	x[i] = sin(2 * PI*F1*ftime[i]) + sin(2 * PI*F2*ftime[i]);
    }
    
    float dct_ratio = sqrt(2 * f_ratio);
    for (int i = 0; i < COUNT_SUM; i++)
    {
    	for (int j = 0; j < COUNT_SUM; j++)
    	{
    		real[i]= real[i]+ x[j] * cos(2 * PI*i*j * f_ratio);//(2*pi*k)/N * j
    		imag[i] = imag[i] - x[j] * sin(2 * PI*i*j * f_ratio);
    		C[i] = C[i] + dct_ratio * x[j]*cos(PI / (2 * COUNT_SUM)*i*(2*j + 1));//2*pi*k / N * (j+1/2)/2
            C1[i] = C1[i] + dct_ratio * x[j] * cos(PI / (COUNT_SUM-1)*i*j);//DCT-1
            C2[i] = C2[i] + dct_ratio * x[j] * cos(PI / (COUNT_SUM*2)*i*(2*j-1));//DCT-2
            C3[i] = C3[i] + dct_ratio * x[j] * cos(PI / (COUNT_SUM * 2)*j*(2 * i - 1));//DCT-3
            C4[i] = C4[i] + dct_ratio * x[j] * cos(PI / (COUNT_SUM * 4)*(2*j-1)*(2 * i - 1));//DCT-4
    	}
    }
    C[0] = C[0] / sqrt(2);
    for (int i = 0; i < COUNT_SUM; i++)
    {
    	absf[i] = sqrt(real[i]* real[i]+ imag[i]* imag[i]);
    	degree[i] = atan2(imag[i], real[i]);
    }
    Mat absf_MAT = Mat::eye(cv::Size(COUNT_SUM, 1), CV_32FC1);
    memcpy(absf_MAT.data, absf, sizeof(float) * COUNT_SUM);
    
    //IFFT
    float k = 1.0 / sqrt(2);
    for (int i = 0; i < COUNT_SUM; i++)
    {
    	for (int j = 0; j < COUNT_SUM; j++)
    	{
    		Re_real[i] = Re_real[i]+ f_ratio*(cos(2*PI*i*j * f_ratio)*real[j]- sin(2 * PI*i*j * f_ratio)*imag[j]);
    		Re_imag[i] = Re_imag[i]+ f_ratio*(sin(2 * PI*i*j * f_ratio)*real[j] + cos(2 * PI*i*j * f_ratio)*imag[j]);
            if (i == 0)
            {
                k = 1.0 / sqrt(2);
            } 
            else
            {
                k = 1.0;
            }
            Re_COS_x[i] = Re_COS_x[i] + dct_ratio *k* C[j] * cos(PI / (2 * COUNT_SUM)*j*(2 * i + 1));
    			
    	}
    	Re_FFT_x[i] = sqrt(Re_real[i] * Re_real[i] + Re_imag[i] * Re_imag[i]);
    }
    
    system("pause");
    return 0;
}