#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <vector>
#include <QString>
#include "GIDataType.h"
#include "MotionCard.h"
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
class CRouteManager: public QObject
{
    Q_OBJECT
public:
    CRouteManager();

    bool InitRoutePath(QString strRoutePath);

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
    void ReadConfig();
    void SaveConfig();
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

    bool ReleasePLCCard();
    bool ReleaseMotionCard();


    //运动卡连续运动
    int m_iThreadContinueRunType; // 0：start 1：reset 2：run1 3：run2
    bool m_bIsThreadContinueRun;   //连续运动线程开始
    QSemaphore m_SemaphoreContinueRun;
    void ThreadMotionContinueRunFun();
    static void WINAPI ThreadMotionContinueRun(void *pThis);
    void ThreadInputSideAndOutputSideReadyFun();
    //运动卡IO控制[光源、相机]
    bool MotionCardIOControl(unsigned int iStep);
    //运动卡运动控制
    bool MotionStepControl(short sStep);
private:
    //进料口
    bool InputSideDown();//下 松
    bool InputSideUp();//紧 上
    bool InputProductOn(short mWaitTime = 1000);
    //出料口
    bool OutputSideDown();//下 松
    bool OutputSideUp();//紧 上
    bool OutputProductOn(short mWaitTime = 1000);
    //光栅
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
    //真空吸
    bool AxisAirOn(bool flag);
    //塔灯亮
    bool TowerLightRedOn(bool flag);
    bool TowerLightGreenOn(bool flag);
    bool TowerLightYellowOn(bool flag);
    //塔·蜂鸣器
    bool TowerBuzzerOn(bool flag);
    //人工指示灯
    bool ManualLightRedOn(bool flag);
    bool ManualLightGreenOn(bool flag);
    //路径
    bool IPhonePath_1();//正面检测
    bool IPhonePath_2();//中框
    bool IPhonePath_3();//翻转+摄像头
    bool IPhonePath_4();//背面检测
    bool IPhonePath_5();//出点检测位置
    //bool IPhonePath_6();//正背检测
private:
    int m_p1;
    int m_p2;
    int m_p3;
    int m_p4;
    int m_p5;
    int m_LightOpen;
    int m_Width;
    int m_Long;
    int m_W_H;
    int m_Circle14;
    int m_OutJudge;
    int m_FrontGrat;
    int m_BackGrat;
    int m_CylinderOffset;
    int m_FrameOffset;
    int m_FrameStep;
    int m_CameraOffset;
    int m_FrontBackImageHeight;
    int m_FrontBackDDROffSet;
    int m_FrontBackYOffSet;
public:
    //path1
    int m_iFrontVel;
    int m_iFrontAcc;
    //path2
    int m_iFrameVel;
    int m_iFrameAcc;
    //path3
    int m_iUpDownCameraVel;
    int m_iUpDownCameraAcc;
    //path4
    int m_iBackVel;
    int m_iBackAcc;
    //path5
    int m_iLineVel;
    int m_iLineAcc;
private:
    void SendLastError();
    std::function<void(s_ErrorInfo &)> m_funErrorInfo;
    s_ErrorInfo m_sErrorInfo; //记录最后报警内容
    std::function<void(e_RouteControlStatus,int)> m_funRunStatus; //状态回调
    void SendRouteStatus(e_RouteControlStatus eStatus,int iValue = 0);

    //信号相关
    bool m_bInitMotionSuc;
    CMotionCard m_MotionCard;
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


};

#endif // ROUTEMANAGER_H
