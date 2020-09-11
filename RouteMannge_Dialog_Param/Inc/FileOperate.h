
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

	// 获取本执行程序所在的路径
	std::string GetCurrentAppPath();


	// 判断路径是否存在
	bool IsPathExist(const std::string &strPath);

	//创建一个多层目录，如果存在就不创建
	//(strPath  合法: "D:\\abc\\me" 或 "me\\you" 或 ""; 
	//			不合法: "D:\\abc\\me\\" 或 "me\\you\\" 或 "\\")
	bool CreateMultiLevelPath(const std::string &strPath, bool bEveryone = false);

	
	//删除当前目录下所有文件及文件夹
	bool DeleteDirectory(const std::string &strDirectory);


	//拷贝文件夹：将strFromPath中的内容（不包含strFromPath），拷贝到strToPath中
	bool CopyFolder(const std::string strFromPath, const std::string strToPath);


    //重命名 F:\\Bin\\Model","F:\\Bin\\Model123" 表示将Model重命名为Model123
	bool ReNameFolder(const std::string  strFromPath, const std::string  strToPath);


	//浏览对话框,strInitPath限制路径   返回的文件夹全路径
	bool BrowseFolder(const std::string strInitPath, std::string &strBrownPath);

	//删除某文件夹下，年月及之前的文件夹，
	bool DeleteFolderByYearMonDay(const std::string  strFolder, int iYear, int iMonth, int iDay);
	///////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//判断文件是否存在
	bool IsFileExist(const std::string &strFileName);


	bool DeleteFilePath(const std::string & strFilePath);


	//strExt = exe或者bmp  或者*
	bool FileSelect(const std::string strInitPath, const std::string strExt, std::string &strFilePath);


	//strExt = exe或者bmp  或者*
	bool FileSave(const std::string strInitPath, const std::string strExt, std::string &strFilePath);

	double MyReadPrivateProfileDouble(const std::string strApp, const std::string strKey, double dbDefault, const std::string strFilePath);
	int MyReadPrivateProfileInt(const std::string strApp, const std::string strKey, int iDefault, const std::string strFilePath);
	std::string MyReadPrivateProfileString(const std::string strApp, const std::string strKey, const std::string strDefault, const std::string strFilePath);
	bool MyWritePrivateProfileString(const std::string strApp, const std::string strKey, const std::string strContent,const std::string strFilePath);
	bool MyWritePrivateProfileInt(const std::string strApp, const std::string strKey, int iContent, const std::string strFilePath);
	bool MyWritePrivateProfileDouble(const std::string strApp, const std::string strKey, double dbContent, const std::string strFilePath);
   
   //////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	// 写系统操作日志
	bool WriteOperateLog(const std::string& strFilePath, const std::string& strBatch, const std::string& strSession, const std::string& str);


	// 写系统异常日志
	bool WriteExceptionLog(const std::string& strFilePath, const std::string& strBatch, const std::string& strSession, const std::string& str);

	//
	bool WriteLog(const std::string& strLogFilePath, const std::string& strContent);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//获得内存剩余容量函数，单位：M
	long GetSurplusMemorySize();

	//获得当前硬盘分区的剩余容量，（返回-1表示失败单位：M） （输入 D:   E:）
	long GetSurplusCurrentPartitionSize(const std::string strDrivePath);


	//杀死当前进程
	void ShutCurrentProgcess(); 

	//////////////////////////////////////////////////////////////////////////


        //写调试信息
        //用法 PrintfDebugLog("[PCB]%d starts to run\n", 1);
        void PrintfDebugLog(const char * strOutputString, ...);
        void PrintfDebugLog(const std::string &strOutputString);

        //////////////////////////////////////////////////////////////////////////
        //要求nTextLen = nOutLen；
        bool Encrypt(const char szText[], unsigned int nTextLen, char szOutString[], unsigned int nOutLen);
        bool Decrypt(const char szText[], unsigned int nTextLen, char szOutString[], unsigned int nOutLen);

        //////////////////////////////////////////////////////////////////////////
        //与图形图像文件相关的
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
