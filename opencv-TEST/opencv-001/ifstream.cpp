
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

    _finddata_t c_file;   // ����ļ����Ľṹ��

    long long hFile;//http://www.mamicode.com/info-detail-2204262.html
    hFile = _findfirst(buffer.c_str(), &c_file);   //�ҵ�һ���ļ���

    if (hFile == -1L)   // ����ļ���Ŀ¼�´�����Ҫ���ҵ��ļ�
        printf("No %s files in current directory!\n", FileType);
    else
    {
        string fullFilePath;
        do
        {
            fullFilePath.clear();

            //����
            fullFilePath = File_Directory + "\\" + c_file.name;

            FilesName.push_back(fullFilePath);

        } while (_findnext(hFile, &c_file) == 0);  //����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1  
        _findclose(hFile);
    }
}


int main1111111()
{

    //string File_Directory1 = "E://experimental_Data//SUBWAY//data_20201119//cam//dat//8";   //�ļ���Ŀ¼1

    //string FileType = ".dat";    // ��Ҫ���ҵ��ļ�����

    //vector<string>FilesName1;    //����ļ���������

    //getFilesName111(File_Directory1, FileType, FilesName1);   // �궨����ͼ���ļ���·��

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
    std::ofstream fileOutput_1(fileName1.c_str());   // ���ļ�������������
    fileName1 = "E:\\experimental_Data\\SICK\\201215\\free_listen\\4000_2000_100000_2.txt";
    std::ofstream fileOutput_2(fileName1.c_str());   // ���ļ�������������

    
    //2D
    std::string fileName = "E:\\experimental_Data\\SICK\\201215\\free_listen\\4000_2000_100000.txt";
    std::ifstream fileInput(fileName.c_str());   // ���ļ�������������
    std::string lineStr;
    std::stringstream sstr;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    int i = 1;
    while (std::getline(fileInput, lineStr))    // ��ȡһ��
    {
        sstr << lineStr;                          // ����ȡ������ѹ�뵽 sstr
        sstr >> x >> y>>z;        //  ʹ��sringsream �������
        //std::cout << "line " << i << " " << x << " " << y << std::endl;
        i++;
        sstr.clear();          // this is important. ע�⽫stringsream������գ�����һֱΪ��һ��
        fileOutput_1 << x << std:: endl;
        fileOutput_2 << z << std::endl;
    }
    fileInput.close(); //�ر�������
    fileOutput_1.close(); //�ر�������
    fileOutput_2.close(); //�ر�������


	return 0;
}