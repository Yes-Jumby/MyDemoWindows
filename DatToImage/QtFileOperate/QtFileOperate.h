
#if !defined(QTFILEOPERATE_H)
#define QTFILEOPERATE_H

#include <QString>
#include <vector>
#define WIDTH_BYTES(bits) (((bits) + 31) / 32 * 4)
#pragma execution_character_set("utf-8")

class CQtFileOperate
{

public:
    CQtFileOperate();
    ~CQtFileOperate();

    QString GetLastError();

	// 获取本执行程序所在的路径
    QString GetCurrentAppPath();


	// 判断路径是否存在
    bool IsPathExist(QString strPath);

	//创建一个多层目录，如果存在就不创建
    bool CreateMultiLevelPath(QString strPath);

	
	//删除当前目录下所有文件及文件夹
    bool DeleteDirectory(QString strPath);


    //重命名 F:\\Bin\\Model","F:\\Bin\\Model123" 表示将Model重命名为Model123
    bool ReNameFolder(QString strFromPath, QString  strToPath);


	//浏览对话框,strInitPath限制路径   返回的文件夹全路径
    bool BrowseFolder(QString strInitPath, QString &strBrownPath);

    //删除某文件夹下，年月及之前的文件夹，例如：F:\Bin\Model\log    子文件夹格式2018年08月
    bool DeleteFolderByYearMonDay(QString  strFolder, int iYear, int iMonth, int iDay);
    ///////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//判断文件是否存在
    bool IsFileExist(QString strFileFullPath);
    bool IsFileExist(std::string strFileFullPath);


    bool FileDelete(QString strFileFullPath);


	//strExt = exe或者bmp  或者*
    bool FileBrowse(QString strInitPath, QString strExt, QString &strFileFullPath);


	//strExt = exe或者bmp  或者*
    bool FileSave(QString strInitPath, QString strExt, QString &strFilePath);

    void GetAllFileFolder(QString dirPath, std::vector<QString> &folder);


private:
     QString m_strErrorInfo;
};



#endif // !define(FileOperate_h_)
