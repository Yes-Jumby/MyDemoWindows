
#include <iostream>
#include <fstream>
#include <io.h>
#include <string>
#include<vector>
#include "ImageSaveAndRead.h"
#include "QtFileOperate/QtFileOperate.h"
using namespace std;

void getFilesName111(string &File_Directory, string &FileType, vector<string>&FilesName)
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


int main()
{
//    std::string infilePath = "E://experimental_Data//SICK//201230//Data//dat//1_ori//";
//    int pos = infilePath.find("dat");
//    std::string outfilePath = infilePath.substr(0, pos+5) + "TimeStamp.txt";
//    cout<<outfilePath<<endl;
//    return 0;
//    CImageSaveAndRead m_ImageSaveAndRead;
//    string prepath = "E://experimental_Data//SUBWAY//data_20201225//cam//dat//";
//    string File_Directory1 = "E://experimental_Data//SUBWAY//data_20201225//cam//dat//7";   //文件夹目录1
//    for(int j =1;j<=14;j++)
//    {
//        File_Directory1 = prepath + to_string(j);
//        cout<<j<<" "<<File_Directory1<<endl;
//        string FileType = ".dat";    // 需要查找的文件类型
//        vector<string>FilesName1;    //存放文件名的容器
//        getFilesName111(File_Directory1, FileType, FilesName1);   // 标定所用图像文件的路径
//        for(int i =0;i<FilesName1.size();i++)
//        {
//            m_ImageSaveAndRead.readbinToCloud(FilesName1.at(i));
//            cout<<i+1<<"finished!"<<endl;
//        }
//    }
    //CQtFileOperate m_QtFileOperate;
    CImageSaveAndRead m_ImageSaveAndRead;
    QString inPath = "E:/experimental_Data/SICK/201231/4/Data/dat";
    m_ImageSaveAndRead.readdatToCloud(inPath);
    //std::vector<QString> folder;

//    m_QtFileOperate.GetAllFileFolder("E://experimental_Data//SICK//201231//4//Data//dat",folder);
//    for(int i =0;i<folder.size();i++)
//    {
//        cout<<i<<"::"<<folder.at(i).toStdString()<<" Start"<<endl;
//        string File_Directory = folder.at(i).toStdString();   //文件夹目录1
//        int pos = File_Directory.find("dat");
//        std::string outParentPath = File_Directory.substr(0, pos) + "dat_txt";
//        string dirname = File_Directory.substr(pos+5, File_Directory.size());

//        string File_Directory_text = outParentPath +"//"+dirname;
//        cout<<File_Directory_text<<endl;

//        m_QtFileOperate.CreateMultiLevelPath(QString::fromStdString(File_Directory_text));
//        string outPath = File_Directory_text + "/";

//        string FileType = ".dat";    // 需要查找的文件类型
//        vector<string>FilesName1;    //存放文件名的容器
//        getFilesName111(File_Directory, FileType, FilesName1);   // 标定所用图像文件的路径
//        for(int i =0;i<FilesName1.size();i++)
//        {
//            cout<<i+1<<"start!"<<endl;
//            m_ImageSaveAndRead.readbinToCloudNew(FilesName1.at(i),outPath,dirname);
//            cout<<i+1<<"finished!"<<endl;
//            cout<<endl;
//        }
//        cout<<i<<"::"<<folder.at(i).toStdString()<<" Start"<<endl;
//        cout<<endl;
//    }
    return 0;



    //m_ImageSaveAndRead.readbinToCloudNew("E://experimental_Data//SICK//201230//Data//dat","E://experimental_Data//");

    return 0;
}
