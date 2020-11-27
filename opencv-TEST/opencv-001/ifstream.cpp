
#include <iostream>
#include <fstream> 
#include <io.h>  
#include <string>  
#include<vector>
#include "readAndWriteDat.h"
#include "SpendTime.h"
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

    string File_Directory1 = "E://experimental_Data//SUBWAY//data_20201119//cam//dat//8";   //文件夹目录1

    string FileType = ".dat";    // 需要查找的文件类型

    vector<string>FilesName1;    //存放文件名的容器

    getFilesName111(File_Directory1, FileType, FilesName1);   // 标定所用图像文件的路径

    CReadAndWriteDat ReadAndWriteDat;
    CSpendTime SpendTime;
    for(int i =0;i<FilesName1.size();i++)
    ReadAndWriteDat.readbinToCloud(FilesName1.at(i));
    //int size = 1000000;
    //SpendTime.Start();
    //ReadAndWriteDat.writeToCloudslow("E://temp//slow.txt", size);

    //cout << SpendTime.GetTimeInterval() << endl;;

    //SpendTime.Start();
    //ReadAndWriteDat.writeToCloudfast("E://temp//fast.txt", size);
    cout << SpendTime.GetTimeInterval() << endl;;
	return 0;
}