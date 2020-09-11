#ifndef GIDATATYPE_H
#define GIDATATYPE_H

#include <string>
#include <vector>
#include <Windows.h>
#include "AlgDataType.h"
#include "SchemaType.h"
#include "SysConfigDefine.h"


#define MAX_WORKCAMERA_COUNT 4

// 异常报警级别
enum e_ErrorGrade
{
    eEG_SystemOperate = 0, //操作
    eEG_Infomation,   //提示
    eEG_ErrorWarn,    //警告
    eEG_ErrorGenal,   //错误
    eEG_ErrorSerious, //异常
    eEG_MainShow      //主界面显示

};

enum e_StatusInfoType
{
    eSIT_Status0 = 0,//状态栏第一行
    eSIT_Status1,
    eSIT_Status2,
    eSIT_Status3,
    eSIT_Status4,
    eSIT_Status5,
    eSIT_Status6,
    eSIT_Status7,
    eSIT_Status8,
    eSIT_Status9,//状态栏第十行
    eSIT_RunProgress,//运行进度
    eSIT_MachineSpeed,//机速
    eSIT_ModelName,//模板名称
    eSIT_BatchName,//批号名称
    eSIT_CheckCount,//检测个数
    eSIT_ErrorCount,//错误个数个数
    eSIT_CurProductCode,//当前产品号
    eSIT_NextProductCode,//下个产品号
    eSIT_MainShowNormal,//主界面显示正常信息
    eSIT_MainShowExcept, //主界面显示异常信息
    eSIT_ShowNormalInfomation,
    eSIT_HideNormalInfomation

};

// 采集图像状态
enum e_GrabState
{
    eGT_Normal = 0,	// 正常
    eGT_GTLostFrame,// 丢帧
};

// 获取队列元素状态
enum e_PushState
{
    ePS_Normal = 0,	// 正常
    ePS_NoEmptyBuffer	// 无空闲队列元素
};

//各个线程运行状态
enum e_ThreadState
{
    eTS_Normal = 0,       //正常
    eTS_InfoPreAbnormity, //预处理线程异常
    eTS_AlgAbnormity,//算法检测异常
    eTS_InspectionAbnormity,//检测线程异常
    eTS_DataSynAbnormity    //综合处理线程异常
};

// 标识系统状态枚举类型
enum e_SystemState
{
    eSys_DefaultState = 0, //默认状态
    eSys_InitState,//初始状态
    eSys_NOThreadStart,  //线程未处理
    eSys_GrabFinish, //采集完毕
    eSys_PageStationStart, //画面处理结束
    eSys_InfoPreFinish, //预处理完毕
    eSys_CheckFinish, //检测完毕
    eSys_DataSummaryFinish,//综合处理完毕
    eSys_PageStationFinish, //画面处理结束
    eSys_WorkStationFinish, //工位操作完成
    eSys_DataSaveFinish,//保存原始图像，保存数据库，保存缺陷图像
    eSys_ShowFinish// 显示完毕
};

// 产品类型
enum e_ProductType
{
    ePT_NormalProdct = 0,                   // 正常产品
    ePT_NoProdcut                           // 非产品
};

// 系统类型
enum e_SystemModuleType
{
    eSMT_MobileWhole= 0             // 手机全检


};

// 状态栏系统状态类型
enum e_SysCurrentStatus
{
    eSC_SStarting = 0,		     // 系统正在启动...
    eSC_SRunning,				 // 系统已启动
    eSC_SClosing,				 // 正在退出系统...
    eSC_SInspecting,			  // 检测中...
    eSC_SStartInspectFail,         // 开始检测失败!
    eSC_SInspectStop,			   // 检测已停止!
    eSC_SNoMission,                // 无任务采集...
    eSC_SCreateMision,             // 创建任务采集...
    eSC_SUpdatingAlgorithmParam,   // 更新算法参数中...
    eSC_SUpdateAlgorithmParamOver, // 更新算法参数完毕!
    eSC_SLoadMissioning,           // 加载任务中...
    eSC_SLoadMissionSuccess,       // 加载任务成功!
    eSC_SLoadMissionFail,          // 加载任务失败!
    eSC_SReadCodeFileing,          // 读取号码文件中...
    eSC_SReadCodeFileSuccess,      // 读取号码文件成功!
    eSC_SReadCodeFileFail,         // 读取号码文件失败!
    eSC_SReadStartCodeFileSuccess, // 设置起始号成功!
    eSC_SReadStartCodeFileFail,    // 设置起始号失败!
    eSC_SRealShowImage,            // 调试实时显示...
    eSC_SReadMarkSchemeing,        // 读取Mark方案中...
    eSC_SReadMarkSchemeSuccess,    // 读取Mark方案成功!
    eSC_SReadMarkSchemeFail,       // 读取Mark方案失败!
    eSC_SJudgeProducting,          // 预判产品中...
    eSC_SSaveGabberImages,          // 保存图像

    eSC_SReadMarkStopGrab,
    eSC_SReadMarkRecycle,
    eSC_SReadMarkParam,
    eSC_SStudying,			        // 学习中...
    eSC_SLoadDataBaseSuc,
    eSC_SLoadDataBaseFail,
    eSC_ShowInt
};

// 采集图像颜色模式
enum e_GrabberColorMode
{
    GCM_GrayMode = 0,                  // 灰度图
    GCM_RGB24Mode,                     // 24位图
    GCM_RGB32Mode,                     // 32位图
    GCM_BayerMode                      // Bayer模式
};
// 接收采集图像内存处理方式
enum e_ImageCopyMode
{
	eICM_Normal = 0,                   // 直接接收
    eICM_Vertical,                     // 垂直镜像接收
    eICM_Horizontal                    //水平镜像接收
};

//给界面发送一些控制命令
enum e_UIControlParam
{
    eUI_Restart = 0,   //重启软件，无参数
    eUI_UpdateUIParam, //更新ui参数,读取s_UIParam
    eUI_LogPath,       //s_CommonCtrlParam:strParam0
    eUI_MachineSpeed,  //检测机速 s_CommonCtrlParam:dbParam0
    eUI_CheckCount,    //检测个数 s_CommonCtrlParam:iParam0  NG个数s_CommonCtrlParam:iParam1
    eUI_SchemaGrab,    //当前采图方案名称s_CommonCtrlParam:strParam0；iParam[0]=1存储；iParam[0]=0停止存储
    eUI_SchemaName,    //当前采图方案名称 s_CommonCtrlParam:strParam0
    eUI_ModelName,     //当前模板名称 s_CommonCtrlParam:strParam0
    eUI_BacthName,     //当前批号名称 s_CommonCtrlParam:strParam0
    eUI_LoadSchemaSuc, //加载采图方案成功 iParam[0]保存Page个数，strParam[0]保存Schema名称，iParam[1]开始Page序号,iParam1[1]开始Page采图方案模式，strParam[1]开始Page名称。
    eUI_LoadModelSuc,  //加载算法模板成功 iParam[0]保存Page个数，strParam[0]保存Model名称，iParam[1]开始Page序号，strParam[1]开始Page名称,iParam1[1]加载模板状态。
    eUI_RouteOpetate,  //运动相关操作
    eUI_AlgStartOrStop //是否开检
};

enum e_RouteParam
{
    eRP_RouteGoHome = 0,//设置所有轴回零位
    eRP_RouteEmergency,
    eRP_RouteEmergencyFinish,
    eRP_RouteReset,     //复位
    eRP_RouteStart, //开始
    eRP_RouteStop, //停止
    eRP_RouteRunFront, //运行前
    eRP_RouteRunBack, //运行后
    eRP_RouteGetStep,     //获取单步调试步骤
    eRP_RouteSetStep,     //设置单步调试
    eRP_GetRouteParam,    //获取轨迹参数
    eRP_SetRouteParam,    //设置轨迹参数
    eRP_SaveRouteParam   //保存轨迹参数
};

enum e_RouteControlStatus
{
    eRCS_Exception = 0,
    eRCS_Init,//初始化
    eRCS_StartBegin,     //
    eRCS_StartFail, //
    eRCS_StartSuccess, //
    eRCS_ResetBegin, //
    eRCS_ResetFail, //
    eRCS_ResetSuccess,     //
    eRCS_StopBegin,     //
    eRCS_StopFail,    //
    eRCS_StopSuccess,    //
    eRCS_EmergencyStart,  //
    eRCS_EmergencyFinish,
    eRCS_StartCheck,
    eRCS_StopCheck,
    eRCS_RunFrontBegin,
    eRCS_RunFrontFail,
    eRCS_RunFrontSuccess,
    eRCS_RunBackBegin,
    eRCS_RunBackFail,
    eRCS_RunBackSuccess,
    eRCS_RunTotalStepNum, //运行总步数
    eRCS_RunCurrentStepNum,//运行当前步数
    eRCS_PressEmergency,
    eRCS_PressEmergencyFinish,
    eRCS_PressStart,
    eRCS_PressStop,
    eRCS_PressReset,
    eRCS_PressRunFront,
    eRCS_PressRunBack

};

/*返回颜色编号*/
enum e_ProductTypeColor
{
    PTC_DEFAULT = -1,
    PTC_FALSE = 0,
    PTC_YELLOW=1,//黄色
    PTC_WHITE=2,//白色
    PTC_BLACK=3,//黑色
    PTC_RED=4,//红色
    PTC_ORANGE=5,//橘红色
    PTC_GOLD=6,//金色
	PTC_BLUE = 7,//金色
    PTC_NO=8,//默认无颜色

};

//模板参数
struct s_ModelParamInfo
{
    e_ProductTypeColor eTypeColor;
    std::string strModelName;
    bool bBGCheckTwoTimes;

    s_ModelParamInfo()
    {
        Reset();
    }
    void Reset()
    {
        eTypeColor = PTC_DEFAULT;
        strModelName = "";
        bBGCheckTwoTimes = false;
    }
};


//常用参数
struct s_GeneralParam
{
    s_ConfigErrorInfo sErrorInfo;
    s_ConfigBatchNo sBatchNo;
    s_GeneralParam() {}
};

//

struct s_CommonCtrlParam
{

    int iParam[20];
    int iParam1[20];
    double dbParam[20];

    std::string strParam[20];

	s_CommonCtrlParam()
	{
		for (int i = 0; i < 20; i++)
		{
			iParam[i] = 0;
			iParam1[i] = 0;
			dbParam[i] = 0.0;
			strParam[i] = "";
		}
	}
};

//
struct s_RouteParam
{
    e_RouteParam eRouteParam;
    s_CommonCtrlParam sParam;

    s_SchemaRouteMode sRouteMode;

    s_RouteParam()
    {}
};


struct s_UIControlParam
{
    e_UIControlParam eUICtrlParam;

    s_CommonCtrlParam sCommonParam;
};

//界面使用参数
struct s_UIParam
{
public:
    bool bStartGrab; //是否开始采集
    bool bStartInspect; //是否开始检测
    bool bLoadSchemaSuc; //是否检测采图方案成功
    bool bLoadModelSuc; //是否加载模板成功
    bool bOffGrab;      //是否为离线采集
    int iWorkCount;  //工位个数
    int iUIFullScreenMode;  //0：全屏模式  1：最大化模式
    int iUIShowStyle; //0:map  1:RealIMage

    std::string strUserPath; //用户路径
    std::string strModelPath;//模板路径
    std::string strDefectImgPath;//缺陷图像路径
    std::string strConfigPath; //配置文件路径

    s_UIParam()
    {
        bStartGrab = false;
        bStartInspect = false;
        bLoadSchemaSuc = false;
        bLoadModelSuc = false;
        bOffGrab = true;
        iWorkCount = 0;
        iUIFullScreenMode = 0;
        iUIShowStyle = 0;
        strUserPath = "";
        strModelPath = "";//模板路径
        strDefectImgPath = "";
        strConfigPath = "";
    }
};

//界面显示队列数据
struct s_CameraWorkInfo
{
public:
    int iWorkType;  //0：队列情况  1：时间情况
    int iWorkIndex; //工位索引
    int iWorkNo;    //工位号
    std::string strWorkName;
    std::string strInfo;

};




//保存实时图像
struct s_SaveRealImage
{
public:
    bool bEnableSavePage; //为建模保存图像
    bool bEnableSaveImage;//是否保存实时图像
    int iSaveImageType; //0:以整个产品为文件夹保存图像 1：以画面为文件夹保存图像
    bool bContinueSave; //连续保存
    int iSaveCount;  //保存个数
	int iCurSaveNum; //当前保存序号
    std::string strSaveImagePath;
    std::string strFileName;
    std::string strSavePagePath;
    std::vector<int> vecSavePageNo;

    s_SaveRealImage()
    {
        bEnableSavePage = false;
        bEnableSaveImage = false;//是否保存
        iSaveCount = 0;
        iCurSaveNum = 0;
        bContinueSave = false;
        vecSavePageNo.clear();
    }
};


// 机器信号
class CMachineSignal
{
public:
    bool bRunning;		// 开机运行

    int  iCount0;         // 剔废口
    int  iCount1;         // 延迟帧
    int  iCount2;         // 延迟行
    int  iCount3;         // 当前编码器帧计数
    int  iCount4;         // 当前编码器行计数
    int  iCount5;         // 行频
    int  iCount6;         // 光电帧计数
    int  iCount7;         // 计数器
    int  iCount8;         // 计数器
    int  iCount9;        // 计数器

public:

    CMachineSignal()
    {
        bRunning	= false;

        iCount0 = 0;         // 计数器
        iCount1 = 0;         // 计数器
        iCount2 = 0;         // 计数器
        iCount3 = 0;         // 计数器
        iCount4 = 0;         // 计数器
        iCount5 = 0;         // 计数器
        iCount6 = 0;         // 计数器
        iCount7 = 0;         // 计数器
        iCount8 = 0;        // 计数器
        iCount9 = 0;        // 计数器

    }

    virtual ~CMachineSignal()
    {
    }

    void Reset()
    {
        bRunning	= false;

        iCount0 = 0;         // 计数器
        iCount1 = 0;         // 计数器
        iCount2 = 0;         // 计数器
        iCount3 = 0;         // 计数器
        iCount4 = 0;         // 计数器
        iCount5 = 0;         // 计数器
        iCount6 = 0;         // 计数器
        iCount7 = 0;         // 计数器
        iCount8 = 0;        // 计数器
        iCount9 = 0;        // 计数器

    }

    CMachineSignal(const CMachineSignal &MachineSignal)
    {
        bRunning	= MachineSignal.bRunning;

        iCount0 = MachineSignal.iCount0;
        iCount1 = MachineSignal.iCount1;
        iCount2 = MachineSignal.iCount2;
        iCount3 = MachineSignal.iCount3;
        iCount4 = MachineSignal.iCount4;
        iCount5 = MachineSignal.iCount5;
        iCount6 = MachineSignal.iCount6;
        iCount7 = MachineSignal.iCount7;
        iCount8 = MachineSignal.iCount8;
        iCount9 = MachineSignal.iCount9;
    }

    const CMachineSignal& operator=(const CMachineSignal &MachineSignal)
    {
        bRunning	= MachineSignal.bRunning;

        iCount0 = MachineSignal.iCount0;
        iCount1 = MachineSignal.iCount1;
        iCount2 = MachineSignal.iCount2;
        iCount3 = MachineSignal.iCount3;
        iCount4 = MachineSignal.iCount4;
        iCount5 = MachineSignal.iCount5;
        iCount6 = MachineSignal.iCount6;
        iCount7 = MachineSignal.iCount7;
        iCount8 = MachineSignal.iCount8;
        iCount9 = MachineSignal.iCount9;
        return *this;
    }
};




/////////////////////////////////////////

//返回错误结构体
struct s_ErrorInfo
{
    int iErrorCode;	//错误代码（0：正常）
    e_ErrorGrade eErrorGrade; // 报警级别
    std::string strErrorDes;	//错误描述
    std::string strErrorMark;		//附加信息
    SYSTEMTIME systime; //报警时间
public:
    void GetTime()
    {
        GetLocalTime(&systime);
    }

};

////////////////////////////////////
/// \brief The s_ErrorImgHead struct
struct s_BatchDBInfo
{
    int iID;
    int iSystemtype;
    int iCheckCount;
    int iErrorCount;

    std::string strMachineNo;
    std::string strMissionName;
    std::string strBatchNo;
    std::string strProducer;
    SYSTEMTIME sysStartTime;
    SYSTEMTIME sysFinishTime;

    s_BatchDBInfo()
    {
        iID  = 0;
        iSystemtype = 0;
        iCheckCount = 0;
        iErrorCount = 0;
        strMachineNo = "";
        strMissionName = "";
        strBatchNo = "";
        strProducer = "";

    }
};

enum eErrorSaveResult
{
    eESR_SaveSuccess = 0, //保存成功
    eESR_PathCreateFail,//文件夹创建失败
    eESR_CutImageFail, //cut缺陷图时候失败
    eESR_CreateFileInvalid, //Create File无效
    eESR_WriteImgHeadFail,  //写图像头失败
    eESR_WriteImgBufFail,//写图像数据失败
    eESR_DisableSave,  //未使能保存缺陷图像
    eESR_AlgNGButNoCount, //算法检测NG，但个数为0
    eESR_AlgCheckOther, //算法检测特殊问题，例如灰尘过多等
    eESR_ALgModelOrCheck,//模板加载异常或者检测false
    eESR_ListShort,      //队列异常或者丢帧，或者线程异常
};

struct s_ErrorImgHead
{

    eErrorSaveResult eSaveResult;  //0:成功 1：保存失败
    int iPageNo;
    int iPageInnerNO; //画面内部编码 ，例如 中框的四个角依次为 0 ，1 ，2,3
    int iWidth;
    int iHeight;
    int iChannel;
    int iErrorType;
    int iErrorID;
    int iErrorIndex; //第几个缺陷
    int iErrImgSize; //图像大小

    float fArea;//缺陷面积
    float fLength;//缺陷长度
    float fWidth;//缺陷长度
    float fConstract;//缺陷长度
    float fCirRat;//缺陷长度
    float fRectRat;//缺陷长度
    float fJnd;//缺陷长度
    float fEnergy;//缺陷能量

    RECT rectE;

    char chProductNo[64];
    char chPageName[64];
    char chRegionName[64];
    char chErrorName[64];
    char chErrorImgPath[256];

    s_ErrorImgHead()
    {
        Reset();
    }

    void Reset()
    {
        memset(chProductNo,0,64);
        memset(chErrorName,0,64);
        memset(chPageName,0,64);
        memset(chRegionName,0,64);
        memset(chErrorImgPath,0,256);
        rectE.left = 0;
        rectE.right = 0;
        rectE.top = 0;
        rectE.bottom = 0;

        eSaveResult = eESR_SaveSuccess;
        iPageNo = 0;
        iPageInnerNO = 0;
        iWidth = 0;
        iHeight = 0;
        iChannel = 0;
        iErrorType = 0;
        iErrorID = 0;
        iErrorIndex = 0;
        iErrImgSize= 0;

        fArea = 0;
        fLength = 0;
        fWidth= 0;
        fConstract= 0;
        fCirRat = 0;
        fRectRat = 0;
        fJnd = 0;
        fEnergy = 0;
    }
};


enum e_AlgCheckStatus
{
	eACS_DefaultStatus = 0, //默认状态
	eACS_ModelOKStatus, //OK
	eACS_AlgModelEmpty, //模板为空
	eACS_AlgModelLoadFail, //模板加载失败
	eACS_AlgStepError, //过程异常
	eACS_AlgCheckReturnTrue,//算法返回正常
	eACS_AlgCheckReturnFalse, //算法返回false
	eACS_AlgCheckTryCatch, //算法trycatch
	eACS_LoadSchemaFail, //未加载采图方案
	eACS_LoadStepExcep, //：加载过程异常
    eACS_UnknowError, //未知错误
};
//检测结果
struct s_AlgResultInfo
{
    bool bCheckBGTwoTimes;//背面采集两次
    int iSchemaPageMode;//采图模式

    e_AlgCheckStatus eAlgCheckStatus; //-1初始  0：ok   //1配置为空  2：加载失败 3：过程异常  100:检测返回， 101：检测返回false  102：检测catch
    s_AlgCheckOutputParam sAlgCheckOutputParam;

    s_ModelParamInfo sModelParamInfo;

    bool bHaveError;    //有错误
    int  iErrorType;    //错误类型
    std::string strErrorDes;  //错误描述

    std::vector<s_ErrorImgHead> vecErrorImgHead;

    s_AlgResultInfo() {Reset();}

    const s_AlgResultInfo& operator=(const s_AlgResultInfo &sAlgResultInfo)
    {
        bCheckBGTwoTimes = sAlgResultInfo.bCheckBGTwoTimes;//背面采集两次
        iSchemaPageMode = sAlgResultInfo.iSchemaPageMode;//采图模式
        eAlgCheckStatus = sAlgResultInfo.eAlgCheckStatus; //工位索引
        sAlgCheckOutputParam = sAlgResultInfo.sAlgCheckOutputParam;  //相机索引

        sModelParamInfo = sAlgResultInfo.sModelParamInfo;

        bHaveError = sAlgResultInfo.bHaveError; ;    //有错误
        iErrorType = sAlgResultInfo.iErrorType; ;    //错误类型
        strErrorDes = sAlgResultInfo.strErrorDes; ;  //错误描述
        vecErrorImgHead.clear();
        for(int i = 0;i < sAlgResultInfo.vecErrorImgHead.size();i++)
        {
            vecErrorImgHead.push_back(sAlgResultInfo.vecErrorImgHead.at(i));
        }
        return *this;
    }
    void Reset()
    {
        bCheckBGTwoTimes = false;
        iSchemaPageMode = 0;
        bHaveError = false;    //有错误
        iErrorType = 0;    //错误类型
        eAlgCheckStatus = eACS_DefaultStatus;
        sAlgCheckOutputParam.Reset();

        strErrorDes = "";  //错误描述
        vecErrorImgHead.clear();

        sModelParamInfo.Reset();

    }
};

//产品结果
enum e_ProductErrorType
{
    ePET_NoResult = -1, //无检测结果
    ePET_ResultOK = 0,  //0:正常
    ePET_ResultNG, //1：有错误
    ePET_ListShort, //2：队列异常
    ePET_FrameShort, //3：有丢帧
    ePET_ThreadExcep,  //4.线程异常
    ePET_CheckExcep,  //5.检测异常
    ePET_ModelExcep,  //6.模板异常
    ePET_ColorExcep,  //7颜色异常

};
//整个产品的结果
struct s_ProductResult
{
    std::string strBatchNo;
    std::string strProductNo;
    s_ModelParamInfo sModelParamInfo;
    int iCheckCountIndex; //检测计数

    bool bHaveError;    //有错误
    e_ProductErrorType  eErrorType;    //错误类型 -1:无检测结果 0:正常  1：有错误  2：队列异常  3：有丢帧  4：线程异常  5：检测异常  6 模板异常 7颜色异常
    std::string strErrorDes;  //错误描述

    std::vector<s_ErrorImgHead> vecErrorImgHead;
    SYSTEMTIME sysFinishTime;

    s_ProductResult()
	{
		Reset();
	}

    void Reset()
    {
        strBatchNo = "";
        strProductNo = "";


        sModelParamInfo.Reset();

        iCheckCountIndex = 0; //检测计数

        bHaveError = true;
        eErrorType = ePET_NoResult;
        strErrorDes = "";
        vecErrorImgHead.clear();

        sysFinishTime.wYear = 0;
        sysFinishTime.wMonth = 0;
        sysFinishTime.wDay = 0;
        sysFinishTime.wHour = 0;
        sysFinishTime.wMinute = 0;
        sysFinishTime.wSecond = 0;
    }
};


struct s_ImageInfo
{
    bool bHaveImage;
    BYTE* pImageBuff;	//图像缓冲区
    long lBuffSize;	//图像缓冲区大小

    long lImageWidth;		//图像宽度
    long lImageHeight;	//图像长度
    long lImageChannel;	//象素大小（单位：字节）
    long lImageLineSize;	//每行占内存大小line memory size
    long lImageSize;		//图像数据大小
    s_ImageInfo()
    {
        Reset();
    }

    void Reset()
    {
        bHaveImage = false;
        lBuffSize = 0;
        lImageWidth = 0;
        lImageHeight = 0;
        lImageChannel = 0;
        lImageLineSize  = 0;
        lImageSize= 0;
        pImageBuff = nullptr;
    }
};
//图像数据流
class  CFrameDataInfo
{
public:
    int iStationIndex; //工位索引, 初始化时填写
    int iCameraIndex;  //相机索引, 初始化时填写
    int iPageIndex;


    //
    e_PushState ePushState;// 获取队列填充状态, 初始化时填写
    e_GrabState	eGrabState; // 当前图像的采集状态，回调时填写
    e_ThreadState eThreadState;//各个线程运行状态
    e_ProductType eProductType; // 产品类型
    e_SystemState  eSystemState; // 当前系统处理状态
	e_ImageCopyMode eImageCopyMode;//图像拷贝方式，回调时候填写
    CMachineSignal MachineSignal; // 采集图像机器信号状态，回调时填写

    int iStationSN; //工位编号，回调时填写
    int iComputerSN; // 计算机编号，回调时填写
    int iCameraSN;  // 采集图像的相机编号，回调时填写
    int iPageNO; //画面号
    int iPageInnerNO; //画面内部编码 ，例如 中框的四个角依次为 0 ，1 ，2,3

    int	iFrameCount; // 采集卡当前采集帧记数，回调时填写
    int iFrameHardSN;  //记录编码器帧数，设置批号时候清零
    int iKickFrameSN;  //踢废帧

    int iProductCount;// 产品计数
    int iBigPageSN;  // 产品的对应大张号


    int iCameraType;  //相机类型 0：面阵 1：线阵 2：贝尔转换
    std::vector<CFrameDataInfo *> vcPFrameData;     //存放工位的所有元素

    //////////////////////////////////////////////////////////////////////////
    std::string strSchemaName;  //采图方案名称
    std::string strModelName;   //模板名称
    std::string strBatchName;   //批号名称
    std::string strProductNo;   //产品名称
    std::string strPageName;   //Page名称

    //检测处理控制
    bool bRunAlgFun; //需要走算法流程
    s_ImageInfo sImageInfo; //采集图像
    std::vector<s_ImageInfo> vecCombineImage;

    //检测结果
    s_AlgResultInfo sAlgResultInfo;

    bool bCheckColor; //是否判断产品颜色
    bool bBGCheckTowTimes; //背面是否检测两次


    //////////////////////////////////////////////////////////////////////////
    //一些过程控制
    s_SaveRealImage sSaveRealImage; //保存图像相关

    ///////////////////////////////////////////////////////////////////////////

    //调整线程中，缓冲时间
    int   iGrabCallBackSpace;    // 回调间隔时间
    int   iRGBToGrayTime;        //分通道时间
    int   iGrabberSpendTime;     // 采集回调耗费时间
    int   iPreProcessSpendTime;  // 预处理线程耗费时间
    int   iAlgSpendTime;	     // 算法耗费时间
    int   iAlgInspectSpendTime;  //检测线程耗时
    int   iSynthesizeSpendTime;  // 综合时间耗时，不算显示
    int   iShowSpendTime;        // 显示耗费时间
    int   iSaveToDatabase;       //存数据库时间
    int   iSaveImageSpendTime;  // 保存图像耗费时间
    int   iNetSendSpendTime;     // 网络发送耗费时间
    int   iSysSpendTime;         // 系统总耗时

    SYSTEMTIME	TimeGrab;       // 采集图像时刻
    SYSTEMTIME	TimeFinish;     //系统结束时


public:
    CFrameDataInfo()
    {

    }

    ~ CFrameDataInfo()
    {

    }



    CFrameDataInfo(const CFrameDataInfo & FrameDataInfo)
    {
        iStationIndex = FrameDataInfo.iStationIndex; //工位索引
        iCameraIndex = FrameDataInfo.iCameraIndex;  //相机索引

    }

    const CFrameDataInfo& operator=(const CFrameDataInfo &FrameDataInfo)
    {
        iStationIndex = FrameDataInfo.iStationIndex; //工位索引
        iCameraIndex = FrameDataInfo.iCameraIndex;  //相机索引
        return *this;
    }

    void ResetFrame()
    {
        iStationIndex = 0; //工位索引
        iCameraIndex = 0;  //相机索引
        iPageIndex = 0;
        //
        eGrabState = eGT_Normal; // 当前图像的采集状态
        ePushState = ePS_Normal;// 获取队列填充状态
        eThreadState = eTS_Normal;//各个线程运行状态
        eProductType = ePT_NormalProdct; // 产品类型
        eSystemState = eSys_DefaultState; // 当前系统状态
        eImageCopyMode = eICM_Normal;//图像拷贝方式
        MachineSignal.Reset(); // 采集图像机器信号状态

        iStationSN = 0;//工位编号
        iComputerSN = 0; // 计算机编号
        iCameraSN = 0; // 采集图像的相机编号
        iPageNO = 0;
        iPageInnerNO = 0;

        iFrameCount = 0; // 采集卡当前采集帧记数
        iProductCount = 0;// 产品计数
        iBigPageSN = 0; // 产品的对应大张号
        iFrameHardSN = 0;  //记录编码器帧数，设置批号时候清零
        iKickFrameSN = 0;            //踢废帧

        vcPFrameData.clear();     //存放工位的所有元素

        iCameraType = 0;  //相机类型 0：面阵 1：线阵 2：贝尔转换
        vecCombineImage.clear();
        //////////////////////////////////////////////////////////////////////////
        strSchemaName = "";  //采图方案名称
        strModelName = "";   //模板名称
        strBatchName = "";   //批号名称
        strProductNo = "";
        strPageName = "";

        //检测控制
        bRunAlgFun = false; //需要走算法流程

        //检测结果
        sAlgResultInfo.Reset();

        bCheckColor = false;
        bBGCheckTowTimes = false; //背面是否检测两次
        //////////////////////////////////////////////////////////////////////////

        //调整线程中，缓冲时间
        iGrabCallBackSpace = 0;    // 回调间隔时间
        iRGBToGrayTime = 0;        //分通道时间
        iGrabberSpendTime = 0;     // 采集回调耗费时间
        iPreProcessSpendTime = 0;  // 预处理线程耗费时间
        iAlgSpendTime = 0;	     // 算法耗费时间
        iAlgInspectSpendTime = 0;  //检测线程耗时
        iSynthesizeSpendTime = 0;  // 综合时间耗时，不算显示
        iShowSpendTime = 0;        // 显示耗费时间
        iSaveToDatabase = 0;       //存数据库时间
        iSaveImageSpendTime = 0;  // 保存图像耗费时间
        iNetSendSpendTime = 0;     // 网络发送耗费时间
        iSysSpendTime = 0;         // 系统总耗时

    }
};

struct s_CommonPageInfo
{
    int iPageNo;
    std::string strPageName;
    e_SchemaPageMode eSchemaPageMode;
    e_AlgCheckStatus eLoadModelStatus;
    s_CommonPageInfo() {}
};

//工位参数
struct s_WorkCamera
{
    int iCameraSelfNo;  //自定义采集编号
    std::string strCameraSelfName;  //自定义采集名称

    int iCamaraNo;  //相机序号
    std::string strCameraMark; //相机标识
    std::string strCameraInitFile; //采集设备初始化文件

    int iCameraBrand; //相机品牌 0：模拟 1：Ds 2：chromens
    int iCameraType;  //相机类型 0：面阵 1：线阵 2：贝尔转换
    int iImageCopyMode;//内存拷贝方式 0：正常拷贝 1：垂直镜像 2：水平镜像
    int iImageWidth; //图像宽
    int iImageHeight;//图像高
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH; //横向分辨率，单位每像素微米数
    double dbResolutionV; //纵向分辨率，单位每像素微米数
    double dbResolutionD; //Z向分辨率，单位每像素微米数
    double dbOverLap; //两个相机的重叠区域，单位微米

    s_SaveRealImage sSaveRealImage;
    LARGE_INTEGER lgiCallSpaceStart;
    LARGE_INTEGER lgiCallSpaceEnd;

    s_WorkCamera()
    {
        iCameraSelfNo = 0;
        strCameraSelfName = "";
        iCamaraNo = 0;
        strCameraMark = "";
        strCameraInitFile = "";
        iCameraBrand = 0;
        iCameraType = 0;
        iImageCopyMode = 0;
        dbResolutionH= 10;
        dbResolutionV= 10;
        dbResolutionD = 10;
        dbOverLap = 0;
        iImageWidth = 0;
        iImageHeight = 0;
        iImageChannel = 0;
    }
};

struct s_WorkStationOne
{
    int iStationNo; //工位编号
    std::string strStationName; //工位名称
    int iPageNo; //画面编号
    std::string strPageName; //画面名称
    int iInspectType; //检测类型
    int iInspectObject; //检测对象

    ///////////////////////////
    std::string strModelPath; //模板路径
    std::string strParamPath; //默认参数路径 例如 D:/Bin/AlgConfig
    std::string strLogPath;   //日志路径 例如 D:/User/Log/AlgLog
    //////////////////////////////
    int iCameraListCount; //队列个数
    int iCameraCount; //相机个数
    std::vector<s_WorkCamera> vecWorkCamera;

    s_WorkStationOne()
    {
        iStationNo = 0;
        strStationName= "";
        iPageNo=0;
        strPageName = "";
        iInspectType = 0;
        iInspectObject= 0;

        /////////////////////////////
        strModelPath = "";
        strParamPath = "";
        strLogPath = "";
        /////////////////////////////

        iCameraListCount = 3;
        iCameraCount= 0;
        vecWorkCamera.clear();
    }
    s_WorkStationOne(const s_WorkStationOne & sWorkStationOne)
    {
        iStationNo = sWorkStationOne.iStationNo;
        strStationName = sWorkStationOne.strStationName;
        iPageNo = sWorkStationOne.iPageNo;
        strPageName = sWorkStationOne.strPageName;
        iInspectType = sWorkStationOne.iInspectType;
        iInspectObject = sWorkStationOne.iInspectObject;

        /////////////////////////////
        strModelPath = sWorkStationOne.strModelPath;
        strParamPath = sWorkStationOne.strParamPath;
        strLogPath = sWorkStationOne.strLogPath;
        /////////////////////////////


        iCameraListCount = sWorkStationOne.iCameraListCount;
        iCameraCount = sWorkStationOne.iCameraCount;
        vecWorkCamera.clear();
        for(int i = 0;i < sWorkStationOne.vecWorkCamera.size();i++)
        {
            vecWorkCamera.push_back(sWorkStationOne.vecWorkCamera.at(i));
        }

    }

    const s_WorkStationOne& operator=(const s_WorkStationOne &sWorkStationOne)
    {
        iStationNo = sWorkStationOne.iStationNo;
        strStationName = sWorkStationOne.strStationName;
        iPageNo = sWorkStationOne.iPageNo;
        strPageName = sWorkStationOne.strPageName;
        iInspectType = sWorkStationOne.iInspectType;
        iInspectObject = sWorkStationOne.iInspectObject;

        /////////////////////////////
        strModelPath = sWorkStationOne.strModelPath;
        strParamPath = sWorkStationOne.strParamPath;
        strLogPath = sWorkStationOne.strLogPath;
        /////////////////////////////

        iCameraListCount = sWorkStationOne.iCameraListCount;
        iCameraCount = sWorkStationOne.iCameraCount;
        vecWorkCamera.clear();
        for(int i = 0;i < sWorkStationOne.vecWorkCamera.size();i++)
        {
            vecWorkCamera.push_back(sWorkStationOne.vecWorkCamera.at(i));
        }
        return *this;
    }

};
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
///

#endif // GIDATATYPE_H
