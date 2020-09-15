#include "ImageSaveAndRead.h"

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
