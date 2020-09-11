#include <QImage>
#include <fstream>
#include <QDebug>
#include <string>
long long id = 1000000000000000000;
bool SaveToImage(std::string path,void*pBuffer,int width=2560,int height=832) {
//    qDebug()<<QString::fromStdString(path);
//    qDebug()<<width;
//    qDebug()<<height;
    std::string savepath = path +std::to_string(id)+".png";
    id=id+250000000;
    qDebug()<<QString::fromStdString(savepath);
    return QImage(static_cast<uchar*>(pBuffer),
           static_cast<int>(width),
           static_cast<int>(height),
           QImage::Format::Format_Grayscale8).save(QString::fromStdString(savepath),"PNG",100);

}
bool readToImage(const std::string &path,const std::string &outpath,uchar *pBuffer,int size_ = 2560*832)
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
int main()
{
    int start = 757;
    int end = 879;
    std::string datpath = "C://imagesave//4HZ//5//";
    std::string inpath;
    std::string outpath = "C://imagesave//PNG1//5//";
    //buffer
    uchar *pBuffer = new uchar[2560*832];

    for(int i = start;i<=end;i++)
    {
        if(i%5==0)
        {
            inpath = datpath+std::to_string(i)+".dat";
            qDebug()<<QString::fromStdString(inpath);
            qDebug()<<readToImage(inpath,outpath,pBuffer);
        }

    }
    qDebug()<<end - start + 1;

    delete []pBuffer;
    pBuffer = nullptr;
    return 0;
}
