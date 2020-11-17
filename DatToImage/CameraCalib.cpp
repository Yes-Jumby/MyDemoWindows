#include "ImageSaveAndRead.h"
int main1()
{
    int start = 1;
    int end = 13;
    std::string datpath = "C://imagesave//201109//1//";
    std::string inpath;
    std::string outpath = "C://imagesave//201109//2//";
    //buffer
    uchar *pBuffer = new uchar[2560*832];
    //image class
    CImageSaveAndRead m_ImageSaveAndRead;
    for(int i = start;i<=end;i++)
    {
        //if(i%5==0)
        {
            inpath = datpath+std::to_string(i)+".dat";
            qDebug()<<QString::fromStdString(inpath);
            qDebug()<<m_ImageSaveAndRead.readToImage(inpath,outpath,pBuffer);
        }

    }
    qDebug()<<end - start + 1;

    delete []pBuffer;
    pBuffer = nullptr;
    return 0;
}
