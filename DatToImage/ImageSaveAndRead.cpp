#include "ImageSaveAndRead.h"
#include "cloud.h"
CImageSaveAndRead::CImageSaveAndRead():m_id(1000000000000000000)
{

}


bool CImageSaveAndRead::SaveToImage(std::string path,void*pBuffer,int width,int height) {
//    qDebug()<<QString::fromStdString(path);
//    qDebug()<<width;
//    qDebug()<<height;
    std::string savepath = path +std::to_string(m_id)+".png";
    m_id=m_id+100000000;
    qDebug()<<QString::fromStdString(savepath);
    return QImage(static_cast<uchar*>(pBuffer),
           static_cast<int>(width),
           static_cast<int>(height),
           QImage::Format::Format_Grayscale8).save(QString::fromStdString(savepath),"PNG",100);

}
bool CImageSaveAndRead::readToImage(const std::string &path,const std::string &outpath,uchar *pBuffer,int size_)
{
//    qDebug()<<"size_:"<<size_;
//    qDebug()<<"pBuffer:"<<pBuffer;
    //read
    std::string infilePath = path;
    int pos = infilePath.find(".");
    //std::string outfilePath = infilePath.substr(0, pos) + ".png";

    std::ifstream mDataInput(path, std::ifstream::binary);
    if (!mDataInput.is_open())
    {
        qDebug() << "read bin failed";
        return false;
    }

    //// get length of file:
//    mDataInput.seekg(0, mDataInput.end);
//    int length = mDataInput.tellg();
//    qDebug()<<"length of dat:"<<length;
    mDataInput.seekg(0, mDataInput.beg);
    //qDebug()<<"11";
    mDataInput.read((char*)pBuffer, size_);
    //qDebug()<<"12";
    mDataInput.close();
    //qDebug()<<"13";
    return SaveToImage(outpath,pBuffer);

}

bool CImageSaveAndRead::SaveToImage_IMU(std::string path,long long id,void*pBuffer,int width,int height) {
//    qDebug()<<QString::fromStdString(path);
//    qDebug()<<width;
//    qDebug()<<height;
    std::string savepath = path +std::to_string(id)+".png";
    qDebug()<<QString::fromStdString(savepath);
    return QImage(static_cast<uchar*>(pBuffer),
           static_cast<int>(width),
           static_cast<int>(height),
           QImage::Format::Format_Grayscale8).save(QString::fromStdString(savepath),"PNG",100);

}
bool CImageSaveAndRead::readToImage_IMU(const std::string &path,const std::string &outpath,long long id,uchar *pBuffer,int size_)
{
//    qDebug()<<"size_:"<<size_;
//    qDebug()<<"pBuffer:"<<pBuffer;
    //read
    std::string infilePath = path;
    int pos = infilePath.find(".");
    //std::string outfilePath = infilePath.substr(0, pos) + ".png";

    std::ifstream mDataInput(path, std::ifstream::binary);
    if (!mDataInput.is_open())
    {
        qDebug() << "read bin failed";
        return false;
    }

    //// get length of file:
//    mDataInput.seekg(0, mDataInput.end);
//    int length = mDataInput.tellg();
//    qDebug()<<"length of dat:"<<length;
    mDataInput.seekg(0, mDataInput.beg);
    //qDebug()<<"11";
    mDataInput.read((char*)pBuffer, size_);
    //qDebug()<<"12";
    mDataInput.close();
    //qDebug()<<"13";
    return SaveToImage_IMU(outpath,id,pBuffer);

}
bool CImageSaveAndRead::readbinToCloud(const std::string & path)
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
    cloud.cloud_size = 2560;
    cloud.rows = 1;

    //std::cerr <<cloud.cloud_size<< std::endl;
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
