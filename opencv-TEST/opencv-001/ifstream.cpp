
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


int main1111111()
{

    //string File_Directory1 = "E://experimental_Data//SUBWAY//data_20201119//cam//dat//8";   //文件夹目录1

    //string FileType = ".dat";    // 需要查找的文件类型

    //vector<string>FilesName1;    //存放文件名的容器

    //getFilesName111(File_Directory1, FileType, FilesName1);   // 标定所用图像文件的路径

    //CReadAndWriteDat ReadAndWriteDat;
    //CSpendTime SpendTime;
    //for(int i =0;i<FilesName1.size();i++)
    //ReadAndWriteDat.readbinToCloud(FilesName1.at(i));
    ////int size = 1000000;
    ////SpendTime.Start();
    ////ReadAndWriteDat.writeToCloudslow("E://temp//slow.txt", size);

    ////cout << SpendTime.GetTimeInterval() << endl;;

    ////SpendTime.Start();
    ////ReadAndWriteDat.writeToCloudfast("E://temp//fast.txt", size);
    //cout << SpendTime.GetTimeInterval() << endl;;


    //3D
    std::string fileName1 = "E:\\experimental_Data\\SICK\\201215\\free_listen\\4000_2000_100000_1.txt";
    std::ofstream fileOutput_1(fileName1.c_str());   // 打开文件，建立数据流
    fileName1 = "E:\\experimental_Data\\SICK\\201215\\free_listen\\4000_2000_100000_2.txt";
    std::ofstream fileOutput_2(fileName1.c_str());   // 打开文件，建立数据流

    
    //2D
    std::string fileName = "E:\\experimental_Data\\SICK\\201215\\free_listen\\4000_2000_100000.txt";
    std::ifstream fileInput(fileName.c_str());   // 打开文件，建立数据流
    std::string lineStr;
    std::stringstream sstr;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    int i = 1;
    while (std::getline(fileInput, lineStr))    // 读取一行
    {
        sstr << lineStr;                          // 将读取的数据压入到 sstr
        sstr >> x >> y>>z;        //  使用sringsream 拆分数据
        //std::cout << "line " << i << " " << x << " " << y << std::endl;
        i++;
        sstr.clear();          // this is important. 注意将stringsream对象清空，否则一直为第一行
        fileOutput_1 << x << std:: endl;
        fileOutput_2 << z << std::endl;
    }
    fileInput.close(); //关闭数据流
    fileOutput_1.close(); //关闭数据流
    fileOutput_2.close(); //关闭数据流


	return 0;
}