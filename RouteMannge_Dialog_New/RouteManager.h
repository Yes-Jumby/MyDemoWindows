#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <vector>
#include <QString>
#include "GIDataType.h"
#include "MotionCard.h"
#include "GardasoftLight.h"
#include <functional>
#include <QObject>
#include <QtConcurrent>

#include <windows.h>          // for HANDLE
#include <process.h>          // for _beginthread()

//运动控制卡
#define MAX_ROUTEMOTION_AXISCOUNT 16
struct s_RouteMotionControl
{
    bool bEnableMotion;
    bool bEnableMotionExt;
    int iMotionType; //0：固高
    int iMotionCount;
    int iMotionChanne[4];
    QString strGTExtModulFile;
    QString strGTInitFile[4];
    QString strMotionInitFile[4];
    bool bEnalbeLightAlarm;
    bool bEnableKickOut;
    bool bEnableStopAlarm;

    s_RouteMotionControl()
    {
        bEnableMotion = false;
        bEnableMotionExt = false;
        iMotionCount = 0;
        iMotionType = 0;
        bEnalbeLightAlarm = false;
        bEnableKickOut = false;
        bEnableStopAlarm = false;
        strGTExtModulFile = "";
        for(int i = 0;i<4; i++)
        {
            iMotionChanne[i] = 0;
            strGTInitFile[i] = "";
            strMotionInitFile[i] = "";
        }
    }
};
//PLC control
struct s_RoutePLCControl
{
    bool bEnablePLC;
    int iEncoderLineCount;
    bool bEnalbeLightAlarm;
    bool bEnableKickOut;
    bool bEnableStopAlarm;

    s_RoutePLCControl()
    {
        bEnablePLC = false;
        iEncoderLineCount = 5000;
        bEnalbeLightAlarm = false;
        bEnableKickOut = false;
        bEnableStopAlarm = false;
    }
};
struct s_Gardsoftparam
{
    double dPulseWidth;
    double dPulseDelay;
    double dCurrent;
    double dRetriggerDelay;
    s_Gardsoftparam()
    {
        dPulseWidth = 0.0;
        dPulseDelay = 0.0;
        dCurrent = 0.0;
        dRetriggerDelay = 0.0;
    }
};
struct s_LightParamInfo
{
    QString strSchemaModelName;
    std::vector<int> vecRSeeParam;
    std::vector<s_Gardsoftparam> vecGardSoftParam;
    bool bBackTwice;
    bool bExposureValid[6];
    float  fExposureTime[6];
    bool bGainValid[6];
    float fGain[6];

    int  iFrontVel = 0;
    int  iFrontAcc = 0;
    int  iFrameVel = 0;
    int  iFrameAcc = 0;
    int  iFrameCornerVel = 0;
    int  iFrameCornerAcc = 0;
    int  iUpDownCameraVel = 0;
    int  iUpDownCameraAcc = 0;
    int  iBackVel = 0;
    int  iBackAcc = 0;
    int  iLineVel = 0;
    int  iLineAcc = 0;
    s_LightParamInfo()
    {
        vecRSeeParam.clear();
        vecGardSoftParam.clear();
        memset(&bBackTwice,0,sizeof(bool));
        memset(bExposureValid,0,6*sizeof(bool));
        memset(fExposureTime,0,6*sizeof(float));
        memset(bGainValid,0,6*sizeof(bool));
        memset(fGain,0,6*sizeof(float));
    }
};
class CRouteManager: public QObject
{
    Q_OBJECT
public:
    CRouteManager();
    ~CRouteManager();
    bool InitRoutePath(QString strSchmaPath,QString strRoutePath,bool bRecheckFrame);//中框 位于ini文件
    bool ReleaseRoute();

    // -1：出现异常 0：Run开始 1：Run结束  100：急停 101：按键start  102：按键stop 103：按键Reset 104:Run
    void RegeditGetRunStatus(std::function<void(e_RouteControlStatus,int)> funStatusInfo);

    //注册获取错误回调
    void RegeditGetLastErrorFun(std::function<void(s_ErrorInfo &)> funErrorInfo);

    //获取最后的异常
    const s_ErrorInfo & GetLastError();

    ///////////////////////////////////////////////////
    //轨迹运动相关
    bool RouteOperate(s_SchemaRouteMode & sRouteParam); //设置轨迹参数

    bool RouteEmergentStop(bool bStart); //急停

    bool RouteReset();   //复位

    bool RouteStart(); //开始

    bool RouteStop();  //停止

    bool RouteRunFront(); //前运行
    bool RouteRunBack(); //后运行

    /////////////////////////////////////////////////////

    //信号相关
    bool CallMotionDebugDlg();

    bool CallMotionModelDlg();

    bool CallRouteManageDlg();

    bool CallRouteParamDlg();

    bool CallLightParamDlg();
    void ReadConfig();
    void SaveConfig();

    //设置条码
    void SetCodeType(bool flag);//false为人工输入[默认]，true为条码枪
    bool SetCodeValid(bool flag);//条码枪输入情况下，返回真，其余为假
    //设置相关参数，注册回调
    bool ReadSchemaConfig(QString strSchmaName,QStringList ListSchemaModelName,bool *bBackTwice);//加接口，背面是否2次采集
    bool SaveSchemaConfig(QString strSchemaModelName);
    void SetStationNoAndCameraNo(int *piStationNo,int *piCameraNo,int size = 4);
    bool SetCurrentSchemaModelName(QString strSchemaModelName);
    //1.普通函数，依次记录摄像头、中框上、中框下、前听筒面阵相机的工位号，相机号
    //设置参数(int iStationSN,int iCameraSN,int iType,float fParamValue) itype 0为曝光 1为增益
    void RegisterCameraStationParamSet(std::function<bool(int,int,int,float)> CallBackFunc);

    bool ReadSchmaRouteConfig(QString strSchmaName);
    bool SaveSchmaRouteConfig();
    bool ReadSchmaLightConfig(QString strSchmaName);
    bool SaveSchmaLightConfig();
    //人工指示灯
    bool ManualLightRedOn(bool flag);
    bool ManualLightGreenOn(bool flag);
    //照明灯
    bool FloodlightOn(bool flag);
signals:
    void signalSentMessageInfomation(QString);

private slots:
    void slotGetMessageInfomation(QString strAlarm);

private:
    void FunThreadRouteStart(); //开始
    void FunThreadRouteReset();   //复位

    void FunThreadRouteRunFront(); //前运行
    void FunThreadRouteRunBack(); //后运行

    void MessageInformation(QString strAlarm,bool bMessageBox = true,bool bAlarm = true);

    bool RouteGoFirst(); //回开始位置

    bool m_bStartMotionSignalRead; //启动线程
    QSemaphore m_SemaphoreSignalReadFinish;
    bool ThreadMotionSignalRead(); //读信号线程

    ///////////////////////

    void FunMotionCallBack(int iCallInfo); //回调信息
    void FunMotionErrorBack(const CMotionCard::s_MotionErrorInfo & sMotionErrorInfo); //回调信息

    bool InitMotionCard();
    bool InitPLCCard();
    bool InitLightDriver();
    bool ReleasePLCCard();
    bool ReleaseMotionCard();


    //运动卡连续运动
    int m_iThreadContinueRunType; // 0：start 1：reset 2：run1 3：run2
    bool m_bIsThreadContinueRun;   //连续运动线程开始
    bool m_bCodeValid;
    bool m_bCodeType;
    QMutex m_MutexCodeValid;
    QSemaphore m_SemaphoreContinueRun;
    HANDLE m_HandleWaitForColor;
    void ThreadMotionContinueRunFun();
    static void WINAPI ThreadMotionContinueRun(void *pThis);
    void ThreadInputSideAndOutputSideReadyFun();
    //运动卡IO控制[光源、相机]
    bool MotionCardIOControl(unsigned int iStep);
    //运动卡运动控制
    bool MotionStepControl(short sStep);
private:
    //进料口
    bool InputSideDownReady();//松 下
    bool InputSideDown();//下 松
    bool InputSideUp();//紧 上
    bool InputProductOn(short mWaitTime = 1000);
    //出料口
    bool OutputSideDownReady();//松 下
    bool OutputSideDown();//下 松
    bool OutputSideUp();//紧 上
    bool OutputProductOn(short mWaitTime = 1000);//有产品为真
    //光栅 无遮挡返回真
    bool GratingFront();
    bool GratingBack();
    //翻转气缸
    bool CylinderReady();//静 下 松
    bool CylinderReadyUp();//静 上 松
    bool CylinderMove();//紧 上 动 下
    bool CylinderSetStatic();//翻转气缸置静点
    bool CylinderSetEmpty();//翻转夹紧置松
    //判断旋转轴有无产品
    bool AxisProductOn(short mWaitTime = 5000);
    //判断是否有气压
    bool IsAirOn();
    //定位开始
    bool Orientated(bool flag);
    bool OrientatedFrontBack(bool flag);
    bool OrientatedLeftRight(bool flag);
    //真空吸
    bool AxisAirOn(bool flag);
    //塔灯亮
    bool TowerLightRedOn(bool flag);
    bool TowerLightGreenOn(bool flag);
    bool TowerLightYellowOn(bool flag);
    //塔·蜂鸣器
    bool TowerBuzzerOn(bool flag);

    //离子吹风,第iIndex路从0开始,-1代表所有。
    bool EnableClearSetting(int iIndex,bool flag);

    //左右门-默认开启检测
    bool IsLeftFrontDoorClosed(bool isEnableCheck = true);
    bool IsLeftBackDoorClosed(bool isEnableCheck = true);
    bool IsRightFrontDoorClosed(bool isEnableCheck = true);
    bool IsRightBackDoorClosed(bool isEnableCheck = true);
    //路径
    bool IPhonePath_1();//正面检测
    bool IPhonePath_1_Lisener();//听筒
    bool IPhonePath_2();//中框
    bool IPhonePath_CylinderCamera();//前置听筒
    bool IPhonePath_3();//翻转+摄像头
    bool IPhonePath_4();//背面检测
    bool IPhonePath_4_Twice();//背面再次检测
    bool IPhonePath_5();//出点检测位置
    //光源设置

    bool IPhonePath_1_Light();
    bool IPhonePath_2_Light();
    bool IPhonePath_4_Light();
    bool IPhonePath_2_ExposureTime();
    bool IPhonePath_3_ExposureTime();
    bool IPhonePath_Lisener_ExposureTime();//前置摄像头
    bool IPhonePath_CylinderCamera_ExposureTime();//听筒
    bool IPhonePath_2_Gain();//中框上 下 前听筒
    bool IPhonePath_3_Gain();//后置摄像头 闪光灯
    bool IPhonePath_Lisener_Gain();//听筒
    bool IPhonePath_CylinderCamera_Gain();
    //bool IPhonePath_6();//正背检测
public:
    int m_iP1;
    int m_iP2;
    int m_iP3;
    int m_iP4;
    int m_iP5;
    int m_iFrontGrat;
    int m_iBackGrat;
    int m_iLightOpen;
    int m_iCircle14;
    int m_iRunBackOffSetY;
public:
    int m_iPublicLong;
    int m_iPublicWidth;
	int m_MyLength;//中框焦点距离
public:
    //Door
    bool m_isEnableCheckDoor;
    bool m_bFloodlightOn;
    //Demension
    int m_iWidth;
    int m_iLong;
    int m_iFrontBackImageHeight;

    //path1
    int m_iFrontVel;
    int m_iFrontAcc;
    int m_iFrontOffSetX;
    int m_iFrontOffSetY;
    int m_iFrontOffSetZ;
    //Lisener
    int m_iLisenerX;
    int m_iLisenerY;
    int m_iLisenerZ;
    //path2
    int m_iCylinderCameraX;
    int m_iCylinderCameraY;
    int m_iCylinderCameraZ;
    int m_iFrameVel;
    int m_iFrameAcc;
    int m_iFrameStep;
    int m_iFrameOffSetX1;
    int m_iFrameOffSetY1;
    int m_iFrameOffSetZ1;
    int m_iFrameOffSetX2;
    int m_iFrameOffSetY2;
    int m_iFrameOffSetZ2;
    int m_iFrameOffSetX3;
    int m_iFrameOffSetY3;
    int m_iFrameOffSetZ3;
    int m_iFrameOffSetX4;
    int m_iFrameOffSetY4;
    int m_iFrameOffSetZ4;
    int m_iFrameCornerVel;
    int m_iFrameCornerAcc;
    int m_iFrameCornerOffSetX1;
    int m_iFrameCornerOffSetY1;
    int m_iFrameCornerOffSetZ1;
    int m_iFrameCornerOffSetX2;
    int m_iFrameCornerOffSetY2;
    int m_iFrameCornerOffSetZ2;
    int m_iFrameCornerOffSetX3;
    int m_iFrameCornerOffSetY3;
    int m_iFrameCornerOffSetZ3;
    int m_iFrameCornerOffSetX4;
    int m_iFrameCornerOffSetY4;
    int m_iFrameCornerOffSetZ4;
    //path3
    int m_iUpDownCameraVel;
    int m_iUpDownCameraAcc;
    int m_iCylinderOffSetX;
    int m_iCylinderOffSetY;
    int m_iCylinderOffSetZ;
    int m_iCameraOffSetX;
    int m_iCameraOffSetY;
    int m_iCameraOffSetZ;
    int m_iFlashOffSetX;
    int m_iFlashOffSetY;
    int m_iFlashOffSetZ;
    //path4
    int m_iBackVel;
    int m_iBackAcc;
    int m_iBackOffSetX;
    int m_iBackOffSetY;
    int m_iBackOffSetZ;
    int m_iBackOffSetX1;
    int m_iBackOffSetY1;
    int m_iBackOffSetZ1;
    //path5
    int m_iLineVel;
    int m_iLineAcc;
    //Points
    int m_iResetPointOffSetX;
    int m_iResetPointOffSetY;
    int m_iResetPointOffSetZ;

    int m_iGetPointOffSetX;
    int m_iGetPointOffSetY;
    int m_iGetPointOffSetZ;
    //FrameSteps
    int m_iStep1[20];
    int m_iStep2[20];
    int m_iStep3[20];
    int m_iStep4[20];
    int m_iStepCount[4];
    int m_iStepLength[4];
public:
    //光源参数
    double m_dPulseWidth[13];
    double m_dPulseDelay[13];
    double m_dCurrent[13];
    double m_dRetriggerDelay[13];
    int    m_iCameraLightIntensity;
    std::vector<s_LightParamInfo> m_vecLightParamInfo;
    //曝光参数 后摄像头、中框上、中框下面阵、前摄像头、前听筒、后闪光灯的工位号，相机号
    bool m_bExposureValid[6];
    float  m_fExposureTime[6];
    bool m_bGainValid[6];
    float m_fGain[6];
    int  m_iStationNo[6];
    int  m_iCameraNo[6];
    QString m_strSchmaName;
    QString m_strSchmaModelName;
    int     m_iSchmaModelIndex;
    QStringList m_listSchemaModelName;
    bool m_bBackTwice;
    bool m_bRecheckFrame;
private:
    QString m_strSchmaPath;
    short m_sProductType;//1为XR
    int m_W_H;
    float  m_fExposureTimeOld[5];//摄像头、中框上、中框下面阵、新加相机
    float m_fGainOld[5];

private:
    void SendLastError();
    //设置参数 itype 0为曝光 1为增益
    bool SetCameraStationParam(int iStationSN,int iCameraSN,int iType,float fParamValue,int iIndex);
    std::function<void(s_ErrorInfo &)> m_funErrorInfo;
    std::function<bool(int,int,int,float)> m_funCameraStationParamSet;
    s_ErrorInfo m_sErrorInfo; //记录最后报警内容
    std::function<void(e_RouteControlStatus,int)> m_funRunStatus; //状态回调
    void SendRouteStatus(e_RouteControlStatus eStatus,int iValue = 0);
    int GetArraySum(short sStepNum,short sIndex);
    void FindAndSetSchemaModelParam(const s_LightParamInfo &sLightParamInfo);
    s_LightParamInfo &FindLightParamInfo(QString strSchemaModelName);
    //信号相关
    bool m_bInitMotionSuc;
    CMotionCard m_MotionCard;
    CGardasoftLight m_GardasoftLight;
    int m_iMotionCrdNumber; //坐标系号
    CMotionCard::s_CoordinateSysOut m_sCoordinateSysOut;
    s_SchemaRouteMode m_sRouteParam;


    e_RouteControlStatus m_eRouteControlStatus;

    //按键相关
    bool m_bPressStart;
    bool m_bPressStop;
    bool m_bPressReset;
    bool m_bPressEmergentStop;
    bool m_bPressRunFront;
    bool m_bPressRunBack;
    bool m_bIsLeftFrontDoorClosed;
    bool m_bIsLeftBackDoorClosed;
    bool m_bIsRightFrontDoorClosed;
    bool m_bIsRightBackDoorClosed;

    //
    QString m_strRoutePath;
    QString m_strRouteFile;

    s_RouteMotionControl m_sMotionControl;
    s_RoutePLCControl m_sPLCControl;

    ///////////////////////////////////////////////////
    //轨迹运动相关
    bool m_bLoadRouteParamSuc; //加载轨迹参数成功
    bool m_bEnableMotionSuc;  //使能成功
    bool m_bEnableAxsisSuc[MAX_ROUTEMOTION_AXISCOUNT];
    bool m_bMotionGoHomeSuc;  //回零成功
    bool m_bMotionResetSuc;   //复位成功
    bool m_bMotionStartSuc;   //开始成功
    bool m_bMotionStopSuc;    //停止成功
    bool m_bMototionEmergency;   //急停
    bool m_bIsMotionInspectAuto;//是否自动检测
    bool m_bFrontRunSuc;
    bool m_bBackRunSuc;

//1.普通函数，依次记录中框上、中框下、摄像头面阵相机的工位号，相机号；
//2.注册回调函数，调用CameraStation中的设置曝光函数；
};

#endif // ROUTEMANAGER_H
