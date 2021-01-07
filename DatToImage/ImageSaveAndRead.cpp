#include "ImageSaveAndRead.h"
#include "cloud.h"
#include "QConfig/KDConfig.h"
CImageSaveAndRead::CImageSaveAndRead():m_id(1000000000000000000)
{
    CKDConfig::setParameterFile("D:\\Demo\\MyDemoWindows\\DatToImage\\QConfig\\SystemConfig.ini");
    m_RMat[1]= CKDConfig::getValue<float>("r11");
    m_RMat[2]= CKDConfig::getValue<float>("r12");
    m_RMat[3]= CKDConfig::getValue<float>("r13");
    m_RMat[4]= CKDConfig::getValue<float>("r21");
    m_RMat[5]= CKDConfig::getValue<float>("r22");
    m_RMat[6]= CKDConfig::getValue<float>("r23");
    m_RMat[7]= CKDConfig::getValue<float>("r31");
    m_RMat[8]= CKDConfig::getValue<float>("r32");
    m_RMat[9]= CKDConfig::getValue<float>("r33");

    m_TMat[1]= CKDConfig::getValue<float>("t1");
    m_TMat[2]= CKDConfig::getValue<float>("t2");
    m_TMat[3]= CKDConfig::getValue<float>("t3");
    for(int i =1;i<=9;i++){
        qDebug()<<"CThreadDataForTrans::RMat:"<<m_RMat[i];
    }
    for(int i =1;i<=3;i++){
        qDebug()<<"CThreadDataForTrans::TMat:"<<m_TMat[i];
    }

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
    float x,y,z;//cloud
    float cx,cy,cz;//cloud
    for (int i = 0; i < cloud.rows; i++)
    {
        for (int j = 0; j < cloud.cols; j++)
        {
            idx = j + i*cloud.cols;
            x = j*cloud.dx+cloud.minx;;
            y = i*cloud.dy;
            z = pRange[idx];
            /**********/
            //x y z transform
            cx = m_RMat[1] * x +
                 m_RMat[2] * y +
                 m_RMat[3] * z +
                 m_TMat[1];
            cy = m_RMat[4] * x +
                 m_RMat[5] * y +
                 m_RMat[6] * z +
                 m_TMat[2];
            cz = m_RMat[7] * x +
                 m_RMat[8] * y +
                 m_RMat[9] * z +
                 m_TMat[3];
            pCloud[idx * 4] = cx;
            pCloud[idx * 4 + 1] = cy;
            pCloud[idx * 4 + 2] = cz;
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
bool CImageSaveAndRead::readbinToCloudNew(const std::string & path,const std::string &outpath,const std::string &dirname)
{
    //std::string infilePath = "E://experimental_Data//SICK//201230//Data//dat//1_ori//";
    int pos = outpath.find("dat_txt");
    std::string outTimeStampPath = outpath.substr(0, pos+8) + dirname+"_TimeStamp.txt";


    std::string outfilePath;

    uint64_t cols_;
    uint64_t rows_;
    uint64_t size_;
    double element_[3];

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
    mDataInput.read((char*)&cols_, sizeof(cols_));
    mDataInput.seekg(sizeof(cols_), mDataInput.beg);
    mDataInput.read((char*)&rows_, sizeof(rows_));
    size_ = cols_*rows_;

    std::cerr <<"cols::"<<cols_<< std::endl;
    std::cerr <<"rows_::"<<rows_<< std::endl;
    std::cerr <<"size_::"<<size_<< std::endl;

    uint64_t *pTimeStamp = new uint64_t[size_];
    float *pRange = new float[size_];
    unsigned char *pIntensity = new unsigned char[size_];

    mDataInput.seekg(sizeof(cols_) + sizeof(rows_), mDataInput.beg);
    mDataInput.read((char*)element_, 3 *sizeof(double));

    mDataInput.seekg(sizeof(cols_) + sizeof(rows_) + 3 *sizeof(double), mDataInput.beg);
    mDataInput.read((char*)pTimeStamp, rows_ *sizeof(uint64_t));

    mDataInput.seekg(sizeof(cols_) + sizeof(rows_)  + 3 *sizeof(double) + rows_ *sizeof(uint64_t), mDataInput.beg);
    mDataInput.read((char*)pRange, size_ *sizeof(float));

    mDataInput.seekg(sizeof(cols_) + sizeof(rows_) + + 3 *sizeof(double) + rows_ *sizeof(uint64_t)+ size_ * sizeof(float), mDataInput.beg);
    mDataInput.read((char*)pIntensity, size_ * sizeof(unsigned char));
    mDataInput.close();

//    for (int i = 0; i < 3; i++)
//    {
//        std::cerr <<"element_::"<<element_[i]<< std::endl;
//    }
//    for (int i = 0; i < rows_; i++)
//    {
//        std::cerr <<"pTimeStamp::"<<pTimeStamp[i]<< std::endl;
//    }
//    for (int i = 0; i < size_; i++)
//    {
//        std::cerr <<"pRange pIntensity::"<<pRange[i]<<"     "<<(int)pIntensity[i]<< std::endl;
//    }



    //cv::Mat range = cv::Mat(cloud.rows, cloud.cols, CV_32FC1, pRange);

    float * pCloudRange = pRange;
    unsigned char * pCloudIntensity = pIntensity;
    std::ofstream outTimeStampfile;
    outTimeStampfile.open(outTimeStampPath, std::ios::app);
    if (!outTimeStampfile)
    {
        return false;
    }
    outTimeStampfile.setf(std::ios::fixed, std::ios::floatfield);
    outTimeStampfile.precision(3);

    std::ofstream outfile;
    for(int ii = 0;ii<rows_;ii++)
    {
        if(ii%1000==0) {
            std::cerr <<"rows::"<<ii<< std::endl;
        }
        pCloudRange = pRange + ii*cols_;
        pCloudIntensity = pIntensity + ii*cols_;
        outfilePath = outpath + std::to_string(pTimeStamp[ii]) + ".txt";
        outTimeStampfile << pTimeStamp[ii] << "\n";

        outfile.open(outfilePath, std::ios::ate);
        if (!outfile)
        {
            return false;
        }
        outfile.setf(std::ios::fixed, std::ios::floatfield);
        outfile.precision(3);
        int idx = 0;
        float x,y,z;//cloud
        float cx,cy,cz;//cloud
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                idx = j + i*cols_;
                x = j*element_[0]+element_[2];;
                y = 0.0/*i*element_[1]*/;
                z = pCloudRange[idx];
                /**********/
                //x y z transform
                cx = m_RMat[1] * x +
                     m_RMat[2] * y +
                     m_RMat[3] * z +
                     m_TMat[1];
                cy = m_RMat[4] * x +
                     m_RMat[5] * y +
                     m_RMat[6] * z +
                     m_TMat[2];
                cz = m_RMat[7] * x +
                     m_RMat[8] * y +
                     m_RMat[9] * z +
                     m_TMat[3];
                outfile << cx << " " << cy << " " << cz << " " << (float)pCloudIntensity[idx] << "\n";
            }
        }
        outfile.close();
    }
    outTimeStampfile.close();


    delete []pRange;
    delete []pIntensity;
    delete []pTimeStamp;
    return true;

}
void CImageSaveAndRead::getFilesName(string &File_Directory, string &FileType, vector<string>&FilesName)
{
    string buffer = File_Directory + "\\*" + FileType;

    _finddata_t c_file;   // 存放文件名的结构体

    long long hFile;//http://www.mamicode.com/info-detail-2204262.html
    hFile = _findfirst(buffer.c_str(), &c_file);   //找第一个文件命

    if (hFile == -1L)   // 检查文件夹目录下存在需要查找的文件
        printf("No %s files in current directory!\n", FileType);
    else
    {
        string fullFilePath;
        do
        {
            fullFilePath.clear();

            //名字
            fullFilePath = File_Directory + "\\" + c_file.name;

            FilesName.push_back(fullFilePath);

        } while (_findnext(hFile, &c_file) == 0);  //如果找到下个文件的名字成功的话就返回0,否则返回-1
        _findclose(hFile);
    }
}
bool CImageSaveAndRead::readdatToCloud(const QString &path)
{
    std::vector<QString> folder;

    m_FileOperate.GetAllFileFolder(path,folder);
    cout<<"======Folder count:"<<folder.size()<<endl;
    for(int i =0;i<folder.size();i++)
    {
        cout<<i<<"::"<<folder.at(i).toStdString()<<" Start"<<endl;
        string File_Directory = folder.at(i).toStdString();   //文件夹目录1
        int pos = File_Directory.find("dat");
        std::string outParentPath = File_Directory.substr(0, pos) + "dat_txt";
        string dirname = File_Directory.substr(pos+4, File_Directory.size());

        string File_Directory_text = outParentPath +"/"+dirname;
        cout<<File_Directory_text<<endl;

        m_FileOperate.CreateMultiLevelPath(QString::fromStdString(File_Directory_text));
        string outPath = File_Directory_text + "/";

        string FileType = ".dat";    // 需要查找的文件类型
        vector<string>FilesName1;    //存放文件名的容器
        getFilesName(File_Directory, FileType, FilesName1);   // 标定所用图像文件的路径
        for(int i =0;i<FilesName1.size();i++)
        {
            cout<<i+1<<"start!"<<endl;
            readbinToCloudNew(FilesName1.at(i),outPath,dirname);
            cout<<i+1<<"finished!"<<endl;
            cout<<endl;
        }
        cout<<i<<"::"<<folder.at(i).toStdString()<<" End"<<endl;
        cout<<endl;
    }
    cout<<"======transfer Success!"<<endl;
}
