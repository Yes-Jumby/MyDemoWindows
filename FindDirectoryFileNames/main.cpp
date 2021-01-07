#include <QCoreApplication>
#include "QGetFileName.h"
#include <QDebug>
#include <fstream>
#include <streambuf>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



//    QString File_Directory = "E://experimental_Data//SICK//201217//free_listen";   //文件夹目录1

//    QString strnumber = File_Directory;
//    strnumber.remove(0,strnumber.lastIndexOf("//")+2);

//    qDebug()<<File_Directory;
//    QString FileType = "*.txt";    // 需要查找的文件类型
//    //qDebug()<<FileType.remove(0,1);
//    vector<string> FilesName;    //存放文件名的容器
//    CQGetFileName m_GetFileName;
//    m_GetFileName.getFilesName(File_Directory,FileType , FilesName);

//    std::string outname = strnumber.toStdString() +"_timestamp.txt";

//    File_Directory.truncate(File_Directory.lastIndexOf("//"));
//    std::string outpath = File_Directory.toStdString() + "//"+outname;
//    std::ofstream outfile;

//    outfile.open(outpath.c_str(), std::ios::ate | std::ios::binary);
//    if (!outfile)
//    {
//        return false;
//    }

//    for(int i=0; i<FilesName.size(); i++)
//    {
//        cout<< i << " " <<FilesName.at(i)<<endl;
//        outfile << i << " " << FilesName.at(i) << "\n";
//    }
//    cout<<"Total Size:" <<FilesName.size()<<endl;
//    outfile.close();

    QString File_Directory = "E://experimental_Data//SICK//201217//free_listen";   //文件夹目录1

    QString strnumber = File_Directory;
    strnumber.remove(0,strnumber.lastIndexOf("//")+2);

    qDebug()<<File_Directory;
    QString FileType = "*.txt";    // 需要查找的文件类型
    //qDebug()<<FileType.remove(0,1);
    vector<string> FilesName;    //存放文件名的容器
    CQGetFileName m_GetFileName;
    m_GetFileName.getFilesPath(File_Directory,FileType , FilesName);

    std::string outname = strnumber.toStdString() +"_timestamp.txt";

    File_Directory.truncate(File_Directory.lastIndexOf("//"));
    std::string outpath = File_Directory.toStdString() + "//"+outname;
    std::ofstream outfile;

    outfile.open(outpath.c_str(), std::ios::ate | std::ios::binary);
    if (!outfile)
    {
        return false;
    }

    for(int i=0; i<FilesName.size(); i++)
    {
        cout<< i << " " <<FilesName.at(i)<<endl;
        outfile << i << " " << FilesName.at(i) << "\n";
    }
    cout<<"Total Size:" <<FilesName.size()<<endl;
    outfile.close();
    return a.exec();
}
