//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include"getMargin.h"
#include "construct_getMargin.h"
using namespace std;

int main0319999()
{
	double a = floor(-10.0);
	cout << a << endl;
	string imgpath = "D:/Stereo3D/data/test1209/BINOCULAR/0323/1/";
	string ouputpath = "D:/Stereo3D/bin/";
	getMargin(imgpath, 25, ouputpath);
	
	//float line1[8];
	//Mat bright = imread("D:/Stereo3D/data/test1209/BINOCULAR/0320/4/left/0000.bmp",0);
	//Mat phase = imread("D:/Stereo3D/data/test1209/BINOCULAR/0320/4/left/0002.bmp",0);
	//getMargin1(bright, phase, 2448, 2048, 25, line1);
	//bright = imread("D:/Stereo3D/data/test1209/BINOCULAR/0320/4/right/0000.bmp",0);
	//phase = imread("D:/Stereo3D/data/test1209/BINOCULAR/0320/4/right/0002.bmp",0);
	//getMargin1(bright, phase, 2448, 2048, 25, &line1[4]);
	return 0;
}
