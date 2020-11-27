#include <QCoreApplication>
#include "QGetFileName.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString File_Directory = "E://experimental_Data//SUBWAY//data_20201119//cam//dat//8";   //文件夹目录1
    QString FileType = "*.dat";    // 需要查找的文件类型
    //qDebug()<<FileType.remove(0,1);
    vector<string> FilesName;    //存放文件名的容器
    CQGetFileName m_GetFileName;
    m_GetFileName.getFilesName(File_Directory,FileType , FilesName);
    for(int i=0; i<FilesName.size(); i++)
    {
        cout<<FilesName.at(i)<<endl;
    }

    m_GetFileName.getFilesPath(File_Directory,FileType , FilesName);
    for(int i=0; i<FilesName.size(); i++)
    {
        cout<<FilesName.at(i)<<endl;
    }

    return a.exec();
}
