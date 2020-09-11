#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <string>
#include <vector>

//UI参数
struct s_UIParamInfo
{
    int iUIFullScreenMode;  //0：全屏模式  1：最大化模式
    int iMapOrRealMode;     //0：Map模式  1：实时图模式。
    s_UIParamInfo()
    {
        iUIFullScreenMode = 0;
        iMapOrRealMode = 0;
    }
};

//错误参数
struct s_SysConfigErrInfo
{
    int iErrorCode;	//错误代码（0：正常）
    int iErrorGrade; // 报警级别 0:操作 1：提示 2：报警 3错误， 4：异常
    std::string strErrorDes;	//错误描述
    std::string strErrorMark;		//附加信息


};

//系统参数
struct s_ConfigSystem
{
    int iClientType; //计算机类型 0：单机 1：前端 2：服务器
    int iSystemInspectType; //1：手机全检
    int iComputerNO;  //计算机编号
    int iMachineNo;   //机器编号
    std::string strMachineName;  //机器名称

    s_ConfigSystem()
    {
        iClientType = 0;
        iSystemInspectType = 0;
        iComputerNO=0;
        iMachineNo = 0;
        strMachineName = "";
    }

};



//控制参数
struct s_ConfigControl
{
    bool bEnableShowImage; //是否实时显示图像
    bool bEnableShowInfo;  //是否显示检测信息
    bool bDefaultCheck;    //是否默认开检
    bool bEnableSaveLog;   //是否保存日志

    s_ConfigControl()
    {
        bEnableShowImage = true;
        bEnableShowInfo = true;
        bDefaultCheck = false;
        bEnableSaveLog  =true;
    }

};

//批号参数
struct s_ConfigBatchNo
{
    int iBatchGenerateType;  //批号产生方式 0：手动生成 1：按日期自动生成
    int iLastGenerateYear;   //批号生成年份
    int iLastGenerateMon;    //批号生成月份
    int iLastGenerateDay;    //批号生成日
    std::string strLastBatchNo;  //批号名称
    int iCheckCount; //检测计数
    int iErrorCount; //错误计数
    int iProductCodeGenerateType; //产品号生成方式 0：手动条码枪  1：按检测计数
    int iBarCodeLength;  //条码长度

    s_ConfigBatchNo()
    {
        iBatchGenerateType = 0;
        iLastGenerateYear= 0;
        iLastGenerateMon= 0;
        iLastGenerateDay = 0;
        strLastBatchNo = "Default";
        iCheckCount = 0;
        iErrorCount = 0;
        iProductCodeGenerateType = 0;
        iBarCodeLength = 12;
    }
};

//模板参数
struct s_ConfigModelInfo
{
    std::string strModelPath;  //模板名称
    std::string strPublicPath;//公共路径
    std::string strLastModelName;  //模板名称
    s_ConfigModelInfo()
    {
        strModelPath = "";
        strPublicPath = "";
        strLastModelName = "";
    }
};

//网络参数
struct s_ConfigNet
{
    bool bConnectNet;  //是否使用网络
    std::string strServerIP; //网络IP
    int iServerPort;   //网络端口

    s_ConfigNet()
    {
        bConnectNet = false;
        strServerIP = "127.0.0.1";
        iServerPort = 8000;
    }
};

//工位参数
struct s_ConfigCamera
{
    int iCameraSelfNo;  //自定义采集编号
    std::string strCameraSelfName;  //自定义采集名称

    int iCamaraNo;  //相机序号
    std::string strCameraMark; //相机标识
    std::string strCameraInitFile; //采集设备初始化文件

    int iCameraBrand; //相机品牌 0：模拟 1：Ds 2：chromens
    int iCameraType;  //相机类型 0：面阵 1：线阵 2：贝尔转换
	int iImageCopyMode;//内存拷贝方式 0：正常拷贝 1：垂直镜像 2：水平镜像
    double dbResolutionH; //横向分辨率，单位每像素毫米
    double dbResolutionV; //纵向分辨率，单位每像素毫米
    double dbResolutionD; //Z向分辨率，单位每像素毫米
    double dbOverLap; //两个相机的重叠区域，单位毫米
    s_ConfigCamera()
    {
        iCameraSelfNo = 0;
        strCameraSelfName = "";
        iCamaraNo = 0;
        strCameraMark = "";
        strCameraInitFile = "";
        iCameraBrand = 0;
        iCameraType = 0;
		iImageCopyMode = 0;
        dbResolutionH= 0.01;
        dbResolutionV= 0.01;
        dbResolutionD = 0.01;
        dbOverLap = 0;
    }
};

struct s_ConfigPage
{
    int iPageNo; //画面编号
    std::string strPageName; //画面名称
    s_ConfigPage()
    {
        iPageNo = 0;
        strPageName = "Page";
    }

};

struct s_ConfigOneStation
{
    int iStationNo; //工位编号
    std::string strStationName; //工位名称
    int iInspectType; //检测类型
    int iInspectObject; //检测对象
    int iCameraListCount; //队列个数
    int iCameraCount; //相机个数
    int iPageCount;   //画面个数
    int iPageMode;    //画面方式
    std::vector<s_ConfigPage> vecConfigPage;
    std::vector<s_ConfigCamera> vecConfigCamera;

    s_ConfigOneStation()
    {
        iStationNo = 0;
        strStationName= "";
        iInspectType = 0;
        iInspectObject= 0;
        iCameraListCount = 3;
        iCameraCount= 0;
        iPageCount= 0;
        vecConfigPage.clear();
        vecConfigCamera.clear();
    }
    s_ConfigOneStation(const s_ConfigOneStation & sConfigOneStation)
    {
       iStationNo = sConfigOneStation.iStationNo;
       strStationName = sConfigOneStation.strStationName;
       iInspectType = sConfigOneStation.iInspectType;
       iInspectObject = sConfigOneStation.iInspectObject;
       iCameraListCount = sConfigOneStation.iCameraListCount;
       iCameraCount = sConfigOneStation.iCameraCount;
       vecConfigCamera.clear();
       for(int i = 0;i < sConfigOneStation.vecConfigCamera.size();i++)
       {
           vecConfigCamera.push_back(sConfigOneStation.vecConfigCamera.at(i));
       }

       iPageCount = sConfigOneStation.iPageCount;
       for(int i = 0;i < sConfigOneStation.vecConfigPage.size();i++)
       {
           vecConfigPage.push_back(sConfigOneStation.vecConfigPage.at(i));
       }
    }

    const s_ConfigOneStation& operator=(const s_ConfigOneStation &sConfigOneStation)
    {
        iStationNo = sConfigOneStation.iStationNo;
        strStationName = sConfigOneStation.strStationName;
        iInspectType = sConfigOneStation.iInspectType;
        iInspectObject = sConfigOneStation.iInspectObject;
        iCameraListCount = sConfigOneStation.iCameraListCount;
        iCameraCount = sConfigOneStation.iCameraCount;
        vecConfigCamera.clear();
        for(int i = 0;i < sConfigOneStation.vecConfigCamera.size();i++)
        {
            vecConfigCamera.push_back(sConfigOneStation.vecConfigCamera.at(i));
        }

        iPageCount = sConfigOneStation.iPageCount;
        for(int i = 0;i < sConfigOneStation.vecConfigPage.size();i++)
        {
            vecConfigPage.push_back(sConfigOneStation.vecConfigPage.at(i));
        }
        return *this;
    }

};

struct s_ConfigAllStation
{
    int iStationCount; //工位个数
    std::vector<s_ConfigOneStation> vecStation;
    s_ConfigAllStation()
    {
        iStationCount= 0;
        vecStation.clear();

    }

    s_ConfigAllStation(const s_ConfigAllStation& sConfigAllStation)
    {
        iStationCount = sConfigAllStation.iStationCount;
        vecStation.clear();
        for(int i = 0;i < sConfigAllStation.vecStation.size();i++)
        {
            vecStation.push_back(sConfigAllStation.vecStation.at(i));
        }
    }

    const s_ConfigAllStation& operator=(const s_ConfigAllStation &sConfigAllStation)
    {
        iStationCount = sConfigAllStation.iStationCount;
        vecStation.clear();
        for(int i = 0;i < sConfigAllStation.vecStation.size();i++)
        {
            vecStation.push_back(sConfigAllStation.vecStation.at(i));
        }
        return *this;
    }

};








//database
struct s_ConfigDatabase
{
    bool bEnableDataBase;
    int iDataBaseType;  //0：sqlserver 1：mysql 2:sqlLite
    std::string strDBHost;
    std::string strDBUserName;
    std::string strDBPassword;
    std::string strDBPort;
    bool bEnableAutoDelDB;
    int iDBReservedDay;
    int iLastDelYear;   //最后删除年份
    int iLastDelMon;    //最后删除月份
    int iLastDelDay;    //最后删除日

    s_ConfigDatabase()
    {
        bEnableDataBase = false;
        iDataBaseType = 0;
        strDBHost = "localhost";
        strDBUserName = "bozhon";
        strDBPassword = "bozhon";
        strDBPort = "3306";
        bEnableAutoDelDB = false;
        iDBReservedDay = 365;
        iLastDelYear = 0;
        iLastDelMon= 0;
        iLastDelDay = 0;

    }
};


//缺陷信息相关参数
struct s_ConfigErrorInfo
{
    bool bEnableSaveError;
    int iErrorMaxCount; //最大缺陷个数
    int iErrorMinSizeWidth; //最大宽度
    int iErrorMinSizeHeight;  //最大高度
    int iErrorMaxSizeWidth; //最大宽度
    int iErrorMaxSizeHeight;  //最大高度
    std::string strErrorSavePath;  //错误路径

    s_ConfigErrorInfo()
    {
        bEnableSaveError = false;
        iErrorMaxCount = 10;
        iErrorMinSizeWidth = 200;
        iErrorMinSizeHeight = 200;
        iErrorMaxSizeWidth = 200;
        iErrorMaxSizeHeight=200;
        strErrorSavePath = "";
    }

};

#endif // SYSCONFIG_H
