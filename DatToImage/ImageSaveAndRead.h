#ifndef IMAGESAVEANDREAD_H
#define IMAGESAVEANDREAD_H
#include <QVector>
#include <QImage>
#include <QDebug>
#include <string>
#include <fstream>
#include <iostream>
#include <io.h>
#include <QtFileOperate/QtFileOperate.h>
using namespace std;
class CImageSaveAndRead
{
public:
    CImageSaveAndRead();
    //rename with stamp of imu*****use in IMU_CALIBRATION
    bool readToImage_IMU(const std::string &path,const std::string &outpath,long long id,uchar *pBuffer,int size_ = 2560*832);
    //camera calib**********use in CAMERA_CALIBRATION
    bool readToImage(const std::string &path,const std::string &outpath,uchar *pBuffer,int size_ = 2560*832);
    //dat to cloud new********use in transfer dat saved by ARM to txt
    bool readdatToCloud(const QString &path);
private:
    //rename with stamp of imu
    bool SaveToImage_IMU(std::string path,long long id,void*pBuffer,int width=2560,int height=832);
    //camera calib
    bool SaveToImage(std::string path,void*pBuffer,int width=2560,int height=832);
    //dat to cloud
    bool readbinToCloud(const std::string &path);
    //dat to cloud new
    bool readbinToCloudNew(const std::string &path,const std::string &outpath,const std::string &dirname);
    //dat to cloud new
    void getFilesName(string &File_Directory, string &FileType, vector<string>&FilesName);
    long long m_id;
    float m_RMat[10];
    float m_TMat[4];
    CQtFileOperate m_FileOperate;
};

#endif // IMAGESAVEANDREAD_H
