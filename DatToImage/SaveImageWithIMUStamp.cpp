#include "ImageSaveAndRead.h"
#include <QFile>
int main()
{
    //time stamp
    QVector<long long> timestamp;
    QFile file("C:/imagesave/times3.dat");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
        QTextStream in(&file);  //用文件构造流
        while((line = in.readLine()).size()>0)//字符串有内容
        {
            timestamp.push_back(line.toLongLong());
        }
    }
    else
    {
        qDebug()<<"open file failed!";
    }
    file.close();

    qDebug()<<"timestamp count"<<timestamp.size();
//    return 1;
    //data files
    int start = 3428;
    int end = 4043;
    int image_count = end -start+1;
    qDebug()<<"image count"<<image_count;


    //judge if return
    if(image_count>timestamp.size()) {
        qDebug()<<"there is too much imgs!!!plz check again";
        return 1;
    }
    std::string datpath = "C://imagesave//4HZ/13//";
    std::string inpath;
    std::string outpath = "C://imagesave//PNG1//13//";
    //buffer
    uchar *pBuffer = new uchar[2560*832];
    //image class
    CImageSaveAndRead m_ImageSaveAndRead;
    for(int i = start;i<=end;i++)
    {
        if(true)
        {
            inpath = datpath+std::to_string(i)+".dat";
            qDebug()<<QString::fromStdString(inpath);
            qDebug()<<m_ImageSaveAndRead.readToImage_IMU(inpath,outpath,timestamp.at(i-start),pBuffer);
        }

    }

    delete []pBuffer;
    pBuffer = nullptr;
    return 0;
}
