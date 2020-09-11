
#if !defined(FileOperate_h_)
#define FileOperate_h_

#include <string>

#define WIDTH_BYTES(bits) (((bits) + 31) / 32 * 4)


#if defined(FILEOPERATE_LIBRARY)
#  define FILEOPERATESHARED_EXPORT __declspec(dllexport)
#else
#  define FILEOPERATESHARED_EXPORT __declspec(dllimport)
#endif

class FILEOPERATESHARED_EXPORT CFileOperate
{
public:
	enum e_PlatType
	{
		eQTPlat = 0,
		eMFCPlat
	};
public:
	CFileOperate(e_PlatType ePlatType = eQTPlat);
	~CFileOperate();

	std::string GetLastError();

	// ��ȡ��ִ�г������ڵ�·��
	std::string GetCurrentAppPath();


	// �ж�·���Ƿ����
	bool IsPathExist(const std::string &strPath);

	//����һ�����Ŀ¼��������ھͲ�����
	//(strPath  �Ϸ�: "D:\\abc\\me" �� "me\\you" �� ""; 
	//			���Ϸ�: "D:\\abc\\me\\" �� "me\\you\\" �� "\\")
	bool CreateMultiLevelPath(const std::string &strPath, bool bEveryone = false);

	
	//ɾ����ǰĿ¼�������ļ����ļ���
	bool DeleteDirectory(const std::string &strDirectory);


	//�����ļ��У���strFromPath�е����ݣ�������strFromPath����������strToPath��
	bool CopyFolder(const std::string strFromPath, const std::string strToPath);


    //������ F:\\Bin\\Model","F:\\Bin\\Model123" ��ʾ��Model������ΪModel123
	bool ReNameFolder(const std::string  strFromPath, const std::string  strToPath);


	//����Ի���,strInitPath����·��   ���ص��ļ���ȫ·��
	bool BrowseFolder(const std::string strInitPath, std::string &strBrownPath);

	//ɾ��ĳ�ļ����£����¼�֮ǰ���ļ��У�
	bool DeleteFolderByYearMonDay(const std::string  strFolder, int iYear, int iMonth, int iDay);
	///////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//�ж��ļ��Ƿ����
	bool IsFileExist(const std::string &strFileName);


	bool DeleteFilePath(const std::string & strFilePath);


	//strExt = exe����bmp  ����*
	bool FileSelect(const std::string strInitPath, const std::string strExt, std::string &strFilePath);


	//strExt = exe����bmp  ����*
	bool FileSave(const std::string strInitPath, const std::string strExt, std::string &strFilePath);

	double MyReadPrivateProfileDouble(const std::string strApp, const std::string strKey, double dbDefault, const std::string strFilePath);
	int MyReadPrivateProfileInt(const std::string strApp, const std::string strKey, int iDefault, const std::string strFilePath);
	std::string MyReadPrivateProfileString(const std::string strApp, const std::string strKey, const std::string strDefault, const std::string strFilePath);
	bool MyWritePrivateProfileString(const std::string strApp, const std::string strKey, const std::string strContent,const std::string strFilePath);
	bool MyWritePrivateProfileInt(const std::string strApp, const std::string strKey, int iContent, const std::string strFilePath);
	bool MyWritePrivateProfileDouble(const std::string strApp, const std::string strKey, double dbContent, const std::string strFilePath);
   
   //////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	// дϵͳ������־
	bool WriteOperateLog(const std::string& strFilePath, const std::string& strBatch, const std::string& strSession, const std::string& str);


	// дϵͳ�쳣��־
	bool WriteExceptionLog(const std::string& strFilePath, const std::string& strBatch, const std::string& strSession, const std::string& str);

	//
	bool WriteLog(const std::string& strLogFilePath, const std::string& strContent);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//����ڴ�ʣ��������������λ��M
	long GetSurplusMemorySize();

	//��õ�ǰӲ�̷�����ʣ��������������-1��ʾʧ�ܵ�λ��M�� ������ D:   E:��
	long GetSurplusCurrentPartitionSize(const std::string strDrivePath);


	//ɱ����ǰ����
	void ShutCurrentProgcess(); 

	//////////////////////////////////////////////////////////////////////////


        //д������Ϣ
        //�÷� PrintfDebugLog("[PCB]%d starts to run\n", 1);
        void PrintfDebugLog(const char * strOutputString, ...);
        void PrintfDebugLog(const std::string &strOutputString);

        //////////////////////////////////////////////////////////////////////////
        //Ҫ��nTextLen = nOutLen��
        bool Encrypt(const char szText[], unsigned int nTextLen, char szOutString[], unsigned int nOutLen);
        bool Decrypt(const char szText[], unsigned int nTextLen, char szOutString[], unsigned int nOutLen);

        //////////////////////////////////////////////////////////////////////////
        //��ͼ��ͼ���ļ���ص�
        bool SaveDIBImageToBMPFile(const std::string& strFileName, const char* pImageBuff, long lImageWidth, long lImageHeight, long lImageBitCount);
        bool CutDIBImage(char *pDest, long xDest, long yDest, long lDestWidth, long lDestHeight, const char* pSrcImageBuff, long lSrcImageWidth, long lSrcImageHeight, long lSrcImageBitCount);
        bool CutPlaneRGBImage(char *pDest, long xDest, long yDest, long lDestWidth, long lDestHeight, const char* pSrcImageBuff, long lSrcImageWidth, long lSrcImageHeight);
        bool ConvertRGBToPlaneR_G_B(char *pDestImageBuffR, char *pDestImageBuffG, char *pDestImageBuffB,
                                    const char* pSrcImageBuff, long lSrcImageWidth, long lSrcImageHeight);
        bool ConvertPlaneR_G_BToRGB(char* pDestImageBuff, const char *pSrcImageBuffR, const char *pSrcImageBuffG, const char *pSrcImageBuffB,
                                    long lSrcImageWidth, long lSrcImageHeight);
        bool  ConvertRGBToPlaneRGB(char *pDestPlaneRGBBuff, const char* pSrcImageRGBBuff, long lSrcImageWidth, long lSrcImageHeight);
        bool  ConvertPlaneRGBToRGB(char* pDestImageRGBBuff, const char *pSrcPlaneRGBBuff, long lSrcImageWidth, long lSrcImageHeight);
	
private:
	 std::string m_strErrorInfo;
};



#endif // !define(FileOperate_h_)
