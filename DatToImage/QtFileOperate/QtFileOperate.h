
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

	// ��ȡ��ִ�г������ڵ�·��
    QString GetCurrentAppPath();


	// �ж�·���Ƿ����
    bool IsPathExist(QString strPath);

	//����һ�����Ŀ¼��������ھͲ�����
    bool CreateMultiLevelPath(QString strPath);

	
	//ɾ����ǰĿ¼�������ļ����ļ���
    bool DeleteDirectory(QString strPath);


    //������ F:\\Bin\\Model","F:\\Bin\\Model123" ��ʾ��Model������ΪModel123
    bool ReNameFolder(QString strFromPath, QString  strToPath);


	//����Ի���,strInitPath����·��   ���ص��ļ���ȫ·��
    bool BrowseFolder(QString strInitPath, QString &strBrownPath);

    //ɾ��ĳ�ļ����£����¼�֮ǰ���ļ��У����磺F:\Bin\Model\log    ���ļ��и�ʽ2018��08��
    bool DeleteFolderByYearMonDay(QString  strFolder, int iYear, int iMonth, int iDay);
    ///////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//�ж��ļ��Ƿ����
    bool IsFileExist(QString strFileFullPath);
    bool IsFileExist(std::string strFileFullPath);


    bool FileDelete(QString strFileFullPath);


	//strExt = exe����bmp  ����*
    bool FileBrowse(QString strInitPath, QString strExt, QString &strFileFullPath);


	//strExt = exe����bmp  ����*
    bool FileSave(QString strInitPath, QString strExt, QString &strFilePath);

    void GetAllFileFolder(QString dirPath, std::vector<QString> &folder);


private:
     QString m_strErrorInfo;
};



#endif // !define(FileOperate_h_)
