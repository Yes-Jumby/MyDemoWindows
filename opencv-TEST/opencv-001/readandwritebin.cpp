#include <string>
#include <fstream>
#include <iostream>
#include "cloud.h"
void writebin1(std::string path)
{
	std::cout << "Cloud3D:" << sizeof(Cloud3D) << std::endl;
	Cloud3D cloud;
	cloud.cloud_size = 1;
	cloud.maxx = 3825;
	float z = 100;
	unsigned char intensity = 255;
	std::ofstream mDataStream;
	mDataStream.open(path, std::ios::binary | std::ios::ate);
	if (!mDataStream.is_open())
	{
		std::cout << "write bin failed" << std::endl;
	}
	mDataStream.write(reinterpret_cast<const char*>(&cloud), sizeof(Cloud3D));
	mDataStream.write(reinterpret_cast<const char*>(&z), cloud.cloud_size * sizeof(float));
	mDataStream.write(reinterpret_cast<const char*>(&intensity), cloud.cloud_size * sizeof(unsigned char));
	mDataStream.close();
}
void readbin1(std::string path)
{
	Cloud3D cloud;
	float z = 0;
	unsigned char intensity = 0;

	std::ifstream mDataInput(path, std::ifstream::binary);
	if (!mDataInput.is_open())
	{
		std::cout << "read bin failed" << std::endl;
	}
	//// get length of file:
	//mDataInput.seekg(0, mDataInput.end);
	//int length = mDataInput.tellg();
	mDataInput.seekg(0, mDataInput.beg);
	mDataInput.read((char*)&cloud, sizeof(Cloud3D));

	mDataInput.seekg(sizeof(Cloud3D), mDataInput.beg);
	mDataInput.read((char*)&z, cloud.cloud_size * sizeof(float));

	mDataInput.seekg(sizeof(Cloud3D) + cloud.cloud_size * sizeof(float), mDataInput.beg);
	mDataInput.read((char*)&intensity, cloud.cloud_size * sizeof(unsigned char));
	mDataInput.close();

	std::cout << "z:" << z << std::endl;
	std::cout << "intensity:" << (int)intensity << std::endl;

}
int mainread()
{
	std::string path;
	path = "D:\\Stereo3D\\test.999";
	writebin1(path);
	readbin1(path);

	return 0;
}
