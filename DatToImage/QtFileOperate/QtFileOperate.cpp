
#include "QtFileOperate.h"
#include <QCoreApplication>
#include <windows.h>
#include <QDir>
#include "QFileDialog"


/*
#include <Shlwapi.h>
#pragma  comment(lib, "shlwapi.lib")

#include <shellapi.h>

#include <ShlObj.h>


#include <io.h>

#include <afxmt.h>


*/

CQtFileOperate::CQtFileOperate()
{

}
CQtFileOperate::~CQtFileOperate()
{

}
QString CQtFileOperate::GetLastError()
{
    return 	m_strErrorInfo;
}

// 获取本执行程序所在的路径
QString CQtFileOperate::GetCurrentAppPath()
{

    return QCoreApplication::applicationDirPath();
}


//判断路径是否存在
bool CQtFileOperate::IsPathExist(QString strPath)
{
    if(strPath.isEmpty()||strPath.isNull())
    {
        return false;
    }
    QDir dir(strPath);
    if (dir.exists())
	{
		return true;
	}
	else
	{
		return false;
	}
}



//创建一个多层目录，如果存在就不创建
//(strPath  合法: "D:\\abc\\me" 或 "me\\you" 或 ""; 
//			不合法: "D:\\abc\\me\\" 或 "me\\you\\" 或 "\\")
bool CQtFileOperate::CreateMultiLevelPath(QString strPath)
{
    QDir dir;
    return dir.mkpath(strPath);//创建多级目录
}

//
bool CQtFileOperate::DeleteDirectory(QString strPath)
{

    if (strPath.isEmpty()||strPath.isNull())
	{
        m_strErrorInfo = "strPath Empty or Null";
		return false;
	}
    if(!IsPathExist(strPath))
    {
        return true;
    }


    QDir dir(strPath);

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            DeleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());

}

bool CQtFileOperate::ReNameFolder(QString strFromPath, QString strToPath)
{
    if(!IsPathExist(strFromPath))
    {
        return false;
    }

    if(IsPathExist(strToPath))
    {
        return false;
    }

    QDir dir;

    return dir.rename(strFromPath,strToPath);
}

//浏览对话框

bool CQtFileOperate::BrowseFolder(QString strInitPath, QString &strBrownPath)
{

    QString dir = QFileDialog::getExistingDirectory(0,"选择目录",strInitPath,QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);

    if(IsPathExist(dir))
    {
        strBrownPath = dir;
        return true;
    }
    else
    {
        return false;
    }


}

bool CQtFileOperate::DeleteFolderByYearMonDay(QString strFolder, int iYear, int iMonth, int iDay)
{
    QDir dir(strFolder);

    QStringList ListPath;
    if(dir.exists())
    {
        dir.setFilter(QDir::Dirs);

        QFileInfoList list = dir.entryInfoList();

        for(int j = 0;j< list.size();j++)
        {
            QFileInfo fileInfo = list.at(j);
            if (fileInfo.fileName()=="."|fileInfo.fileName()=="..")

            {

                continue;

            }
            if(fileInfo.isDir())
            {
                QString filename = fileInfo.fileName();
                QString filepath = fileInfo.filePath();

                int itmpYear = filename.mid(0,4).toInt();
                int itmpMonth = filename.mid(5,2).toInt();
                if (itmpYear < iYear)
                {
                    ListPath.push_back(filepath);

                }
                else if (itmpYear == iYear && itmpMonth <= iMonth)
                {
                    ListPath.push_back(filepath);
                }
            }
        }

    }

    for(int i = 0;i< ListPath.size();i++)
    {
         DeleteDirectory(ListPath.at(i));

    }

    return true;


}


//判断文件是否存在
bool CQtFileOperate::IsFileExist(QString strFileFullPath)
{

    if(strFileFullPath.isEmpty() | strFileFullPath.isNull())
    {
        return false;
    }
    QFileInfo fileInfo(strFileFullPath);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;



    return true;
}

bool CQtFileOperate::IsFileExist(std::string strFileFullPath)
{
    QString str = QString::fromStdString(strFileFullPath);
    return IsFileExist(str);
}

bool CQtFileOperate::FileDelete(QString strFileFullPath)
{

    if(IsFileExist(strFileFullPath))
    {
        QFile File(strFileFullPath);
        if(File.exists())
        {
            return File.remove();
        }
    }


	return true;
}

//strExt = exe或者bmp  或者*
bool CQtFileOperate::FileBrowse(QString strInitPath, QString strExt, QString &strFileFullPath)
{
    QString str = "*."+strExt;
    QString FileName = QFileDialog::getOpenFileName(0,"选择文件",strInitPath,str);

    if(IsFileExist(FileName))
    {
        strFileFullPath = FileName;
        return true;
    }
    else
    {
        return false;
    }

}

bool CQtFileOperate::FileSave(QString strInitPath, QString strExt, QString &strFilePath)
{
    QString str = "*."+strExt;

    QString FileName = QFileDialog::getSaveFileName(0,"Save as",strInitPath,str);

    if(FileName.isEmpty() || FileName.isNull())
    {
        return false;
    }
    else
    {
        strFilePath = FileName;

        return true;
    }


}
void CQtFileOperate::GetAllFileFolder(QString dirPath, std::vector<QString> &folder)
{

    QDir dir(dirPath);

    dir.setFilter(QDir::Dirs);

    foreach(QFileInfo fullDir, dir.entryInfoList())

    {

        if(fullDir.fileName() == "." || fullDir.fileName() == "..") continue;

        folder.push_back(fullDir.absoluteFilePath());

        this->GetAllFileFolder(fullDir.absoluteFilePath(),  folder);

    }

}
