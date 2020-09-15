#ifndef IMAGESAVEANDREAD_H
#define IMAGESAVEANDREAD_H
#include <QVector>
#include <QImage>
#include <QDebug>
#include <string>
#include <fstream>
class CImageSaveAndRead
{
public:
    CImageSaveAndRead();
    //rename with stamp of imu
    bool SaveToImage_IMU(std::string path,long long id,void*pBuffer,int width=2560,int height=832);
    bool readToImage_IMU(const std::string &path,const std::string &outpath,long long id,uchar *pBuffer,int size_ = 2560*832);
    //camera calib
    bool SaveToImage(std::string path,void*pBuffer,int width=2560,int height=832);
    bool readToImage(const std::string &path,const std::string &outpath,uchar *pBuffer,int size_ = 2560*832);
private:
    long long m_id;
};

#endif // IMAGESAVEANDREAD_H
