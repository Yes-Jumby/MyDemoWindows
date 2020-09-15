#include "readAndWriteDat.h"
bool CReadAndWriteDat::writeToCloudfast(const std::string &path,int size_)
{
    float pCloud[4] = { 1.111111,2.123456,3.1,4 };
    const char *pcCloud = reinterpret_cast<const char*>(pCloud);
    std::ofstream outfile;
    outfile.open(path, std::ios::ate | std::ios::binary);
    if (!outfile)
    {
        return false;
    }
    std::stringstream ss;
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss.precision(3);
    m_SpendTime.Start();
    for (int i = 0; i<size_; i++)
    {
        ss << pCloud[0] << " " << pCloud[1] << " " << pCloud[2] << " " << pCloud[3]  << "\n";
    }
    cout << "for time consume :"<<m_SpendTime.GetTimeInterval() << endl;;
    m_SpendTime.Start();
    for (int i = 0; i<size_; i++)
    {
        pCloud[0] = 0;
    }
    cout << "null for time consume :" << m_SpendTime.GetTimeInterval() << endl;;
    outfile << ss.str();

    //outfile.flush();
    outfile.close();
    return true;

}
bool CReadAndWriteDat::writeToCloudslow(const std::string &path, int size_)
{
    float pCloud[4] = { 1.111111,2.123456,3.1,4 };
    const char *pcCloud = reinterpret_cast<const char*>(pCloud);
    std::ofstream outfile;
    outfile.open(path, std::ios::ate | std::ios::binary);
    if (!outfile)
    {
        return false;
    }
    outfile.setf(std::ios::fixed, std::ios::floatfield);
    outfile.precision(3);
    m_SpendTime.Start();
    for (int i = 0; i<size_; i++)
    {
        outfile << pCloud[0] << " " << pCloud[1] << " " << pCloud[2] << " " << pCloud[3] << "\n";
    }
    cout << "for time consume :" << m_SpendTime.GetTimeInterval() << endl;;
    m_SpendTime.Start();
    for (int i = 0; i<size_; i++)
    {
        pCloud[0] = 0;
    }
    cout << "null for time consume :" << m_SpendTime.GetTimeInterval() << endl;;

    outfile.close();
    return true;

}
bool CReadAndWriteDat::readbinToCloud(const std::string & path)
{
	std::string infilePath = path;
	int pos = infilePath.find(".");
	std::string outfilePath = infilePath.substr(0, pos) + ".txt";

	Cloud3D cloud;

	std::ifstream mDataInput(path, std::ifstream::binary);
	if (!mDataInput.is_open())
	{
		std::cout << "read bin failed" << std::endl;
		return false;
	}

	//// get length of file:
	//mDataInput.seekg(0, mDataInput.end);
	//int length = mDataInput.tellg();
	mDataInput.seekg(0, mDataInput.beg);
	mDataInput.read((char*)&cloud, sizeof(Cloud3D));

    std::cerr <<cloud.cloud_size<< std::endl;
	float *pRange = new float[cloud.cloud_size];
	unsigned char *pIntensity = new unsigned char[cloud.cloud_size];
	float * pCloud = new float[cloud.cloud_size * 4];

	mDataInput.seekg(sizeof(Cloud3D), mDataInput.beg);
	mDataInput.read((char*)pRange, cloud.cloud_size *sizeof(float));

	mDataInput.seekg(sizeof(Cloud3D)+ cloud.cloud_size * sizeof(float), mDataInput.beg);
	mDataInput.read((char*)pIntensity, cloud.cloud_size * sizeof(unsigned char));
	mDataInput.close();

	float Xscale = (cloud.maxx - cloud.minx) / cloud.cols;
	//cv::Mat range = cv::Mat(cloud.rows, cloud.cols, CV_32FC1, pRange);

	std::ofstream outfile;
	outfile.open(outfilePath, std::ios::ate);
	if (!outfile)
	{
		return false;
	}
	outfile.setf(std::ios::fixed, std::ios::floatfield);
	outfile.precision(3);
	int idx = 0;
	for (int i = 0; i < cloud.rows; i++)
	{
		for (int j = 0; j < cloud.cols; j++)
		{
			idx = j + i*cloud.cols;
            pCloud[idx * 4] = j*cloud.dx+cloud.minx;
            pCloud[idx * 4 + 1] = i*cloud.dy;
			pCloud[idx * 4 + 2] = pRange[idx];
			pCloud[idx * 4 + 3] = (float)pIntensity[idx];
			outfile << pCloud[idx * 4] << " " << pCloud[idx * 4 + 1] << " " << pCloud[idx * 4 + 2] << " " << pCloud[idx * 4 + 3] << "\n";
		}
	}

	delete[]pRange;
	delete[]pIntensity;
	//delete[]pX;
	delete[]pCloud;
    return true;

}

bool CReadAndWriteDat::readbinToCloud1(const std::string & path)
{
    std::string infilePath = path;
    int pos = infilePath.find(".");
    std::string outfilePath = infilePath.substr(0, pos) + ".txt";

    Cloud3D cloud;

    std::ifstream mDataInput(path, std::ifstream::binary);
    if (!mDataInput.is_open())
    {
        std::cout << "read bin failed" << std::endl;
        return false;
    }

    //// get length of file:
    //mDataInput.seekg(0, mDataInput.end);
    //int length = mDataInput.tellg();
    cloud.cloud_size = 2560 * 500;
    cloud.cols = 2560;
    cloud.rows = 500;
    cloud.minx = 80;
    cloud.dx = 0.05;
    cloud.dy = 0.05;
    mDataInput.seekg(0, mDataInput.beg);
    
    float *pRange = new float[cloud.cloud_size];
    mDataInput.read((char*)pRange, cloud.cloud_size * sizeof(float));
    mDataInput.close();


    std::ofstream outfile;
    outfile.open(outfilePath, std::ios::ate);
    if (!outfile)
    {
        return false;
    }
    outfile.setf(std::ios::fixed, std::ios::floatfield);
    outfile.precision(3);
    int idx = 0;
    float x, y, z, gray;
    for (int i = 0; i < cloud.rows; i++)
    {
        for (int j = 0; j < cloud.cols; j++)
        {
            idx = j + i*cloud.cols;
            x = j*cloud.dx + cloud.minx;
            y = i*cloud.dy;
            z = pRange[idx];
            gray = 255.0;
            outfile << x << " " << y << " " << z << " " << gray << "\n";
        }
    }
    delete[]pRange;
    return true;

}

void CReadAndWriteDat::writebin(const std::string & path,const Cloud3D &cloud,void *pbuffer3D,void *pbuffer2D){
    std::ofstream mDataStream;
    mDataStream.open(path,std::ios::binary| std::ios::ate);
    if (!mDataStream.is_open()){
        std::cout << "write bin failed" << std::endl;
    }
    mDataStream.write(reinterpret_cast<const char*>(&cloud),sizeof(Cloud3D));
    mDataStream.write(reinterpret_cast<const char*>(pbuffer3D), cloud.cloud_size*sizeof(float));
    mDataStream.write(reinterpret_cast<const char*>(pbuffer2D), cloud.cloud_size*sizeof(unsigned char));
    mDataStream.close();
}
bool CReadAndWriteDat::transformToCloudWin(const std::string & inpath)//withNAN
{
	//std::string infilePath = "D:\\Stereo3D\\cali\\Tutorial1-GettingStarted\\Images\\img-0.dat";
	std::string infilePath = inpath;
	int pos = infilePath.find(".");
	std::string xmlfilePath = infilePath.substr(0, pos) + ".xml";
	std::string outfilePath = infilePath.substr(0, pos) + ".txt";


	int cols = 2560;
	float lower_x;
	float upper_x;
	float lower_z;;
	float upper_z;
	int sizeperRows;
	std::ifstream mDataInput(infilePath, std::ifstream::binary);
    if (!mDataInput.is_open())
    {
        std::cout << "read bin failed" << std::endl;
        return false;
    }
    if (mDataInput.is_open())
	{
		// get length of file:
		mDataInput.seekg(0, mDataInput.end);
		int length = mDataInput.tellg();
		mDataInput.seekg(0, mDataInput.beg);
		
		int rows = length / (sizeof(float) /*+ sizeof(char)*/ + sizeof(float)) / cols;

		std::cout << "length:" << length << std::endl;
		std::cout << "rows:" << rows << std::endl;
		std::cout << "cols:" << cols << std::endl;
		//char * buffer = new char[length];
		int mySize = rows*cols;
		float *pRange = new float[mySize];
		float *pIntensity = new float[mySize];
		//float *pX = new float[mySize];
		float * pCloud = new float[mySize * 4];
		std::cout << "Reading " << length << " characters... " << std::endl;
		// read data as a block:
		mDataInput.read((char*)pRange, sizeof(float)*mySize);
		mDataInput.seekg(sizeof(float)*mySize, mDataInput.beg);
		mDataInput.read((char*)pIntensity, sizeof(float)*mySize);
		//mDataInput.seekg(sizeof(float)*mySize + sizeof(unsigned char)*mySize, mDataInput.beg);
		//mDataInput.read((char*)pX, sizeof(float)*mySize);
		std::cout << "all characters read successfully." << pRange[1000]<< "****"<<0.123456789<< std::endl;
		mDataInput.close();

		float Xscale = (339.786 - 74.0131) / 2560;
		std::cout << "Xscale:" << Xscale << std::endl;

		//cv::Mat range = cv::Mat(rows, cols, CV_32FC1, pRange);

		std::ofstream outfile;
		outfile.open(outfilePath, std::ios::ate);
		if (!outfile.is_open())
		{
			return false;
		}
		outfile.setf(std::ios::fixed, std::ios::floatfield);
		outfile.precision(3);              //输出数据有效数字位数

		int idx = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				idx = j + i*cols;
				pCloud[idx * 4] = j*Xscale;
				pCloud[idx * 4 + 1] = i*Xscale;
				pCloud[idx * 4 + 2] = pRange[idx];
				pCloud[idx * 4 + 3] = (float)pIntensity[idx];
				outfile << pCloud[idx * 4] << " " << pCloud[idx * 4 + 1] << " " << pCloud[idx * 4 + 2] << " " << pCloud[idx * 4 + 3] << "\n";
			}
		}

		//for (size_t h = 0; h < cloud_size; h++)
		//{
		//	int index = h * cloud->channel;
		//	for (size_t k = 0; k < cloud->channel; k++)
		//	{
		//		outfile << cloud->data[index + k] << "  ";
		//	}
		//	outfile << "\n";
		//}

		outfile.close();
		delete[]pRange;
		delete[]pIntensity;
		//delete[]pX;
		delete[]pCloud;

	}
	return true;
}
bool CReadAndWriteDat::transformToCloudLinux(const std::string & inpath)//withoutNAN
{
	//std::string infilePath = "D:\\Stereo3D\\cali\\Tutorial1-GettingStarted\\Images\\img-0.dat";
	std::string infilePath = inpath;
	int pos = infilePath.find(".");
	std::string xmlfilePath = infilePath.substr(0, pos) + ".xml";
	std::string outfilePath = infilePath.substr(0, pos) + ".txt";


	int cols = 2560;
	float lower_x;
	float upper_x;
	float lower_z;;
	float upper_z;
	int sizeperRows;
	//cv::FileStorage fs(xmlfilePath, cv::FileStorage::READ);    //OpenCV 读XML文件流
	//fs["lower bound x"] >> lower_x;
	//fs["lower bound x"] >> upper_x;
	//fs["upper bound z"] >> lower_z;
	//fs["upper bound z"] >> upper_z;
	//fs["size"] >> sizeperRows;
	//fs["width"] >> cols;
	//fs.release();
	std::ifstream mDataInput(infilePath, std::ifstream::binary);
    if (!mDataInput.is_open())
    {
        std::cout << "read bin failed" << std::endl;
        return false;
    }
    if (mDataInput.is_open())
	{
		// get length of file:
		mDataInput.seekg(0, mDataInput.end);
		int length = mDataInput.tellg();
		mDataInput.seekg(0, mDataInput.beg);

		int rows = length / (sizeof(float) /*+ sizeof(char)*/ + sizeof(unsigned char)) / cols;

		//std::cout << "length:" << length << std::endl;
		//std::cout << "rows:" << rows << std::endl;
		//std::cout << "cols:" << cols << std::endl;
		//char * buffer = new char[length];
		int mySize = rows*cols;
		float *pRange = new float[mySize];
		unsigned char *pIntensity = new unsigned char[mySize];
		//float *pX = new float[mySize];
		float * pCloud = new float[mySize * 4];
		std::cout << "Reading " << length << " characters... " << std::endl;
		// read data as a block:
		mDataInput.read((char*)pRange, sizeof(float)*mySize);
		mDataInput.seekg(sizeof(float)*mySize, mDataInput.beg);
		mDataInput.read((char*)pIntensity, sizeof(unsigned char)*mySize);
		//mDataInput.seekg(sizeof(float)*mySize + sizeof(unsigned char)*mySize, mDataInput.beg);
		//mDataInput.read((char*)pX, sizeof(float)*mySize);
		//std::cout << "all characters read successfully." << pRange[1000] << "****" << 0.123456789 << std::endl;
		mDataInput.close();

		float Xscale = (339.786 - 74.0131) / 2560;
		std::cout << "Xscale:" << Xscale << std::endl;

		//cv::Mat range = cv::Mat(rows, cols, CV_32FC1, pRange);

		std::ofstream outfile;
		outfile.open(outfilePath, std::ios::ate);
		if (!outfile)
		{
			return false;
		}
		outfile.setf(std::ios::fixed, std::ios::floatfield);
		outfile.precision(3);              //输出数据有效数字位数

		int idx = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				idx = j + i*cols;
				pCloud[idx * 4] = j*Xscale;
				pCloud[idx * 4 + 1] = i*Xscale;
				pCloud[idx * 4 + 2] = pRange[idx];
				pCloud[idx * 4 + 3] = (float)pIntensity[idx];
				outfile << pCloud[idx * 4] << " " << pCloud[idx * 4 + 1] << " " << pCloud[idx * 4 + 2] << " " << pCloud[idx * 4 + 3] << "\n";
			}
		}

		//for (size_t h = 0; h < cloud_size; h++)
		//{
		//	int index = h * cloud->channel;
		//	for (size_t k = 0; k < cloud->channel; k++)
		//	{
		//		outfile << cloud->data[index + k] << "  ";
		//	}
		//	outfile << "\n";
		//}

		outfile.close();
		delete[]pRange;
		delete[]pIntensity;
		//delete[]pX;
		delete[]pCloud;

	}
	return true;
}
