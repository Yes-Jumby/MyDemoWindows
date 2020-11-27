#include "QGetFileName.h"

CQGetFileName::CQGetFileName()
{

}
/*
@param File_Directory 为文件夹目录
@param FileType 为需要查找的文件类型
@param FilesName 为存放文件名的容器
*/
void CQGetFileName::getFilesName(const QString &File_Directory, const QString &FileType, vector<string>&FilesName)
{
    FilesName.clear();
    QDir dir(File_Directory);
    if(!dir.exists()) {
        cout<<"dir not exists"<<endl;
        return ;
    }


    //查看路径中后缀为.cfg格式的文件
    QStringList filters;
    filters<<FileType;
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

    //统计cfg格式的文件个数
    int dir_count = dir.count();
    if(dir_count <= 0)
    {
        cout<<"dir_count <= 0"<<endl;
    }
    cout<<" total count:"<<dir_count<<endl;


    QString file_name;
    QString remove_ = FileType;
            remove_.remove(0,1);
    for(int i=0; i < dir_count; i++)
    {
        file_name = dir[i];  //文件名称
        file_name.remove(remove_);
        FilesName.push_back(file_name.toStdString());
    }
}
void CQGetFileName::getFilesPath(const QString &File_Directory, const QString &FileType, vector<string>&FilesPath)
{
    FilesPath.clear();
    QDir dir(File_Directory);
    if(!dir.exists()) {
        cout<<"dir not exists"<<endl;
        return ;
    }


    //查看路径中后缀为.cfg格式的文件
    QStringList filters;
    filters<<FileType;
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

    //统计cfg格式的文件个数
    int dir_count = dir.count();
    if(dir_count <= 0)
    {
        cout<<"dir_count <= 0"<<endl;
    }
    cout<<" total count:"<<dir_count<<endl;

    QString file_name;
    for(int i=0; i < dir_count; i++)
    {
        file_name = dir[i];  //文件名称
        file_name = File_Directory + "//" + file_name;//absolute directory
        //cout<<file_name.toStdString()<<endl;
        FilesPath.push_back(file_name.toStdString());
    }
}
