#include "ImageSaveAndRead.h"
int main1()
{
    int start = 344;
    int end = 474;
    std::string datpath = "C://imagesave//4HZ/9//";
    std::string inpath;
    std::string outpath = "C://imagesave//PNG1//9//";
    //buffer
    uchar *pBuffer = new uchar[2560*832];
    //image class
    CImageSaveAndRead m_ImageSaveAndRead;
    for(int i = start;i<=end;i++)
    {
        if(i%5==0)
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
