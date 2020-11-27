
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


int main()
{

    string File_Directory1 = "E://experimental_Data//SUBWAY//data_20201119//cam//dat//8";   //�ļ���Ŀ¼1

    string FileType = ".dat";    // ��Ҫ���ҵ��ļ�����

    vector<string>FilesName1;    //����ļ���������

    getFilesName111(File_Directory1, FileType, FilesName1);   // �궨����ͼ���ļ���·��

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