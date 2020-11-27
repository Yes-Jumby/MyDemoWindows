#ifndef QGETFILENAME_H
#define QGETFILENAME_H
#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <vector>
using namespace std;

class CQGetFileName
{
public:
    CQGetFileName();
    /*
    @param File_Directory 为文件夹目录
    @param FileType 为需要查找的文件类型
    @param FilesName 为存放文件名的容器 //name without suffix
    */
    void getFilesName(const QString &File_Directory,const  QString &FileType, vector<string>&FilesName);
    /*
    @param File_Directory 为文件夹目录
    @param FileType 为需要查找的文件类型
    @param FilesName 为存放文件名的容器 //absolute directory
    */
    void getFilesPath(const QString &File_Directory, const QString &FileType, vector<string>&FilesPath);
};

#endif // QGETFILENAME_H
