#include "RouteManager.h"
#include "QtFileOperate.h"
#include "DefinedGuGaoIO.h"
#include <QSemaphore>//信号量
#include <sstream>
#include <QMessageBox>
#include <QDebug>
#include "DlgRouteManage.h"
#include "DlgRouteParam.h"
#include "DlgLightParam.h"
#include <mutex>
#include <condition_variable>
//提供了高层次的函数接口 (APIs)，使得编写的程序，可根据当前计算机中实际的 CPU 核数，自动调整运行的线程数目。
#define DelayTime 2000
CRouteManager::CRouteManager():
    m_funErrorInfo(nullptr),
    m_funRunStatus(nullptr),
    m_funCameraStationParamSet(nullptr),//状态回调
    m_bInitMotionSuc(false),
    m_bEnableMotionSuc(false),
    m_bMotionGoHomeSuc(false),
    m_bMotionResetSuc(false),
    m_bMotionStartSuc(false),
    m_bMotionStopSuc(false),
    m_bLoadRouteParamSuc(false),
    m_bIsThreadContinueRun(false),
    m_bCodeValid(false),
    m_bCodeType(false),
    m_bStartMotionSignalRead(false),
    m_bMototionEmergency(false),
    m_bIsMotionInspectAuto(false),
    m_bFrontRunSuc(true),
    m_bBackRunSuc(true),
    m_iThreadContinueRunType(-1),
    m_iSchmaModelIndex(0)
{
    ///////初始化轨迹参数/////////
    m_iPublicLong = 150800;
    m_iPublicWidth = 75500;
	m_MyLength = 48150;
    m_sProductType = -1;//1为XR 0为8
    m_isEnableCheckDoor = false;
    m_bFloodlightOn = false;
    //初始化固定变量
    //path1
    m_iFrontVel = 0;
    m_iFrontAcc = 0;
    //path2
    m_iFrameVel = 0;
    m_iFrameAcc = 0;
    m_iFrameCornerVel = 0;
    m_iFrameCornerAcc = 0;
    //path3
    m_iUpDownCameraVel = 0;
    m_iUpDownCameraAcc = 0;
    //path4
    m_iBackVel = 0;
    m_iBackAcc = 0;
    //path5
    m_iLineVel = 0;
    m_iLineVel = 0;
    //Fixed Point
    m_iP1 = 0;//正背同轴光
    m_iP2 = 0;//背面摄像头
    m_iP3 = 0;//中框同轴光
    m_iP4 = 0;//翻转机构900000-770
    m_iP5 = 0;//取点
    m_iFrontGrat = 0;
    m_iBackGrat = 0;
    m_iLightOpen = 0;
    m_iCircle14 = 0;
    m_iRunBackOffSetY = 0;

    //初始化成员变量
    m_iLong = 0;
    m_iWidth = 0;
    m_iFrontBackImageHeight = 0;
    m_iRunBackOffSetY = 0;

    m_iFrontOffSetX = 0;
    m_iFrontOffSetY = 0;
    m_iFrontOffSetZ = 0;

    m_iLisenerX = 0;
    m_iLisenerY = 0;
    m_iLisenerZ = 0;

    m_iCylinderCameraX = 0;
    m_iCylinderCameraY = 0;
    m_iCylinderCameraZ = 0;
    m_iFrameStep = 0;
    m_iFrameOffSetX1 = 0;
    m_iFrameOffSetY1 = 0;
    m_iFrameOffSetZ1 = 0;
    m_iFrameOffSetX2 = 0;
    m_iFrameOffSetY2 = 0;
    m_iFrameOffSetZ2 = 0;
    m_iFrameOffSetX3 = 0;
    m_iFrameOffSetY3 = 0;
    m_iFrameOffSetZ3 = 0;
    m_iFrameOffSetX4 = 0;
    m_iFrameOffSetY4 = 0;
    m_iFrameOffSetZ4 = 0;

    m_iFrameCornerOffSetX1 = 0;
    m_iFrameCornerOffSetY1 = 0;
    m_iFrameCornerOffSetZ1 = 0;
    m_iFrameCornerOffSetX2 = 0;
    m_iFrameCornerOffSetY2 = 0;
    m_iFrameCornerOffSetZ2 = 0;
    m_iFrameCornerOffSetX3 = 0;
    m_iFrameCornerOffSetY3 = 0;
    m_iFrameCornerOffSetZ3 = 0;
    m_iFrameCornerOffSetX4 = 0;
    m_iFrameCornerOffSetY4 = 0;
    m_iFrameCornerOffSetZ4 = 0;

    m_iCylinderOffSetX = 0;
    m_iCylinderOffSetY = 0;
    m_iCylinderOffSetZ = 0;

    m_iCameraOffSetX = 0;
    m_iCameraOffSetY = 0;
    m_iCameraOffSetZ = 0;
    m_iFlashOffSetX = 0;
    m_iFlashOffSetY = 0;
    m_iFlashOffSetZ = 0;

    m_iBackOffSetX = 0;
    m_iBackOffSetY = 0;
    m_iBackOffSetZ = 0;
    m_iBackOffSetX1 = 0;
    m_iBackOffSetY1 = 0;
    m_iBackOffSetZ1 = 0;

    //Points
    m_iResetPointOffSetX = 0;
    m_iResetPointOffSetY = 0;
    m_iResetPointOffSetZ = 0;

    m_iGetPointOffSetX = 0;
    m_iGetPointOffSetY = 0;
    m_iGetPointOffSetZ = 0;
    //FrameSteps
    for(int i =0;i < 20;i++)
    {
        m_iStep1[i] = 0;
        m_iStep2[i] = 0;
        m_iStep3[i] = 0;
        m_iStep4[i] = 0;
    }
    for(int i =0;i < 4;i++)
    {
        m_iStepCount[i] = 0;
        m_iStepLength[i] = 0;
    }

    //光源
    m_iCameraLightIntensity = 0;
    for(int i =0;i<13;i++)
    {
        m_dPulseWidth[i] = 0.0;
        m_dPulseDelay[i] = 0.0;
        m_dCurrent[i] = 0.0;
        m_dRetriggerDelay[i] = 0.0;
    }
    m_vecLightParamInfo.clear();
    //曝光
    for(int i =0;i < 6;i++)
    {
        m_bExposureValid[i] = false;
        m_bGainValid[i] = false;
        m_fExposureTime[i] = -1.0;
        m_iStationNo[i] = -1;
        m_iCameraNo[i] = -1;
        m_fExposureTimeOld[i] = -2.0;
        m_fGain[i] = -1.0;
        m_fGainOld[i] = -2.0;
    }
    qRegisterMetaType<e_StatusInfoType>("e_StatusInfoType");

    m_eRouteControlStatus = eRCS_Exception;
    for(int i = 0;i< MAX_ROUTEMOTION_AXISCOUNT;i++)
    {
        m_bEnableAxsisSuc[i] = false;
    }

    m_iMotionCrdNumber = 1;

    //背面相关参数
    m_bBackTwice = false;
    m_bRecheckFrame = false;
    m_bPressStart = false;
    m_bPressStop = false;
    m_bPressReset = false;
    m_bPressEmergentStop = false;
    m_bPressRunFront = false;
    m_bPressRunBack = false;
    m_bIsLeftFrontDoorClosed = false;
    m_bIsLeftBackDoorClosed = false;
    m_bIsRightFrontDoorClosed = false;
    m_bIsRightBackDoorClosed = false;

    connect(this,&CRouteManager::signalSentMessageInfomation,this,&CRouteManager::slotGetMessageInfomation,Qt::BlockingQueuedConnection);


    m_HandleWaitForColor = CreateEvent(NULL,FALSE,FALSE,NULL);

}
CRouteManager::~CRouteManager()
{
    if(m_sMotionControl.bEnableMotion)
    {
        m_GardasoftLight.Close();
    }
    CloseHandle(m_HandleWaitForColor);
}
bool CRouteManager::SetCodeValid(bool flag)
{
    if(m_bCodeType)
    {
        m_MutexCodeValid.lock();
        m_bCodeValid = flag;
        m_MutexCodeValid.unlock();
        return true;
    }
    return false;

}
void CRouteManager::SetCodeType(bool flag)
{
    m_bCodeType = flag;
}
bool CRouteManager::InitRoutePath(QString strSchmaPath,QString strRoutePath,bool bRecheckFrame)
{
    m_bRecheckFrame = bRecheckFrame;
    m_strRoutePath = strRoutePath;
    m_strSchmaPath = strSchmaPath;
    CQtFileOperate FileOperate;
    if(!FileOperate.IsPathExist(strRoutePath))
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "配置文件路径不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::InitRoutePath()";
        m_sErrorInfo.GetTime();

        return false;
    }

    m_strRouteFile = m_strRoutePath + "/RouteConfig.ini";
    if(!FileOperate.IsFileExist(m_strRouteFile))
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "配置文件不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::InitRoutePath()";
        m_sErrorInfo.GetTime();

        return false;
    }

    ReadConfig();
    SaveConfig();
    QStringList emp ;
    bool a[1];
    a[0] = false;
    ReadSchemaConfig("苹果xr",emp,a);
//    ReadSchmaRouteConfig("苹果xr-Test");
//    SaveSchmaRouteConfig();
//    ReadSchmaLightConfig("苹果xr-Test");
//    SaveSchmaLightConfig();
    if(!InitMotionCard())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "运动卡初始化失败";
        m_sErrorInfo.strErrorMark = "CRouteManager::InitRoutePath()";
        m_sErrorInfo.GetTime();

        return false;
    }

    if(!InitPLCCard())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "PLC初始化失败";
        m_sErrorInfo.strErrorMark = "CRouteManager::InitRoutePath()";
        m_sErrorInfo.GetTime();

        return false;
    }
    if(!InitLightDriver())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "光源初始化失败";
        m_sErrorInfo.strErrorMark = "CRouteManager::InitRoutePath()";
        m_sErrorInfo.GetTime();

        return false;
    }

    m_eRouteControlStatus = eRCS_Init;
    SendRouteStatus(m_eRouteControlStatus);
    MessageInformation("准备就绪",false,false);

    m_bStartMotionSignalRead = true;
    QFuture<bool> future = QtConcurrent::run(this, &CRouteManager::ThreadMotionSignalRead);




   
    return true;
}
void CRouteManager::ReadConfig()
{
    QFileInfo fileInfo(m_strRouteFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "运动配置参数不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::ReadConfig";
        return ;
    }
    CQtFileOperate FileOperate;
    m_sPLCControl.bEnablePLC = FileOperate.MyReadPrivateProfileInt("PLCControl","EnablePLC",0,m_strRouteFile);
    m_sPLCControl.iEncoderLineCount = FileOperate.MyReadPrivateProfileInt("PLCControl","EncoderLineCount",0,m_strRouteFile);
    m_sPLCControl.bEnalbeLightAlarm = FileOperate.MyReadPrivateProfileInt("PLCControl","EnableLightAlarm",0,m_strRouteFile);
    m_sPLCControl.bEnableKickOut = FileOperate.MyReadPrivateProfileInt("PLCControl","EnableKickOut",0,m_strRouteFile);
    m_sPLCControl.bEnableStopAlarm = FileOperate.MyReadPrivateProfileInt("PLCControl","EnableStopAlarm",0,m_strRouteFile);


   m_sMotionControl.bEnableMotion = FileOperate.MyReadPrivateProfileInt("MotionControl","EnableMotion",0,m_strRouteFile);
   m_sMotionControl.bEnableMotionExt = FileOperate.MyReadPrivateProfileInt("MotionControl","EnableMotionExt",0,m_strRouteFile);
   m_sMotionControl.iMotionType = FileOperate.MyReadPrivateProfileInt("MotionControl","MotionType",0,m_strRouteFile);
   m_sMotionControl.iMotionCount = FileOperate.MyReadPrivateProfileInt("MotionControl","MotionCount",0,m_strRouteFile);
   m_sMotionControl.strGTExtModulFile = FileOperate.MyReadPrivateProfileString("MotionControl","GTExtModulInitFile","ExtModule.cfg",m_strRouteFile);


   for(int i = 0; i< m_sMotionControl.iMotionCount;i++)
   {
       QString strKey;
       strKey = QString("MotionChannel%1").arg(i);

       m_sMotionControl.iMotionChanne[i] = FileOperate.MyReadPrivateProfileInt("MotionControl",strKey,0,m_strRouteFile);


       strKey = QString("GTInitFile%1").arg(i);
       m_sMotionControl.strGTInitFile[i] = FileOperate.MyReadPrivateProfileString("MotionControl",strKey,"GTS800.cfg",m_strRouteFile);

       strKey = QString("MotionInitFile%1").arg(i);
       m_sMotionControl.strMotionInitFile[i] = FileOperate.MyReadPrivateProfileString("MotionControl",strKey,"MotionCard.ini",m_strRouteFile);

   }


   m_sMotionControl.bEnalbeLightAlarm = FileOperate.MyReadPrivateProfileInt("MotionControl","EnableLightAlarm",0,m_strRouteFile);
   m_sMotionControl.bEnableKickOut = FileOperate.MyReadPrivateProfileInt("MotionControl","EnableKickOut",0,m_strRouteFile);
   m_sMotionControl.bEnableStopAlarm = FileOperate.MyReadPrivateProfileInt("MotionControl","EnableStopAlarm",0,m_strRouteFile);

   //Fixed Point
   m_iP1 = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_p1",0,m_strRouteFile);
   m_iP2 = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_p2",0,m_strRouteFile);
   m_iP3 = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_p3",0,m_strRouteFile);
   m_iP4 = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_p4",0,m_strRouteFile);
   m_iP5 = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_p5",0,m_strRouteFile);
   m_iFrontGrat = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_FrontGrat",0,m_strRouteFile);
   m_iBackGrat = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_BackGrat",0,m_strRouteFile);
   m_iLightOpen = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_LightOpen",0,m_strRouteFile);
   m_iCircle14 = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_Circle14",0,m_strRouteFile);
   m_iRunBackOffSetY = FileOperate.MyReadPrivateProfileInt("FixedPoint","m_RunBackOffSetY",0,m_strRouteFile);

}
bool CRouteManager::ReadSchmaRouteConfig(QString strSchmaName)
{
    m_strSchmaName = strSchmaName;
    QString strSchemaRouteFile =m_strSchmaPath+"/"+m_strSchmaName+"/Schema/Route.ini";
    QFileInfo fileInfo(strSchemaRouteFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "采图方案轨迹参数不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::ReadSchmaRouteConfig";
        return false;
    }
    std::string SchmaRouteConfigPath = strSchemaRouteFile.toStdString();
    CQtFileOperate FileOperate;
    //Dimension
    m_iLong = FileOperate.MyReadPrivateProfileInt("Dimension","Long",0,SchmaRouteConfigPath);
    m_iWidth = FileOperate.MyReadPrivateProfileInt("Dimension","Width",0,SchmaRouteConfigPath);
    m_iFrontBackImageHeight = FileOperate.MyReadPrivateProfileInt("Dimension","FrontBackImageHeight",0,SchmaRouteConfigPath);
    m_sProductType = FileOperate.MyReadPrivateProfileInt("Dimension","ProductType",0,SchmaRouteConfigPath);
    //[Point]
    m_iResetPointOffSetX=FileOperate.MyReadPrivateProfileInt("Point","ResetPointX",0,SchmaRouteConfigPath);
    m_iResetPointOffSetY=FileOperate.MyReadPrivateProfileInt("Point","ResetPointY",0,SchmaRouteConfigPath);
    m_iResetPointOffSetZ=FileOperate.MyReadPrivateProfileInt("Point","ResetPointZ",0,SchmaRouteConfigPath);
    m_iGetPointOffSetX=FileOperate.MyReadPrivateProfileInt("Point","GetPointX",0,SchmaRouteConfigPath);
    m_iGetPointOffSetY=FileOperate.MyReadPrivateProfileInt("Point","GetPointY",0,SchmaRouteConfigPath);
    m_iGetPointOffSetZ=FileOperate.MyReadPrivateProfileInt("Point","GetPointZ",0,SchmaRouteConfigPath);
    //[Path1]
    m_iFrontOffSetX=FileOperate.MyReadPrivateProfileInt("Path1","FrontOffSetX",0,SchmaRouteConfigPath);
    m_iFrontOffSetY=FileOperate.MyReadPrivateProfileInt("Path1","FrontOffSetY",0,SchmaRouteConfigPath);
    m_iFrontOffSetZ=FileOperate.MyReadPrivateProfileInt("Path1","FrontOffSetZ",0,SchmaRouteConfigPath);
    //[Lisener]
    m_iLisenerX=FileOperate.MyReadPrivateProfileInt("Path1","LisenerX",0,SchmaRouteConfigPath);
    m_iLisenerY=FileOperate.MyReadPrivateProfileInt("Path1","LisenerY",0,SchmaRouteConfigPath);
    m_iLisenerZ=FileOperate.MyReadPrivateProfileInt("Path1","LisenerZ",0,SchmaRouteConfigPath);
    //[Path2]
    m_iCylinderCameraX=FileOperate.MyReadPrivateProfileInt("Path2","CylinderCameraX",0,SchmaRouteConfigPath);
    m_iCylinderCameraY=FileOperate.MyReadPrivateProfileInt("Path2","CylinderCameraY",0,SchmaRouteConfigPath);
    m_iCylinderCameraZ=FileOperate.MyReadPrivateProfileInt("Path2","CylinderCameraZ",0,SchmaRouteConfigPath);
    m_iFrameStep = FileOperate.MyReadPrivateProfileInt("Path2","FrameStep",0,SchmaRouteConfigPath);
    m_iFrameOffSetX1=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetX1",0,SchmaRouteConfigPath);
    m_iFrameOffSetY1=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetY1",0,SchmaRouteConfigPath);
    m_iFrameOffSetZ1=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetZ1",0,SchmaRouteConfigPath);
    m_iFrameOffSetX2=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetX2",0,SchmaRouteConfigPath);
    m_iFrameOffSetY2=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetY2",0,SchmaRouteConfigPath);
    m_iFrameOffSetZ2=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetZ2",0,SchmaRouteConfigPath);
    m_iFrameOffSetX3=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetX3",0,SchmaRouteConfigPath);
    m_iFrameOffSetY3=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetY3",0,SchmaRouteConfigPath);
    m_iFrameOffSetZ3=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetZ3",0,SchmaRouteConfigPath);
    m_iFrameOffSetX4=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetX4",0,SchmaRouteConfigPath);
    m_iFrameOffSetY4=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetY4",0,SchmaRouteConfigPath);
    m_iFrameOffSetZ4=FileOperate.MyReadPrivateProfileInt("Path2","FrameOffSetZ4",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetX1 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetX1",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetY1 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetY1",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetZ1 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetZ1",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetX2 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetX2",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetY2 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetY2",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetZ2 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetZ2",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetX3 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetX3",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetY3 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetY3",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetZ3 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetZ3",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetX4 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetX4",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetY4 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetY4",0,SchmaRouteConfigPath);
    m_iFrameCornerOffSetZ4 = FileOperate.MyReadPrivateProfileInt("Path2","FrameCornerOffSetZ4",0,SchmaRouteConfigPath);
    //[Path3]
    m_iCylinderOffSetX=FileOperate.MyReadPrivateProfileInt("Path3","CylinderOffSetX",0,SchmaRouteConfigPath);
    m_iCylinderOffSetY=FileOperate.MyReadPrivateProfileInt("Path3","CylinderOffSetY",0,SchmaRouteConfigPath);
    m_iCylinderOffSetZ=FileOperate.MyReadPrivateProfileInt("Path3","CylinderOffSetZ",0,SchmaRouteConfigPath);
    m_iCameraOffSetX = FileOperate.MyReadPrivateProfileInt("Path3","CameraOffSetX",0,SchmaRouteConfigPath);
    m_iCameraOffSetY = FileOperate.MyReadPrivateProfileInt("Path3","CameraOffSetY",0,SchmaRouteConfigPath);
    m_iCameraOffSetZ = FileOperate.MyReadPrivateProfileInt("Path3","CameraOffSetZ",0,SchmaRouteConfigPath);
    m_iFlashOffSetX = FileOperate.MyReadPrivateProfileInt("Path3","FlashX",0,SchmaRouteConfigPath);
    m_iFlashOffSetY = FileOperate.MyReadPrivateProfileInt("Path3","FlashY",0,SchmaRouteConfigPath);
    m_iFlashOffSetZ = FileOperate.MyReadPrivateProfileInt("Path3","FlashZ",0,SchmaRouteConfigPath);
    //[Path4]
    m_iBackOffSetX = FileOperate.MyReadPrivateProfileInt("Path4","BackOffSetX",0,SchmaRouteConfigPath);
    m_iBackOffSetY = FileOperate.MyReadPrivateProfileInt("Path4","BackOffSetY",0,SchmaRouteConfigPath);
    m_iBackOffSetZ = FileOperate.MyReadPrivateProfileInt("Path4","BackOffSetZ",0,SchmaRouteConfigPath);
    m_iBackOffSetX1 = FileOperate.MyReadPrivateProfileInt("Path4","BackOffSetX1",0,SchmaRouteConfigPath);
    m_iBackOffSetY1 = FileOperate.MyReadPrivateProfileInt("Path4","BackOffSetY1",0,SchmaRouteConfigPath);
    m_iBackOffSetZ1 = FileOperate.MyReadPrivateProfileInt("Path4","BackOffSetZ1",0,SchmaRouteConfigPath);
    //FrameSteps
    for(int i = 1;i < 5; i++)
    {
        std::stringstream ss;
        std::string strApp;
        ss<<"FrameStep";
        ss<<i;
        ss>>strApp;
        m_iStepCount[i-1] = FileOperate.MyReadPrivateProfileInt(strApp,"StepCount",0,SchmaRouteConfigPath);
        m_iStepLength[i-1] = FileOperate.MyReadPrivateProfileInt(strApp,"StepLength",0,SchmaRouteConfigPath);
        switch (i)
        {
        case 1:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                m_iStep1[i] = FileOperate.MyReadPrivateProfileInt(strApp,strKey,0,SchmaRouteConfigPath);;
            }
            continue;
        case 2:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                m_iStep2[i] = FileOperate.MyReadPrivateProfileInt(strApp,strKey,0,SchmaRouteConfigPath);;
            }
            continue;
        case 3:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                m_iStep3[i] = FileOperate.MyReadPrivateProfileInt(strApp,strKey,0,SchmaRouteConfigPath);;
            }
            continue;
        case 4:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                m_iStep4[i] = FileOperate.MyReadPrivateProfileInt(strApp,strKey,0,SchmaRouteConfigPath);;
            }
            continue;
        default:
            continue;
        }
    }
    return true;
}
//
bool CRouteManager::ReadSchemaConfig(QString strSchmaName,QStringList ListSchemaModelName,bool *bBackTwice)
{
	//读取轨迹
	ReadSchmaRouteConfig(strSchmaName);
    //读取之前重置
    m_vecLightParamInfo.clear();
    m_listSchemaModelName.clear();
    //按默认读取，无默认返回false
    QString strSchemaModelName = "Default";
    m_strSchmaName = strSchmaName;
    m_listSchemaModelName.push_back(strSchemaModelName);
    for(int i = 0;i < ListSchemaModelName.size();i++)
    {
        m_listSchemaModelName.push_back(ListSchemaModelName.at(i));
    }
    QString strSchemaLightFile = m_strSchmaPath + "/" + m_strSchmaName + QString("/Schema/Light-%1.ini").arg(strSchemaModelName);
    QFileInfo fileInfo(strSchemaLightFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "采图方案默认光源参数路径不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::ReadSchmaConfig";
        m_sErrorInfo.GetTime();
        return false;
    }
    CQtFileOperate FileOperate;
    /*以下为光源参数*/
    s_LightParamInfo defalutLightParamInfo;
    defalutLightParamInfo.bBackTwice = false;//背面参数
    defalutLightParamInfo.strSchemaModelName = strSchemaModelName;
    std::string SchmaLightConfigPath = strSchemaLightFile.toStdString();
    //GardSoft
    s_Gardsoftparam sGardsoftparam;
    for(int i = 0;i < 13; i++)
    {
        std::stringstream ss;
        std::string strApp;
        ss<<"Channel";
        ss<<i;
        ss>>strApp;
        sGardsoftparam.dPulseWidth = FileOperate.MyReadPrivateProfileDouble(strApp,"PulseWidth",0,SchmaLightConfigPath);
        sGardsoftparam.dPulseDelay = FileOperate.MyReadPrivateProfileDouble(strApp,"PulseDelay",0,SchmaLightConfigPath);
        sGardsoftparam.dCurrent = FileOperate.MyReadPrivateProfileDouble(strApp,"Current",0,SchmaLightConfigPath);
        sGardsoftparam.dRetriggerDelay = FileOperate.MyReadPrivateProfileDouble(strApp,"RetriggerDelay",0,SchmaLightConfigPath);
        defalutLightParamInfo.vecGardSoftParam.push_back(sGardsoftparam);
    }
    //RSee
    m_iCameraLightIntensity = FileOperate.MyReadPrivateProfileInt("RSeeParam","CameraLightIntensity",0,SchmaLightConfigPath);
    defalutLightParamInfo.vecRSeeParam.push_back(m_iCameraLightIntensity);
    /*以下为曝光参数*///背面摄像头  中框上 中框下  前置摄像头  前听筒
    defalutLightParamInfo.bExposureValid[0] = FileOperate.MyReadPrivateProfileBool("CameraFocus", "ExposureValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fExposureTime[0] = FileOperate.MyReadPrivateProfileDouble("CameraFocus", "ExposureTime", 0, SchmaLightConfigPath);
    defalutLightParamInfo.bGainValid[0] = FileOperate.MyReadPrivateProfileBool("CameraFocus", "GainValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fGain[0] = FileOperate.MyReadPrivateProfileDouble("CameraFocus", "Gain", 0, SchmaLightConfigPath);
    defalutLightParamInfo.bExposureValid[1] = FileOperate.MyReadPrivateProfileBool("CameraFrameUp","ExposureValid",0,SchmaLightConfigPath);
    defalutLightParamInfo.fExposureTime[1] = FileOperate.MyReadPrivateProfileDouble("CameraFrameUp","ExposureTime",0,SchmaLightConfigPath);
    defalutLightParamInfo.bGainValid[1] = FileOperate.MyReadPrivateProfileBool("CameraFrameUp", "GainValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fGain[1] = FileOperate.MyReadPrivateProfileDouble("CameraFrameUp", "Gain", 0, SchmaLightConfigPath);
    defalutLightParamInfo.bExposureValid[2] = FileOperate.MyReadPrivateProfileBool("CameraFrameDown","ExposureValid",0,SchmaLightConfigPath);
    defalutLightParamInfo.fExposureTime[2] = FileOperate.MyReadPrivateProfileDouble("CameraFrameDown","ExposureTime",0,SchmaLightConfigPath);
    defalutLightParamInfo.bGainValid[2] = FileOperate.MyReadPrivateProfileBool("CameraFrameDown", "GainValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fGain[2] = FileOperate.MyReadPrivateProfileDouble("CameraFrameDown", "Gain", 0, SchmaLightConfigPath);

    defalutLightParamInfo.bExposureValid[3] = FileOperate.MyReadPrivateProfileBool("CameraFocus1","ExposureValid",0,SchmaLightConfigPath);
    defalutLightParamInfo.fExposureTime[3] = FileOperate.MyReadPrivateProfileDouble("CameraFocus1","ExposureTime",0,SchmaLightConfigPath);
    defalutLightParamInfo.bGainValid[3] = FileOperate.MyReadPrivateProfileBool("CameraFocus1", "GainValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fGain[3] = FileOperate.MyReadPrivateProfileDouble("CameraFocus1", "Gain", 0, SchmaLightConfigPath);

    defalutLightParamInfo.bExposureValid[4] = FileOperate.MyReadPrivateProfileBool("CameraNew","ExposureValid",0,SchmaLightConfigPath);
    defalutLightParamInfo.fExposureTime[4] = FileOperate.MyReadPrivateProfileDouble("CameraNew","ExposureTime",0,SchmaLightConfigPath);
    defalutLightParamInfo.bGainValid[4] = FileOperate.MyReadPrivateProfileBool("CameraNew", "GainValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fGain[4] = FileOperate.MyReadPrivateProfileDouble("CameraNew", "Gain", 0, SchmaLightConfigPath);

    defalutLightParamInfo.bExposureValid[5] = FileOperate.MyReadPrivateProfileBool("CameraFlash","ExposureValid",0,SchmaLightConfigPath);
    defalutLightParamInfo.fExposureTime[5] = FileOperate.MyReadPrivateProfileDouble("CameraFlash","ExposureTime",0,SchmaLightConfigPath);
    defalutLightParamInfo.bGainValid[5] = FileOperate.MyReadPrivateProfileBool("CameraFlash", "GainValid", 0, SchmaLightConfigPath);
    defalutLightParamInfo.fGain[5] = FileOperate.MyReadPrivateProfileDouble("CameraFlash", "Gain", 0, SchmaLightConfigPath);
    /*以下为速度、加速度参数*/
    /*以下为速度、加速度参数*/
    //path1
    defalutLightParamInfo.iFrontVel = FileOperate.MyReadPrivateProfileInt("Path1Control","FrontVel",0,SchmaLightConfigPath);
    defalutLightParamInfo.iFrontAcc = FileOperate.MyReadPrivateProfileInt("Path1Control","FrontAcc",0,SchmaLightConfigPath);
    //path2
    defalutLightParamInfo.iFrameVel = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameVel",0,SchmaLightConfigPath);
    defalutLightParamInfo.iFrameAcc = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameAcc",0,SchmaLightConfigPath);
    defalutLightParamInfo.iFrameCornerVel = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameCornerVel",0,SchmaLightConfigPath);
    defalutLightParamInfo.iFrameCornerAcc = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameCornerAcc",0,SchmaLightConfigPath);
    //path3
    defalutLightParamInfo.iUpDownCameraVel = FileOperate.MyReadPrivateProfileInt("Path3Control","UpDownCameraVel",0,SchmaLightConfigPath);
    defalutLightParamInfo.iUpDownCameraAcc = FileOperate.MyReadPrivateProfileInt("Path3Control","UpDownCameraAcc",0,SchmaLightConfigPath);
    //path4
    defalutLightParamInfo.iBackVel = FileOperate.MyReadPrivateProfileInt("Path4Control","BackVel",0,SchmaLightConfigPath);
    defalutLightParamInfo.iBackAcc = FileOperate.MyReadPrivateProfileInt("Path4Control","BackAcc",0,SchmaLightConfigPath);
    //path5
    defalutLightParamInfo.iLineVel = FileOperate.MyReadPrivateProfileInt("Path5Control","LineVel",0,SchmaLightConfigPath);
    defalutLightParamInfo.iLineAcc = FileOperate.MyReadPrivateProfileInt("Path5Control","LineAcc",0,SchmaLightConfigPath);
    m_vecLightParamInfo.push_back(defalutLightParamInfo);
    //依次读取ListSchemaModelName，无有也返回true，按默认参数进行
    for(int i = 1;i < m_listSchemaModelName.size();i++)
    {
        strSchemaModelName = m_listSchemaModelName.at(i);
        strSchemaLightFile = m_strSchmaPath + "/" + m_strSchmaName + QString("/Schema/Light-%1.ini").arg(strSchemaModelName);
        QFileInfo fileInfo(strSchemaLightFile);
        if(!fileInfo.isFile())
        {
            defalutLightParamInfo.strSchemaModelName = strSchemaModelName;
            m_vecLightParamInfo.push_back(defalutLightParamInfo);
            continue;
        }
        s_LightParamInfo LightParamInfo;
        LightParamInfo.bBackTwice = bBackTwice[i-1];//背面相关参数
        LightParamInfo.strSchemaModelName = strSchemaModelName;
        std::string SchmaLightConfigPath = strSchemaLightFile.toStdString();
        CQtFileOperate FileOperate;
        //GardSoft
        s_Gardsoftparam sGardsoftparam;
        for(int i = 0;i < 13; i++)
        {
            std::stringstream ss;
            std::string strApp;
            ss<<"Channel";
            ss<<i;
            ss>>strApp;
            sGardsoftparam.dPulseWidth = FileOperate.MyReadPrivateProfileDouble(strApp,"PulseWidth",0,SchmaLightConfigPath);
            sGardsoftparam.dPulseDelay = FileOperate.MyReadPrivateProfileDouble(strApp,"PulseDelay",0,SchmaLightConfigPath);
            sGardsoftparam.dCurrent = FileOperate.MyReadPrivateProfileDouble(strApp,"Current",0,SchmaLightConfigPath);
            sGardsoftparam.dRetriggerDelay = FileOperate.MyReadPrivateProfileDouble(strApp,"RetriggerDelay",0,SchmaLightConfigPath);
            LightParamInfo.vecGardSoftParam.push_back(sGardsoftparam);
        }
        //RSee
        m_iCameraLightIntensity = FileOperate.MyReadPrivateProfileInt("RSeeParam","CameraLightIntensity",0,SchmaLightConfigPath);
        LightParamInfo.vecRSeeParam.push_back(m_iCameraLightIntensity);
        /*以下为曝光参数*/
        LightParamInfo.bExposureValid[0] = FileOperate.MyReadPrivateProfileBool("CameraFocus", "ExposureValid", 0, SchmaLightConfigPath);
        LightParamInfo.fExposureTime[0] = FileOperate.MyReadPrivateProfileDouble("CameraFocus", "ExposureTime", 0, SchmaLightConfigPath);
        LightParamInfo.bGainValid[0] = FileOperate.MyReadPrivateProfileBool("CameraFocus", "GainValid", 0, SchmaLightConfigPath);
        LightParamInfo.fGain[0] = FileOperate.MyReadPrivateProfileDouble("CameraFocus", "Gain", 0, SchmaLightConfigPath);
        LightParamInfo.bExposureValid[1] = FileOperate.MyReadPrivateProfileBool("CameraFrameUp","ExposureValid",0,SchmaLightConfigPath);
        LightParamInfo.fExposureTime[1] = FileOperate.MyReadPrivateProfileDouble("CameraFrameUp","ExposureTime",0,SchmaLightConfigPath);
        LightParamInfo.bGainValid[1] = FileOperate.MyReadPrivateProfileBool("CameraFrameUp", "GainValid", 0, SchmaLightConfigPath);
        LightParamInfo.fGain[1] = FileOperate.MyReadPrivateProfileDouble("CameraFrameUp", "Gain", 0, SchmaLightConfigPath);
        LightParamInfo.bExposureValid[2] = FileOperate.MyReadPrivateProfileBool("CameraFrameDown","ExposureValid",0,SchmaLightConfigPath);
        LightParamInfo.fExposureTime[2] = FileOperate.MyReadPrivateProfileDouble("CameraFrameDown","ExposureTime",0,SchmaLightConfigPath);
        LightParamInfo.bGainValid[2] = FileOperate.MyReadPrivateProfileBool("CameraFrameDown", "GainValid", 0, SchmaLightConfigPath);
        LightParamInfo.fGain[2] = FileOperate.MyReadPrivateProfileDouble("CameraFrameDown", "Gain", 0, SchmaLightConfigPath);

		LightParamInfo.bExposureValid[3] = FileOperate.MyReadPrivateProfileBool("CameraFocus1","ExposureValid",0,SchmaLightConfigPath);
		LightParamInfo.fExposureTime[3] = FileOperate.MyReadPrivateProfileDouble("CameraFocus1","ExposureTime",0,SchmaLightConfigPath);
		LightParamInfo.bGainValid[3] = FileOperate.MyReadPrivateProfileBool("CameraFocus1", "GainValid", 0, SchmaLightConfigPath);
		LightParamInfo.fGain[3] = FileOperate.MyReadPrivateProfileDouble("CameraFocus1", "Gain", 0, SchmaLightConfigPath);

		LightParamInfo.bExposureValid[4] = FileOperate.MyReadPrivateProfileBool("CameraNew","ExposureValid",0,SchmaLightConfigPath);
		LightParamInfo.fExposureTime[4] = FileOperate.MyReadPrivateProfileDouble("CameraNew","ExposureTime",0,SchmaLightConfigPath);
		LightParamInfo.bGainValid[4] = FileOperate.MyReadPrivateProfileBool("CameraNew", "GainValid", 0, SchmaLightConfigPath);
		LightParamInfo.fGain[4] = FileOperate.MyReadPrivateProfileDouble("CameraNew", "Gain", 0, SchmaLightConfigPath);

        LightParamInfo.bExposureValid[5] = FileOperate.MyReadPrivateProfileBool("CameraFlash","ExposureValid",0,SchmaLightConfigPath);
        LightParamInfo.fExposureTime[5] = FileOperate.MyReadPrivateProfileDouble("CameraFlash","ExposureTime",0,SchmaLightConfigPath);
        LightParamInfo.bGainValid[5] = FileOperate.MyReadPrivateProfileBool("CameraFlash", "GainValid", 0, SchmaLightConfigPath);
        LightParamInfo.fGain[5] = FileOperate.MyReadPrivateProfileDouble("CameraFlash", "Gain", 0, SchmaLightConfigPath);
        /*以下为速度、加速度参数*/
        //path1
        LightParamInfo.iFrontVel = FileOperate.MyReadPrivateProfileInt("Path1Control","FrontVel",0,SchmaLightConfigPath);
        LightParamInfo.iFrontAcc = FileOperate.MyReadPrivateProfileInt("Path1Control","FrontAcc",0,SchmaLightConfigPath);
        //path2
        LightParamInfo.iFrameVel = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameVel",0,SchmaLightConfigPath);
        LightParamInfo.iFrameAcc = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameAcc",0,SchmaLightConfigPath);
        LightParamInfo.iFrameCornerVel = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameCornerVel",0,SchmaLightConfigPath);
        LightParamInfo.iFrameCornerAcc = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameCornerAcc",0,SchmaLightConfigPath);
        //path3
        LightParamInfo.iUpDownCameraVel = FileOperate.MyReadPrivateProfileInt("Path3Control","UpDownCameraVel",0,SchmaLightConfigPath);
        LightParamInfo.iUpDownCameraAcc = FileOperate.MyReadPrivateProfileInt("Path3Control","UpDownCameraAcc",0,SchmaLightConfigPath);
        //path4
        LightParamInfo.iBackVel = FileOperate.MyReadPrivateProfileInt("Path4Control","BackVel",0,SchmaLightConfigPath);
        LightParamInfo.iBackAcc = FileOperate.MyReadPrivateProfileInt("Path4Control","BackAcc",0,SchmaLightConfigPath);
        //path5
        LightParamInfo.iLineVel = FileOperate.MyReadPrivateProfileInt("Path5Control","LineVel",0,SchmaLightConfigPath);
        LightParamInfo.iLineAcc = FileOperate.MyReadPrivateProfileInt("Path5Control","LineAcc",0,SchmaLightConfigPath);
        m_vecLightParamInfo.push_back(LightParamInfo);
    }
	//
	SetCurrentSchemaModelName("Default");

    return true;
}
bool CRouteManager::SetCurrentSchemaModelName(QString strSchemaModelName)
{
    //有，返回true
    qDebug()<<"CRouteManager-ModelNameSetting"<<strSchemaModelName;
    if(m_listSchemaModelName.contains(strSchemaModelName))
    {
        FindAndSetSchemaModelParam(FindLightParamInfo(strSchemaModelName));

        if(strSchemaModelName != "Default")
        {

            SetEvent(m_HandleWaitForColor);
        }

        return true;
    }
    else    //无有，按默认参数进行，返回false
    {
        FindAndSetSchemaModelParam(m_vecLightParamInfo.at(0));

        if(strSchemaModelName != "Default")
        {

            SetEvent(m_HandleWaitForColor);
        }
        return false;
    }
}
void CRouteManager::SetStationNoAndCameraNo(int *piStationNo,int *piCameraNo,int size)
{//后摄像头、中框上、中框下面阵、前摄像头、前听筒、闪光灯
    memcpy(m_iStationNo,piStationNo,size*sizeof(int));
    memcpy(m_iCameraNo,piCameraNo,size*sizeof(int));
    m_iStationNo[4] = m_iStationNo[3];
    m_iCameraNo[4] = m_iCameraNo[3];
    m_iStationNo[3] = m_iStationNo[0];
    m_iCameraNo[3] = m_iCameraNo[0];
    m_iStationNo[5] = m_iStationNo[4];
    m_iCameraNo[5] = m_iCameraNo[4];
}
s_LightParamInfo &CRouteManager::FindLightParamInfo(QString strSchemaModelName)
{
    for(int i = 1;i < m_vecLightParamInfo.size() ;i++)
    {
        if(m_vecLightParamInfo.at(i).strSchemaModelName == strSchemaModelName)
        {
            m_iSchmaModelIndex = i;
            return m_vecLightParamInfo.at(i);
        }
    }
    m_iSchmaModelIndex = 0;
    return m_vecLightParamInfo.at(0);
}
bool CRouteManager::SaveSchemaConfig(QString strSchemaModelName)
{
    QString strSchemaLightFile = m_strSchmaPath + "/" + m_strSchmaName + QString("/Schema/Light-%1.ini").arg(strSchemaModelName);
//    QFileInfo fileInfo(strSchemaLightFile);
//    if(!fileInfo.isFile())
//    {
//        m_sErrorInfo.iErrorCode = 1;
//        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
//        m_sErrorInfo.strErrorDes = "采图方案默认光源参数路径不存在";
//        m_sErrorInfo.strErrorMark = "CRouteManager::SaveSchmaConfig";
//        m_sErrorInfo.GetTime();
//        return false;
//    }
    CQtFileOperate FileOperate;
    /*以下为光源参数*/
    s_LightParamInfo LightParamInfo = FindLightParamInfo(strSchemaModelName);
    std::string SchmaLightConfigPath = strSchemaLightFile.toStdString();
    //GardSoft
    for(int i = 0;i < 13; i++)
    {
        std::stringstream ss;
        std::string strApp;
        ss<<"Channel";
        ss<<i;
        ss>>strApp;
        FileOperate.MyWritePrivateProfileDouble(strApp,"PulseWidth",LightParamInfo.vecGardSoftParam.at(i).dPulseWidth,SchmaLightConfigPath);
        FileOperate.MyWritePrivateProfileDouble(strApp,"PulseDelay",LightParamInfo.vecGardSoftParam.at(i).dPulseDelay,SchmaLightConfigPath);
        FileOperate.MyWritePrivateProfileDouble(strApp,"Current",LightParamInfo.vecGardSoftParam.at(i).dCurrent,SchmaLightConfigPath);
        FileOperate.MyWritePrivateProfileDouble(strApp,"RetriggerDelay",LightParamInfo.vecGardSoftParam.at(i).dRetriggerDelay,SchmaLightConfigPath);
    }
    //RSee
    FileOperate.MyWritePrivateProfileInt("RSeeParam","CameraLightIntensity",LightParamInfo.vecRSeeParam.at(0),SchmaLightConfigPath);
    /*以下为曝光参数*/
    FileOperate.MyWritePrivateProfileBool("CameraFocus", "ExposureValid", LightParamInfo.bExposureValid[0], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFocus", "ExposureTime", LightParamInfo.fExposureTime[0], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFocus", "GainValid", LightParamInfo.bGainValid[0], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFocus", "Gain", LightParamInfo.fGain[0], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFrameUp","ExposureValid",LightParamInfo.bExposureValid[1],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFrameUp","ExposureTime",LightParamInfo.fExposureTime[1],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFrameUp", "GainValid", LightParamInfo.bGainValid[1], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFrameUp", "Gain", LightParamInfo.fGain[1], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFrameDown","ExposureValid",LightParamInfo.bExposureValid[2],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFrameDown","ExposureTime",LightParamInfo.fExposureTime[2],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFrameDown", "GainValid", LightParamInfo.bGainValid[2], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFrameDown", "Gain", LightParamInfo.fGain[2], SchmaLightConfigPath);

    FileOperate.MyWritePrivateProfileBool("CameraFocus1","ExposureValid",LightParamInfo.bExposureValid[3],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFocus1","ExposureTime",LightParamInfo.fExposureTime[3],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFocus1", "GainValid", LightParamInfo.bGainValid[3], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFocus1", "Gain", LightParamInfo.fGain[3], SchmaLightConfigPath);

    FileOperate.MyWritePrivateProfileBool("CameraNew","ExposureValid",LightParamInfo.bExposureValid[4],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraNew","ExposureTime",LightParamInfo.fExposureTime[4],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraNew", "GainValid", LightParamInfo.bGainValid[4], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraNew", "Gain", LightParamInfo.fGain[4], SchmaLightConfigPath);

    FileOperate.MyWritePrivateProfileBool("CameraFlash","ExposureValid",LightParamInfo.bExposureValid[5],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFlash","ExposureTime",LightParamInfo.fExposureTime[5],SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileBool("CameraFlash", "GainValid", LightParamInfo.bGainValid[5], SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileDouble("CameraFlash", "Gain", LightParamInfo.fGain[5], SchmaLightConfigPath);
    /*以下为速度、加速度参数*/
    //path1
    FileOperate.MyWritePrivateProfileInt("Path1Control","FrontVel",LightParamInfo.iFrontVel,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path1Control","FrontAcc",LightParamInfo.iFrontAcc,SchmaLightConfigPath);
    //path2
    FileOperate.MyWritePrivateProfileInt("Path2Control","FrameVel",LightParamInfo.iFrameVel,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2Control","FrameAcc",LightParamInfo.iFrameAcc,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2Control","FrameCornerVel",LightParamInfo.iFrameCornerVel,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2Control","FrameCornerAcc",LightParamInfo.iFrameCornerAcc,SchmaLightConfigPath);
    //path3
    FileOperate.MyWritePrivateProfileInt("Path3Control","UpDownCameraVel",LightParamInfo.iUpDownCameraVel,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3Control","UpDownCameraAcc",LightParamInfo.iUpDownCameraAcc,SchmaLightConfigPath);
    //path4
    FileOperate.MyWritePrivateProfileInt("Path4Control","BackVel",LightParamInfo.iBackVel,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path4Control","BackAcc",LightParamInfo.iBackAcc,SchmaLightConfigPath);
    //path5
    FileOperate.MyWritePrivateProfileInt("Path5Control","LineVel",LightParamInfo.iLineVel,SchmaLightConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path5Control","LineAcc",LightParamInfo.iLineAcc,SchmaLightConfigPath);
    return true;
}
void CRouteManager::FindAndSetSchemaModelParam(const s_LightParamInfo &sLightParamInfo)
{
    m_strSchmaModelName = sLightParamInfo.strSchemaModelName;
    m_iCameraLightIntensity = sLightParamInfo.vecRSeeParam.at(0);
    m_bBackTwice = sLightParamInfo.bBackTwice;
    for(int i = 0;i < 13; i++)
    {
        if(i < 5)
        {
            m_dPulseWidth[i] = m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dPulseWidth;
            m_dPulseDelay[i] = m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dPulseDelay;
            m_dCurrent[i] = m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dCurrent;
            m_dRetriggerDelay[i] = m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dRetriggerDelay;
            continue;
        }
        m_dPulseWidth[i] = sLightParamInfo.vecGardSoftParam.at(i).dPulseWidth;
        m_dPulseDelay[i] = sLightParamInfo.vecGardSoftParam.at(i).dPulseDelay;
        m_dCurrent[i] = sLightParamInfo.vecGardSoftParam.at(i).dCurrent;
        m_dRetriggerDelay[i] = sLightParamInfo.vecGardSoftParam.at(i).dRetriggerDelay;
    }
    memcpy(m_bExposureValid,sLightParamInfo.bExposureValid,6*sizeof(bool));
    memcpy(m_fExposureTime,sLightParamInfo.fExposureTime,6*sizeof(float));
    memcpy(m_bGainValid,sLightParamInfo.bGainValid,6*sizeof(bool));
    memcpy(m_fGain,sLightParamInfo.fGain,6*sizeof(float));
    m_iFrontVel = sLightParamInfo.iFrontVel;
    m_iFrontAcc = sLightParamInfo.iFrontAcc;
    m_iFrameVel = sLightParamInfo.iFrameVel;
    m_iFrameAcc = sLightParamInfo.iFrameAcc;
    m_iFrameCornerVel = sLightParamInfo.iFrameCornerVel;
    m_iFrameCornerAcc = sLightParamInfo.iFrameCornerAcc;
    m_iUpDownCameraVel = sLightParamInfo.iUpDownCameraVel;
    m_iUpDownCameraAcc = sLightParamInfo.iUpDownCameraAcc;
    m_iBackVel = sLightParamInfo.iBackVel;
    m_iBackAcc = sLightParamInfo.iBackAcc;
    m_iLineVel = sLightParamInfo.iLineVel;
    m_iLineAcc = sLightParamInfo.iLineAcc;
}
bool CRouteManager::ReadSchmaLightConfig(QString strSchmaName)
{
    m_strSchmaName = strSchmaName;
    QString strSchemaLightFile = m_strSchmaPath+"/"+m_strSchmaName+"/Schema/Light.ini";
    QFileInfo fileInfo(strSchemaLightFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "采图方案光源参数路径不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::ReadSchmaLightConfig";
        m_sErrorInfo.GetTime();
        return false;
    }
    std::string SchmaLightConfigPath = strSchemaLightFile.toStdString();
    CQtFileOperate FileOperate;
    for(int i = 0;i < 13; i++)
    {
        std::stringstream ss;
        std::string strApp;
        ss<<"Channel";
        ss<<i;
        ss>>strApp;
        m_dPulseWidth[i] = FileOperate.MyReadPrivateProfileDouble(strApp,"PulseWidth",0,SchmaLightConfigPath);
        m_dPulseDelay[i] = FileOperate.MyReadPrivateProfileDouble(strApp,"PulseDelay",0,SchmaLightConfigPath);
        m_dCurrent[i] = FileOperate.MyReadPrivateProfileDouble(strApp,"Current",0,SchmaLightConfigPath);
        m_dRetriggerDelay[i] = FileOperate.MyReadPrivateProfileDouble(strApp,"RetriggerDelay",0,SchmaLightConfigPath);
    }
    return true;
}
bool CRouteManager::SaveSchmaLightConfig()
{
    QString strSchemaLightFile =m_strSchmaPath+"/"+m_strSchmaName+"/Schema/Light.ini";
    QFileInfo fileInfo(strSchemaLightFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "采图方案光源参数路径不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::SaveSchmaLightConfig";
        return false;
    }
    std::string SchmaLightConfigPath = strSchemaLightFile.toStdString();
    CQtFileOperate FileOperate;
    for(int i = 0;i < 13; i++)
    {
        std::stringstream ss;
        std::string strApp;
        ss<<"Channel";
        ss<<i;
        ss>>strApp;
        FileOperate.MyWritePrivateProfileDouble(strApp,"PulseWidth",m_dPulseWidth[i],SchmaLightConfigPath);
        FileOperate.MyWritePrivateProfileDouble(strApp,"PulseDelay",m_dPulseDelay[i],SchmaLightConfigPath);
        FileOperate.MyWritePrivateProfileDouble(strApp,"Current",m_dCurrent[i],SchmaLightConfigPath);
        FileOperate.MyWritePrivateProfileDouble(strApp,"RetriggerDelay",m_dRetriggerDelay[i],SchmaLightConfigPath);
    }
    return true;
}
void CRouteManager::SaveConfig()
{
    QFileInfo fileInfo(m_strRouteFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "运动配置参数不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::SaveConfig";
        return ;
    }
    CQtFileOperate FileOperate;
    FileOperate.MyWritePrivateProfileInt("PLCControl","EnablePLC",m_sPLCControl.bEnablePLC,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("PLCControl","EncoderLineCount",m_sPLCControl.iEncoderLineCount,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("PLCControl","EnableLightAlarm",m_sPLCControl.bEnalbeLightAlarm,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("PLCControl","EnableKickOut",m_sPLCControl.bEnableKickOut,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("PLCControl","EnableStopAlarm",m_sPLCControl.bEnableStopAlarm,m_strRouteFile);



    FileOperate.MyWritePrivateProfileInt("MotionControl","EnableMotion",m_sMotionControl.bEnableMotion,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("MotionControl","MotionType",m_sMotionControl.iMotionType,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("MotionControl","MotionCount",m_sMotionControl.iMotionCount,m_strRouteFile);
    for(int i = 0; i< m_sMotionControl.iMotionCount;i++)
    {
        QString strKey;

        strKey = QString("MotionChannel%1").arg(i);
        FileOperate.MyWritePrivateProfileInt("MotionControl",strKey,m_sMotionControl.iMotionChanne[i],m_strRouteFile);


        strKey = QString("GTInitFile%1").arg(i);
        FileOperate.MyWritePrivateProfileString("MotionControl",strKey,m_sMotionControl.strGTInitFile[i],m_strRouteFile);


        strKey = QString("MotionInitFile%1").arg(i);
        FileOperate.MyWritePrivateProfileString("MotionControl",strKey,m_sMotionControl.strMotionInitFile[i],m_strRouteFile);


    }

    FileOperate.MyWritePrivateProfileInt("MotionControl","EnableLightAlarm",m_sMotionControl.bEnalbeLightAlarm,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("MotionControl","EnableKickOut",m_sMotionControl.bEnableKickOut,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("MotionControl","EnableStopAlarm",m_sMotionControl.bEnableStopAlarm,m_strRouteFile);

    //Fixed Point
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_p1",m_iP1,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_p2",m_iP2,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_p3",m_iP3,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_p4",m_iP4,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_p5",m_iP5,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_FrontGrat",m_iFrontGrat,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_BackGrat",m_iBackGrat,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_LightOpen",m_iLightOpen,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_Circle14",m_iCircle14,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("FixedPoint","m_RunBackOffSetY",m_iRunBackOffSetY,m_strRouteFile);
}
bool CRouteManager::SaveSchmaRouteConfig()
{
    QString strSchemaRouteFile =m_strSchmaPath+"/"+m_strSchmaName+"/Schema/Route.ini";
    QFileInfo fileInfo(strSchemaRouteFile);
    if(!fileInfo.isFile())
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "采图方案轨迹参数不存在";
        m_sErrorInfo.strErrorMark = "CRouteManager::SaveSchmaRouteConfig";
        return false;
    }
    std::string SchmaRouteConfigPath = strSchemaRouteFile.toStdString();
    //std::string SchmaRouteConfigPath = "D:/BZVisualInspect/UserData/Mission/Test/Route.ini";
    CQtFileOperate FileOperate;
    //Dimension
    FileOperate.MyWritePrivateProfileInt("Dimension","Long",m_iLong,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Dimension","Width",m_iWidth,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Dimension","FrontBackImageHeight",m_iFrontBackImageHeight,SchmaRouteConfigPath);
    //[Point]
    FileOperate.MyWritePrivateProfileInt("Point","ResetPointX",m_iResetPointOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Point","ResetPointY",m_iResetPointOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Point","ResetPointZ",m_iResetPointOffSetZ,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Point","GetPointX",m_iGetPointOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Point","GetPointY",m_iGetPointOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Point","GetPointZ",m_iGetPointOffSetZ,SchmaRouteConfigPath);
    //[Path1]
    FileOperate.MyWritePrivateProfileInt("Path1","FrontOffSetX",m_iFrontOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path1","FrontOffSetY",m_iFrontOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path1","FrontOffSetZ",m_iFrontOffSetZ,SchmaRouteConfigPath);
    //[Lisener]
    FileOperate.MyWritePrivateProfileInt("Path1","LisenerX",m_iLisenerX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path1","LisenerY",m_iLisenerY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path1","LisenerZ",m_iLisenerZ,SchmaRouteConfigPath);
    //[Path2]
    FileOperate.MyWritePrivateProfileInt("Path2","CylinderCameraX",m_iCylinderCameraX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","CylinderCameraY",m_iCylinderCameraY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","CylinderCameraZ",m_iCylinderCameraZ,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameStep",m_iFrameStep,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetX1",m_iFrameOffSetX1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetY1",m_iFrameOffSetY1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetZ1",m_iFrameOffSetZ1,SchmaRouteConfigPath);

    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetX2",m_iFrameOffSetX2,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetY2",m_iFrameOffSetY2,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetZ2",m_iFrameOffSetZ2,SchmaRouteConfigPath);

    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetX3",m_iFrameOffSetX3,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetY3",m_iFrameOffSetY3,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetZ3",m_iFrameOffSetZ3,SchmaRouteConfigPath);

    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetX4",m_iFrameOffSetX4,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetY4",m_iFrameOffSetY4,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameOffSetZ4",m_iFrameOffSetZ4,SchmaRouteConfigPath);

    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetX1",m_iFrameCornerOffSetX1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetY1",m_iFrameCornerOffSetY1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetZ1",m_iFrameCornerOffSetZ1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetX2",m_iFrameCornerOffSetX2,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetY2",m_iFrameCornerOffSetY2,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetZ2",m_iFrameCornerOffSetZ2,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetX3",m_iFrameCornerOffSetX3,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetY3",m_iFrameCornerOffSetY3,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetZ3",m_iFrameCornerOffSetZ3,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetX4",m_iFrameCornerOffSetX4,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetY4",m_iFrameCornerOffSetY4,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path2","FrameCornerOffSetZ4",m_iFrameCornerOffSetZ4,SchmaRouteConfigPath);
    //[Path3]
    FileOperate.MyWritePrivateProfileInt("Path3","CylinderOffSetX",m_iCylinderOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","CylinderOffSetY",m_iCylinderOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","CylinderOffSetZ",m_iCylinderOffSetZ,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","CameraOffSetX",m_iCameraOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","CameraOffSetY",m_iCameraOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","CameraOffSetZ",m_iCameraOffSetZ,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","FlashX",m_iFlashOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","FlashY",m_iFlashOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path3","FlashZ",m_iFlashOffSetZ,SchmaRouteConfigPath);
    //[Path4]
    FileOperate.MyWritePrivateProfileInt("Path4","BackOffSetX",m_iBackOffSetX,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path4","BackOffSetY",m_iBackOffSetY,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path4","BackOffSetZ",m_iBackOffSetZ,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path4","BackOffSetX1",m_iBackOffSetX1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path4","BackOffSetY1",m_iBackOffSetY1,SchmaRouteConfigPath);
    FileOperate.MyWritePrivateProfileInt("Path4","BackOffSetZ1",m_iBackOffSetZ1,SchmaRouteConfigPath);
    //FrameSteps
    for(int i = 1;i < 5; i++)
    {
        std::stringstream ss;
        std::string strApp;
        ss<<"FrameStep";
        ss<<i;
        ss>>strApp;
        FileOperate.MyWritePrivateProfileInt(strApp,"StepCount",m_iStepCount[i-1],SchmaRouteConfigPath);
        FileOperate.MyWritePrivateProfileInt(strApp,"StepLength",m_iStepLength[i-1],SchmaRouteConfigPath);
        switch (i)
        {
        case 1:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                FileOperate.MyWritePrivateProfileInt(strApp,strKey,m_iStep1[i],SchmaRouteConfigPath);
            }
            continue;
        case 2:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                FileOperate.MyWritePrivateProfileInt(strApp,strKey,m_iStep2[i],SchmaRouteConfigPath);
            }
            continue;
        case 3:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                FileOperate.MyWritePrivateProfileInt(strApp,strKey,m_iStep3[i],SchmaRouteConfigPath);
            }
            continue;
        case 4:
            for(int i = 0;i < 13 ;i++)
            {
                std::stringstream sss;
                std::string strKey;
                sss<<"Step";
                sss<<i;
                sss>>strKey;
                FileOperate.MyWritePrivateProfileInt(strApp,strKey,m_iStep4[i],SchmaRouteConfigPath);
            }
            continue;
        default:
            continue;
        }
    }
    return true;
}
bool CRouteManager::ReleaseRoute()
{
    if(m_bStartMotionSignalRead)
    {
        m_bStartMotionSignalRead = false;
        m_SemaphoreSignalReadFinish.acquire();
    }
    if(m_bIsThreadContinueRun)
    {
        m_bIsThreadContinueRun = false;
        m_SemaphoreContinueRun.acquire();
    }


    ReleasePLCCard();

    ReleaseMotionCard();
    return true;
}

void CRouteManager::RegeditGetRunStatus(std::function<void(e_RouteControlStatus,int)> funStatusInfo)
{
    m_funRunStatus = funStatusInfo;

}

//注册获取错误回调
void CRouteManager::RegeditGetLastErrorFun(std::function<void(s_ErrorInfo &)> funErrorInfo)
{
    m_funErrorInfo = funErrorInfo;
}
void CRouteManager::RegisterCameraStationParamSet(std::function<bool(int,int,int,float)> CallBackFunc)
{
    m_funCameraStationParamSet = CallBackFunc;
}
bool CRouteManager::SetCameraStationParam(int iStationSN,int iCameraSN,int iType,float fParamValue,int iIndex)
{
    switch(iType)
    {
        case 0:
            if (!m_bExposureValid[iIndex])
            {
                return true;
            }
            if(iIndex==0 || iIndex==3)
            {
                if(m_fExposureTimeOld[0] == fParamValue)
                {
                    return true;
                }
            } else if(iIndex==4 || iIndex==5)
            {
                if(m_fExposureTimeOld[4] == fParamValue)
                {
                    return true;
                }
            }
            else
            {
                if(m_fExposureTimeOld[iIndex] == fParamValue)
                {
                    return true;
                }
            }

            if(m_funCameraStationParamSet != nullptr)
            {
                if(iIndex==0 || iIndex==3)
                {
                    m_fExposureTimeOld[0] = fParamValue;
                } else if(iIndex==4 || iIndex==5)
                {
                    m_fExposureTimeOld[4] = fParamValue;
                }
                else
                {
                    m_fExposureTimeOld[iIndex] = fParamValue;
                }
                qDebug()<<"CRouteManager-GainSetting"<<"工位号"<<iStationSN<<"相机号"<<iCameraSN<<"曝光值"<<fParamValue;
                return m_funCameraStationParamSet(iStationSN,iCameraSN,iType,fParamValue);
            }
            break;
        case 1:
            if (!m_bGainValid[iIndex])
            {
                return true;
            }
            if(iIndex==0 || iIndex==3)
            {
                if(m_fGainOld[0] == fParamValue)
                {
                    return true;
                }
            }
            else if(iIndex==4 || iIndex==5)
            {
                if(m_fGainOld[4] == fParamValue)
                {
                    return true;
                }
            }
            else
            {
                if(m_fGainOld[iIndex] == fParamValue)
                {
                    return true;
                }
            }
            if(m_funCameraStationParamSet != nullptr)
            {
                if(iIndex==0 || iIndex==3)
                {
                    m_fGainOld[0] = fParamValue;
                }
                else if(iIndex==4 || iIndex==5)
                {
                    m_fGainOld[4] = fParamValue;
                }
                else
                {
                    m_fGainOld[iIndex] = fParamValue;
                }
                qDebug()<<"CRouteManager-GainSetting"<<"工位号"<<iStationSN<<"相机号"<<iCameraSN<<"增益值"<<fParamValue;
                return m_funCameraStationParamSet(iStationSN,iCameraSN,iType,fParamValue);
            }
            break;
        default:
            return false;
    }
    return false;
}
//获取最后的异常
const s_ErrorInfo & CRouteManager::GetLastError()
{
    return m_sErrorInfo;
}

 void CRouteManager::SendLastError()
 {
     //return;
     if(m_funErrorInfo != nullptr)
     {
         m_funErrorInfo(m_sErrorInfo);
     }
 }

 void CRouteManager::SendRouteStatus(e_RouteControlStatus eStatus, int iValue)
 {
     //return;
     if(m_funRunStatus != nullptr)
     {
         m_funRunStatus(eStatus,iValue);
     }

 }

 void CRouteManager::MessageInformation(QString strAlarm, bool bMessageBox, bool bAlarm)
 {
     //return;
     if(bMessageBox)
     {
         emit signalSentMessageInfomation(strAlarm);
     }
     else
     {
         if(bAlarm)
         {
             m_sErrorInfo.iErrorCode = 1;
         }
         else
         {
             m_sErrorInfo.iErrorCode = 0;
         }

         m_sErrorInfo.eErrorGrade = eEG_MainShow;
         m_sErrorInfo.strErrorDes = strAlarm.toStdString();
         m_sErrorInfo.strErrorMark = "CRouteManager";
         m_sErrorInfo.GetTime();
         SendLastError();

         if(bAlarm)
         {
             m_sErrorInfo.iErrorCode = 1;
             m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
             m_sErrorInfo.strErrorDes = strAlarm.toStdString();
             m_sErrorInfo.strErrorMark = "CRouteManager";
             m_sErrorInfo.GetTime();
             SendLastError();
         }

     }

 }
 //运动卡回调信息
 void CRouteManager::FunMotionCallBack(int iCallInfo)
 {

 }

 //运动卡报警信息
 void CRouteManager::FunMotionErrorBack(const CMotionCard::s_MotionErrorInfo & sMotionErrorInfo)//回调信息
 {

     m_sErrorInfo.iErrorCode = sMotionErrorInfo.iErrorCode;
     m_sErrorInfo.eErrorGrade = (e_ErrorGrade)sMotionErrorInfo.iErrorGrade;
     m_sErrorInfo.strErrorDes = sMotionErrorInfo.strErrorDes;
     m_sErrorInfo.strErrorMark = sMotionErrorInfo.strErrorMark;
     m_sErrorInfo.GetTime();
     SendLastError();
 }

 ////////////////////
 bool CRouteManager::CallMotionDebugDlg()
 {
     if(m_bInitMotionSuc)
     {
         m_MotionCard.CallDebugDlg();
     }
     else
     {
         QMessageBox::information(0,"提示","未使能运动卡");
     }
     return true;
 }

 bool CRouteManager::CallMotionModelDlg()
 {
     if(m_bInitMotionSuc)
     {
         m_MotionCard.CallModelDlg();
     }
     else
     {
         QMessageBox::information(0,"提示","未使能运动卡");
     }
     return true;
 }

 bool CRouteManager::CallRouteManageDlg()
 {
     if(m_bInitMotionSuc)
     {
         CDlgRouteManage *dlg = new CDlgRouteManage(0,this);//非模态
         dlg->setModal(false);
         dlg->show();
     }
     else
     {
         QMessageBox::information(0,"提示","未使能运动卡");
     }
     return true;
 }
 bool CRouteManager::CallRouteParamDlg()
 {
     if(m_bInitMotionSuc)
     {
         CDlgRouteParam *dlg = new CDlgRouteParam(0,this);//非模态
         dlg->setModal(false);
         dlg->show();
     }
     else
     {
         QMessageBox::information(0,"提示","未使能运动卡");
     }
     return true;
 }
 bool CRouteManager::CallLightParamDlg()
 {
     m_bInitMotionSuc = true;
     if(m_bInitMotionSuc)
     {
         CDlgLightParam *dlg = new CDlgLightParam(0,this);//非模态
         dlg->setModal(false);
         dlg->show();
     }
     else
     {
         QMessageBox::information(0,"提示","未使能运动卡");
     }
     return true;
 }
 void CRouteManager::slotGetMessageInfomation(QString strAlarm)
 {
     QMessageBox::information(0,"警告",strAlarm);
 }

bool CRouteManager::InitMotionCard()
{
    if(m_sMotionControl.bEnableMotion)
    {
        CMotionCard::s_MotionInitParam sInitParam;

        QString str;
        sInitParam.iCardNum = m_sMotionControl.iMotionChanne[0];  //iChannel:运动卡号

        sInitParam.bExtMdlFlag = m_sMotionControl.bEnableMotionExt;
        str = m_strRoutePath+ "/" +m_sMotionControl.strGTExtModulFile;
        sInitParam.strGTExtMdlFilePath = str.toStdString();//运动卡初始化路径，传给固高库


        str = m_strRoutePath+ "/" +m_sMotionControl.strGTInitFile[0];
        sInitParam.strGTFilePath = str.toStdString();//运动卡初始化路径，传给固高库

        str = m_strRoutePath + "/" + m_sMotionControl.strMotionInitFile[0];
        sInitParam.strMotionFilePath = str.toStdString(); //运动卡参数路径

        auto funCall = std::bind(&CRouteManager::FunMotionCallBack,this,std::placeholders::_1);
        sInitParam.funCallBackInfo = funCall; //回调信息

        auto funError = std::bind(&CRouteManager::FunMotionErrorBack,this,std::placeholders::_1);
        sInitParam.funErrorInfo = funError; //报警信息

        m_bInitMotionSuc = m_MotionCard.InitMotionCard(sInitParam);
        if(m_bInitMotionSuc)
        {

            long outvalue = 0;
            if (m_MotionCard.GetDiInput(outvalue))
            {

                short stQuickStop1 = 0x0001 & (outvalue>>4);
                short stQuickStop2 = 0x0001 & (outvalue>>5);



                // -1：出现异常 0：Run开始 1：Run结束  100：急停 101：按键start  102：按键stop 103：按键Reset 104:运行1 105:运行2
                if(stQuickStop1 == 1 || stQuickStop2 == 1) //急停按钮
                {

                }
                else
                {
                    if(m_MotionCard.ClearDriverAlarm(1)==false||
                            m_MotionCard.ClearDriverAlarm(2) == false
                            ||m_MotionCard.ClearDriverAlarm(3) == false)
                    {
                        QMessageBox::information(0,"提示","清除报警失败！");
                    }
                }
            }


            if(!TowerLightGreenOn(false))
            {
            }
            if(!TowerLightRedOn(false))
            {

            }
            if(!TowerLightYellowOn(false))
            {

            }
        }
        return m_bInitMotionSuc;
    }
    return true;
}
bool CRouteManager::InitPLCCard()
{
    return true;
}
bool CRouteManager::InitLightDriver()
{
    if(m_sMotionControl.bEnableMotion)
    {
		try
		{
			if (!m_GardasoftLight.Init(this))
			{
				return false;
			}
		}
		catch (...)
		{

		}
       
        if(!m_GardasoftLight.Open(0))
        {
            return false;
        }
    }
    return true;
}

bool CRouteManager::IPhonePath_1_Light()
{
    for(int i = 0;i < 5;i++)
    {
        if(!m_GardasoftLight.SendCommand(i,m_dPulseWidth[i],m_dPulseDelay[i],m_dCurrent[i],m_dRetriggerDelay[i]))
        {
            return false;
        }
    }
    return true;
}
bool CRouteManager::IPhonePath_2_Light()
{
    for(int i = 5;i < 8;i++)
    {
        if(!m_GardasoftLight.SendCommand(i,m_dPulseWidth[i],m_dPulseDelay[i],m_dCurrent[i],m_dRetriggerDelay[i]))
        {
            return false;
        }
    }
    return true;
}
bool CRouteManager::IPhonePath_2_ExposureTime()
{
    if(!SetCameraStationParam(m_iStationNo[1],m_iCameraNo[1],0,m_fExposureTime[1],1))
    {
        return false;
    }
    if(!SetCameraStationParam(m_iStationNo[2],m_iCameraNo[2],0,m_fExposureTime[2],2))
    {
        return false;
    }
    if(!SetCameraStationParam(m_iStationNo[4],m_iCameraNo[4],0,m_fExposureTime[4],4))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_CylinderCamera_ExposureTime()
{
    if(!SetCameraStationParam(m_iStationNo[4],m_iCameraNo[4],0,m_fExposureTime[4],4))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_3_ExposureTime()
{
    if(!SetCameraStationParam(m_iStationNo[0],m_iCameraNo[0],0,m_fExposureTime[0],0))
    {
        return false;
    }
    if(!SetCameraStationParam(m_iStationNo[5],m_iCameraNo[5],0,m_fExposureTime[5],5))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_Lisener_ExposureTime()//听筒
{
    if(!SetCameraStationParam(m_iStationNo[3],m_iCameraNo[3],0,m_fExposureTime[3],3))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_2_Gain()
{
    if(!SetCameraStationParam(m_iStationNo[1],m_iCameraNo[1],1,m_fGain[1],1))
    {
        return false;
    }
    if(!SetCameraStationParam(m_iStationNo[2],m_iCameraNo[2],1,m_fGain[2],2))
    {
        return false;
    }
    if(!SetCameraStationParam(m_iStationNo[4],m_iCameraNo[4],1,m_fGain[4],4))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_CylinderCamera_Gain()
{
    if(!SetCameraStationParam(m_iStationNo[4],m_iCameraNo[4],1,m_fGain[4],4))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_3_Gain()
{
    if(!SetCameraStationParam(m_iStationNo[0],m_iCameraNo[0],1,m_fGain[0],0))
    {

        return false;
    }
    if(!SetCameraStationParam(m_iStationNo[5],m_iCameraNo[5],1,m_fGain[5],5))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_Lisener_Gain()
{
    if(!SetCameraStationParam(m_iStationNo[3],m_iCameraNo[3],1,m_fGain[3],3))
    {
        return false;
    }
    return true;
}
bool CRouteManager::IPhonePath_4_Light()
{
    for(int i = 8;i < 13;i++)
    {
        if(!m_GardasoftLight.SendCommand(i-8,m_dPulseWidth[i],m_dPulseDelay[i],m_dCurrent[i],m_dRetriggerDelay[i]))
        {
            return false;
        }
    }
    return true;
}



bool CRouteManager::ReleasePLCCard()
{
    return true;
}
bool CRouteManager::ReleaseMotionCard()
{
    if(m_bInitMotionSuc)
    {
        if(m_bIsThreadContinueRun)
        {
            m_bIsThreadContinueRun = false;
            m_SemaphoreContinueRun.acquire();
        }
        for(int i = 0;i< MAX_ROUTEMOTION_AXISCOUNT;i++)
        {
            if(m_bEnableAxsisSuc[i])
            {
                m_MotionCard.AxisEnabled(i,false);
                m_bEnableAxsisSuc[i] = false;
            }

        }

        m_bEnableMotionSuc = false;
    }

    m_bInitMotionSuc = false;

    m_bMotionGoHomeSuc = false;
    m_bMotionResetSuc = false;
    return true;
}

//轨迹运动相关

bool CRouteManager::RouteOperate(s_SchemaRouteMode & sRouteParam) //设置轨迹参数
{
    m_sRouteParam = sRouteParam;
    m_bLoadRouteParamSuc = true;
    return true;
}

bool CRouteManager::RouteGoFirst() //回开始位置
{
    if(!m_bMotionGoHomeSuc)
    {
        return false;
    }
    return true;
}

bool CRouteManager::RouteEmergentStop(bool bStart) //急停
{
    if(bStart)
    {
        if(m_bMototionEmergency == false)
        {
            //
            //
            m_eRouteControlStatus = eRCS_EmergencyStart;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("急停中",false);

            m_bMototionEmergency = true;

            //关真空吸
            if(!AxisAirOn(false))
            {
                MessageInformation("关真空吸失败!",false);

                return false;
            }

            if(m_bIsThreadContinueRun)
            {

                m_bIsThreadContinueRun = false;
                m_SemaphoreContinueRun.acquire();
            }




            //
            m_bMotionStartSuc = false;
            m_bMotionStopSuc = true;

            //红色灯亮 黄灯灭绿灯灭
            if(!TowerLightRedOn(true))
            {
                MessageInformation("红灯亮失败!",false);


            }
            if(!TowerLightYellowOn(true))
            {
                MessageInformation("黄灯亮失败!",false);

            }
            if(!TowerLightGreenOn(false))
            {
                MessageInformation("绿灯灭失败!",false);

            }



        }



    }
    else
    {
        m_eRouteControlStatus = eRCS_EmergencyFinish;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("解除急停",false,false);
    }

     return true;
}

bool CRouteManager::RouteReset()   //复位到起点
{
    if(m_bIsThreadContinueRun)
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "动作正在运行";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

         MessageInformation("动作正在运行!",false);
        return false;
    }

    if(m_eRouteControlStatus == eRCS_StartSuccess||m_eRouteControlStatus == eRCS_ResetFail
            ||m_eRouteControlStatus == eRCS_RunFrontFail||m_eRouteControlStatus == eRCS_RunBackFail
            ||m_eRouteControlStatus == eRCS_StopFail)

    {

    }
    else
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "当前动作不被允许";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

         MessageInformation("动作正在运行!",false);
        return false;

    }
    //启动开始线程
    m_iThreadContinueRunType =1;
    m_bIsThreadContinueRun = true;

    QFuture<void> future = QtConcurrent::run(this, &CRouteManager::ThreadMotionContinueRunFun);
   // return future.result();
    return true;


    return true;
}

//读取信号线程
bool CRouteManager::ThreadMotionSignalRead()
{
    while(m_bStartMotionSignalRead)
    {
        if(m_bInitMotionSuc)
        {
            ////////////////判断门
            if(!IsLeftFrontDoorClosed(m_isEnableCheckDoor))
            {
                if(m_bIsLeftFrontDoorClosed == false)
                {
                    if(m_bMotionStartSuc == true)
                    {
                        SendRouteStatus(eRCS_PressStop);
                        MessageInformation("左侧前门未关闭!",false);
                    }

                }
                m_bIsLeftFrontDoorClosed = true;

            }
            else
            {
                m_bIsLeftFrontDoorClosed = false;
            }

            if(!IsLeftBackDoorClosed(m_isEnableCheckDoor))
            {
                if(m_bIsLeftBackDoorClosed == false)
                {
                    if(m_bMotionStartSuc == true)
                    {
                        SendRouteStatus(eRCS_PressStop);
                        MessageInformation("左侧后门未关闭!",false);
                    }

                }
                m_bIsLeftBackDoorClosed = true;

            }
            else
            {
                m_bIsLeftBackDoorClosed = false;
            }

            if(!IsRightFrontDoorClosed(m_isEnableCheckDoor))
            {
                if(m_bIsRightFrontDoorClosed == false)
                {
                    if(m_bMotionStartSuc == true)
                    {
                        SendRouteStatus(eRCS_PressStop);
                        MessageInformation("右侧前门未关闭!",false);
                    }

                }
                m_bIsRightFrontDoorClosed = true;

            }
            else
            {
                m_bIsRightFrontDoorClosed = false;
            }

            if(!IsRightBackDoorClosed(m_isEnableCheckDoor))
            {
                if(m_bIsRightBackDoorClosed == false)
                {
                    if(m_bMotionStartSuc == true)
                    {
                        SendRouteStatus(eRCS_PressStop);
                        MessageInformation("右侧后门未关闭!",false);
                    }

                }
                m_bIsRightBackDoorClosed = true;

            }
            else
            {
                m_bIsRightBackDoorClosed = false;
            }
            ///////////////////////////////////////////////
            /// \brief outvalue
            //Start键 ，stop键，reset键 急停键
            long outvalue = 0;
            if (m_MotionCard.GetDiInput(outvalue))
            {
                short stStart = 0x0001 & (outvalue>>13);
                short stStop = 0x0001 & (outvalue>>14);
                short stReset = 0x0001 & (outvalue>>15);
                short stQuickStop1 = 0x0001 & (outvalue>>4);
                short stQuickStop2 = 0x0001 & (outvalue>>5);
                short stRunFront1 = 0x0001 & (outvalue>>0);
                short stRunFront2 = 0x0001 & (outvalue>>1);
                short stRunBack1 = 0x0001 & (outvalue>>2);
                short stRunBack2 = 0x0001 & (outvalue>>3);


                 // -1：出现异常 0：Run开始 1：Run结束  100：急停 101：按键start  102：按键stop 103：按键Reset 104:运行1 105:运行2
                if(stQuickStop1 == 1 || stQuickStop2 == 1) //急停按钮
                {
                    if(m_bPressEmergentStop == false)
                    {
                        //第一次按下

                        SendRouteStatus(eRCS_PressEmergency);
                    }
                    m_bPressEmergentStop = true;

                    //急停时候，不响应其他键
                    continue;
                }
                else
                {
                    if(m_bPressEmergentStop)
                    {
                         SendRouteStatus(eRCS_PressEmergencyFinish);
                        m_bPressEmergentStop = false;
                    }

                }

                if(m_funRunStatus != nullptr)
                {
                    if(stStart == 1) //启动按钮
                    {
                        if(m_bPressStart == false)
                        {
                            //第一次按下
                            if(m_bMotionStartSuc ==false && m_bIsThreadContinueRun == false)
                            {
                                if(m_eRouteControlStatus == eRCS_Init||m_eRouteControlStatus == eRCS_StartFail
                                        ||m_eRouteControlStatus == eRCS_EmergencyFinish||m_eRouteControlStatus == eRCS_StopSuccess)
                                {
                                    SendRouteStatus(eRCS_PressStart);

                                }


                            }
                        }
                        m_bPressStart = true;
                    }
                    else
                    {
                        m_bPressStart = false;
                    }

                    if(stStop == 1) //停止按钮
                    {
                        if(m_bPressStop == false)
                        {
                            //第一次按下
                            if(m_bMotionStartSuc == true)
                            {
                                if(m_eRouteControlStatus == eRCS_StartSuccess||m_eRouteControlStatus == eRCS_ResetFail
                                        ||m_eRouteControlStatus == eRCS_RunFrontFail||m_eRouteControlStatus == eRCS_RunBackFail
                                        ||m_eRouteControlStatus == eRCS_ResetSuccess||m_eRouteControlStatus == eRCS_RunBackSuccess
                                        ||m_eRouteControlStatus == eRCS_RunFrontSuccess||m_eRouteControlStatus == eRCS_RunFrontBegin
                                        ||m_eRouteControlStatus == eRCS_RunBackBegin)
                                {
                                    SendRouteStatus(eRCS_PressStop);
                                }

                            }
                        }
                        m_bPressStop = true;

                    }
                    else
                    {
                        m_bPressStop = false;
                    }

                    if(stReset == 1) //复位按钮
                    {
                        if(m_bPressReset == false)
                        {
                            //第一次按下，只有start启动，并且未运行时候，可以reset
                            if(m_bMotionStartSuc == true && m_bIsThreadContinueRun == false)
                            {
                                if(m_eRouteControlStatus == eRCS_StartSuccess||m_eRouteControlStatus == eRCS_ResetFail
                                        ||m_eRouteControlStatus == eRCS_RunFrontFail||m_eRouteControlStatus == eRCS_RunBackFail
                                        ||m_eRouteControlStatus == eRCS_StopFail)

                                {
                                    SendRouteStatus(eRCS_PressReset);
                                }



                            }
                        }
                        m_bPressReset = true;
                    }
                    else
                    {
                        m_bPressReset = false;
                    }





                    ///////////////////////////////////////////////
                    /// \brief outvalue
                    //开始运行键前面
                    if(stRunFront1 == 1 && stRunFront2 == 1)
                    {
                        if(m_bPressRunFront == false)
                        {
                            //第一次按下
                            if(m_bMotionStartSuc == true && m_bIsThreadContinueRun == false)
                            {
                                if(m_eRouteControlStatus == eRCS_ResetSuccess||m_eRouteControlStatus == eRCS_RunBackSuccess)
                                {
                                    SendRouteStatus(eRCS_PressRunFront);

                                }


                            }

                        }
                        m_bPressRunFront = true;

                    }
                    else
                    {
                        m_bPressRunFront = false;
                    }


                    //
                    //开始运行键后
                    if(stRunBack1 == 1 && stRunBack2 == 1)
                    {
                        if(m_bPressRunBack == false)
                        {
                            //第一次按下
                            if(m_bMotionStartSuc == true && m_bIsThreadContinueRun == false)
                            {
                                if(m_eRouteControlStatus == eRCS_RunFrontSuccess)
                                {
                                    SendRouteStatus(eRCS_PressRunBack);

                                }
                            }

                        }
                        m_bPressRunBack = true;

                    }
                    else
                    {
                        m_bPressRunBack = false;
                    }

                }


			}
            else
            {

                m_sErrorInfo.iErrorCode = 1;
                m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
                m_sErrorInfo.strErrorDes = "m_MotionCard.GetDiInput fail";
                m_sErrorInfo.strErrorMark = "CRouteManager::ThreadMotionSignalRead";
                m_sErrorInfo.GetTime();
                SendLastError();

            }



        }
        Sleep(100);
    }

    m_SemaphoreSignalReadFinish.release();
    return true;
}

bool CRouteManager::RouteStart() //开始
{
    if(m_bIsThreadContinueRun)
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "动作正在运行";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

         MessageInformation("动作正在运行!",false);
        return false;
    }

    if(m_eRouteControlStatus == eRCS_Init||m_eRouteControlStatus == eRCS_StartFail
            ||m_eRouteControlStatus == eRCS_EmergencyFinish||m_eRouteControlStatus == eRCS_StopSuccess)
    {

    }
    else
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "当前动作不被允许";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

         MessageInformation("动作正在运行!",false);
        return false;

    }

    //启动开始线程
    m_iThreadContinueRunType =0;
    m_bIsThreadContinueRun = true;

    QFuture<void> future = QtConcurrent::run(this, &CRouteManager::ThreadMotionContinueRunFun);
   // return future.result();
    return true;

}

bool CRouteManager::RouteStop()  //停止
{
    if(m_eRouteControlStatus == eRCS_StartSuccess||m_eRouteControlStatus == eRCS_ResetFail
            ||m_eRouteControlStatus == eRCS_RunFrontFail||m_eRouteControlStatus == eRCS_RunBackFail
            ||m_eRouteControlStatus == eRCS_ResetSuccess||m_eRouteControlStatus == eRCS_RunBackSuccess
            ||m_eRouteControlStatus == eRCS_RunFrontSuccess||m_eRouteControlStatus == eRCS_RunFrontBegin
            ||m_eRouteControlStatus == eRCS_RunBackBegin)
    {

    }
    else
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "当前动作不被允许";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

         MessageInformation("动作正在运行!",false);
        return false;

    }


    m_eRouteControlStatus = eRCS_StopBegin;
    SendRouteStatus(m_eRouteControlStatus);
    MessageInformation("STOP 进行中!",false,false);

    if(m_bPressEmergentStop)
    {
        m_eRouteControlStatus = eRCS_StopFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("急停状态中!",false);
        return false;
    }
    if(m_bIsThreadContinueRun)
    {
        m_bIsThreadContinueRun = false;
        m_SemaphoreContinueRun.acquire();
    }

    //
    m_bMotionStartSuc = false;
    m_bMotionStopSuc = true;



    //关真空吸
    if(!AxisAirOn(false))
    {
        m_eRouteControlStatus = eRCS_StopFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("关真空吸失败!",false);

        return false;
    }

    m_eRouteControlStatus = eRCS_StopSuccess;
    SendRouteStatus(m_eRouteControlStatus);
    MessageInformation("STOP 成功!",false,false);

    //红色灯亮 绿灯灭
    if(!TowerLightRedOn(false))
    {
        m_eRouteControlStatus = eRCS_StopFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("红灯灭失败!",false);

    }
    if(!TowerLightYellowOn(true))
    {
        m_eRouteControlStatus = eRCS_StopFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("黄灯亮失败!",false);

    }
    if(!TowerLightGreenOn(false))
    {
        m_eRouteControlStatus = eRCS_StopFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("绿灯灭失败!",false);

    }


    //离子风
    if(!EnableClearSetting(-1,false))
    {

        MessageInformation("离子风失败!",false);

    }
    return true;
}


bool CRouteManager::RouteRunFront()
{
    if(m_bIsThreadContinueRun)
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "动作正在运行";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

        MessageInformation("动作正在运行!",false);
        return false;
    }


    if(m_eRouteControlStatus == eRCS_ResetSuccess||m_eRouteControlStatus == eRCS_RunBackSuccess)
        {

        }
        else
        {
            m_sErrorInfo.iErrorCode = 1;
            m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
            m_sErrorInfo.strErrorDes = "当前动作不被允许";
            m_sErrorInfo.strErrorMark = "QtConcurrent::run";
            m_sErrorInfo.GetTime();
            SendLastError();

            MessageInformation("动作正在运行!",false);
            return false;

        }

    //启动开始线程
    m_iThreadContinueRunType =4;
    m_bIsThreadContinueRun = true;
    m_bIsMotionInspectAuto = true;
    QFuture<void> future = QtConcurrent::run(this, &CRouteManager::ThreadMotionContinueRunFun);
    // return future.result();
    return true;
}

bool CRouteManager::RouteRunBack()
{
    return true;
    if(m_bIsThreadContinueRun)
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "动作正在运行";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

        MessageInformation("动作正在运行!",false);
        return false;
    }

    if(m_eRouteControlStatus == eRCS_RunFrontSuccess)
    {



    }
    else
    {
        m_sErrorInfo.iErrorCode = 1;
        m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
        m_sErrorInfo.strErrorDes = "当前动作不被允许";
        m_sErrorInfo.strErrorMark = "QtConcurrent::run";
        m_sErrorInfo.GetTime();
        SendLastError();

        MessageInformation("动作正在运行!",false);
        return false;

    }
    //启动开始线程
    m_iThreadContinueRunType = 3;
    m_bIsThreadContinueRun = true;
    QFuture<void> future = QtConcurrent::run(this, &CRouteManager::ThreadMotionContinueRunFun);
    // return future.result();
    return true;




}

void CRouteManager::ThreadMotionContinueRun(void *pThis)
{
    CRouteManager *p = (CRouteManager *)pThis;
    p->ThreadMotionContinueRunFun();
}
//运动卡连续运动
void CRouteManager::ThreadMotionContinueRunFun()
{

    if(m_bIsThreadContinueRun)
    {
        if(m_iThreadContinueRunType == 0)
        {
            FunThreadRouteStart();
        }

        if(m_iThreadContinueRunType == 1)
        {
            FunThreadRouteReset();
        }

        if(m_iThreadContinueRunType == 2)
        {
           FunThreadRouteRunFront();

        }

        if(m_iThreadContinueRunType == 3)
        {
            FunThreadRouteRunBack();
        }
        if(m_iThreadContinueRunType == 4)
        {
            do
             {
                if(m_bBackRunSuc)
                {
                   FunThreadRouteRunFront();
                }
                if(m_bFrontRunSuc)
                {
                    FunThreadRouteRunBack();
                }

             }while(m_bIsThreadContinueRun && m_bIsMotionInspectAuto && m_bFrontRunSuc && m_bBackRunSuc);

        }



    }
    else
    {

        m_SemaphoreContinueRun.release();

    }

    m_bIsThreadContinueRun = false;
    m_iThreadContinueRunType = -1;


}

void CRouteManager::FunThreadRouteStart() //开始
{
    if(m_bIsThreadContinueRun)
    {
        //
        m_eRouteControlStatus = eRCS_StartBegin;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("START进行中...",false,false);
        //


        if(m_bPressEmergentStop)
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("急停状态中!",false);
            return;
        }

        if(m_bMototionEmergency)
        {
            m_bEnableMotionSuc = false;
            m_bMotionGoHomeSuc = false;
            m_bMototionEmergency = false;

            m_MotionCard.ClearDriverAlarm(1);
            m_MotionCard.ClearDriverAlarm(2);
            m_MotionCard.ClearDriverAlarm(3);
        }

        if(m_bMotionStartSuc)
        {
            m_eRouteControlStatus = eRCS_StartSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已经START!",false);
            return;
        }
        //门必须关闭
        if(!IsLeftFrontDoorClosed(m_isEnableCheckDoor))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("左侧前门未关闭!",false);
            return;
        }
        if(!IsLeftBackDoorClosed(m_isEnableCheckDoor))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("左侧后门未关闭!",false);
            return;
        }
        if(!IsRightFrontDoorClosed(m_isEnableCheckDoor))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("右侧前门未关闭!",false);
            return;
        }
        if(!IsRightBackDoorClosed(m_isEnableCheckDoor))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("右侧后门未关闭!",false);
            return;
        }
        //不能有产品
        if(InputProductOn(500) || OutputProductOn(500))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("载具有产品!",false);
            return;
        }

        //IO重置
        //正压检查
        if(!IsAirOn())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("真空气压未开启!",false);
            return;
        }
        //检查有无产品
        //开真空吸
        if(!AxisAirOn(true))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("开真空吸失败!",false);
            return;
        }
        //判断有无产品
        if(AxisProductOn(500))//等待一秒
        {
            //关闭真空吸
            if(!AxisAirOn(false))
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("关闭真空吸失败!",false);
                return;
            }

            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("旋转轴上有产品!",false);
            return;
        }
        //关闭真空吸
        if(!AxisAirOn(false))
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("关闭真空吸失败!",false);
            return;
        }
        //判断前部光栅
        if(!GratingFront())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("前部光栅遮挡!",false);
            return;
        }
        //进料置下位
        if(!InputSideDownReady())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("进料置下位失败!",false);
            return;
        }
        //判断前部光栅
        if(!GratingFront())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("前部光栅遮挡!",false);
            return;
        }
        //进料定位气缸-缩
//        if(!Orientated(false))
//        {

//            m_eRouteControlStatus = eRCS_StartFail;
//            SendRouteStatus(m_eRouteControlStatus);
//            MessageInformation("进料定位气缸缩失败!",false);
//            return;
//        }
        if(!OrientatedFrontBack(false))
        {

            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("前后进料定位气缸缩失败!",false);
            return;
        }
        if(!OrientatedLeftRight(false))
        {

            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("左右进料定位气缸缩失败!",false);
            return;
        }
        //判断后部光栅
        if(!GratingBack())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("后部光栅遮挡!",false);
            return;
        }
        //出料置下位
        if(!OutputSideDownReady())
        {

            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("出料置下位失败!",false);
            return;
        }
        //翻转预备-Up 防止短轴回零撞上
        if(!CylinderReadyUp())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("翻转上升失败!",false);
            return;
        }

        if(!m_bMotionGoHomeSuc)
        {
            //使能
            m_MotionCard.CreatCoordinate(1,1,2,3);
            m_bEnableMotionSuc = m_MotionCard.CoordinateEnable(1);
            if(!m_bEnableMotionSuc)
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("坐标系使能失败!",false);
                return;
            }
            //回零
            //判断前部光栅
            if(!GratingFront())
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前部光栅遮挡!",false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("后部光栅遮挡!",false);
                return;
            }
            Sleep(1000);
            if(!m_MotionCard.AxisGoHome(2))
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("短轴回零失败!",false);
                return;
            }
            //判断前部光栅
            if(!GratingFront())
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前光栅有遮挡!",false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("后光栅有遮挡!",false);
                return;
            }
            if(!m_MotionCard.AxisGoHome(1))
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("长轴回零失败!",false);
                return;
            }
            //判断前部光栅
            if(!GratingFront())
            {
                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);

                MessageInformation("前光栅遮挡!",false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {

                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("后部光栅遮挡!",false);
                return;
            }
            if(!m_MotionCard.AxisGoHome(3))
            {

                m_eRouteControlStatus = eRCS_StartFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("旋转轴回零失败!",false);
                return;

            }
            bool flag;
            flag = m_MotionCard.CoordinateClear(1);
            flag = m_MotionCard.CoordinateLineMove(1,m_iResetPointOffSetX,m_iResetPointOffSetY,m_iResetPointOffSetZ,50,20);//此 长轴回零 位置需要实际验证
            flag = m_MotionCard.CoordinateStart(1);
            flag = m_MotionCard.CoordinateMovedForXR(1);
            m_bMotionGoHomeSuc = true;
        }

        m_bMotionStartSuc = true;
        m_bMotionStopSuc = false;
        m_bMotionResetSuc = false;

        m_eRouteControlStatus = eRCS_StartSuccess;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("START 成功!",false,false);

        //绿灯亮 红灯灭 黄灯灭
        if(!TowerLightGreenOn(true))
        {

            MessageInformation("绿灯亮失败!",false);
        }
        if(!TowerLightRedOn(false))
        {

            MessageInformation("红灯关失败!",false);

        }
        if(!TowerLightYellowOn(false))
        {

            MessageInformation("黄灯关失败!",false);

        }



    }


}
void CRouteManager::FunThreadRouteReset()   //复位
{
    if(m_bIsThreadContinueRun)
    {
    //
    m_eRouteControlStatus = eRCS_ResetBegin;
    SendRouteStatus(m_eRouteControlStatus);
    MessageInformation("RESET进行中...",false,false);
    //

    if(m_bPressEmergentStop)
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
       MessageInformation("急停状态中!",false);

        return;
    }
    if(!m_bMotionStartSuc) //必须start状态按下，才有用。
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("未启动Start!",false);

        return;
    }

    if(!m_bInitMotionSuc)
    {


        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("初始化未成功!",false);

        return;
    }

    if(!m_bEnableMotionSuc)
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("轴使能失败!",false);


        return;
    }


    if(!m_bMotionGoHomeSuc)
    {

        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("轴回零失败!",false);

        return;
    }


    ///////////////////////
    m_bMotionResetSuc = false;
    //门必须关闭
    if(!IsLeftFrontDoorClosed(m_isEnableCheckDoor))
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("左侧前门未关闭!",false);
        return;
    }
    if(!IsLeftBackDoorClosed(m_isEnableCheckDoor))
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("左侧后门未关闭!",false);
        return;
    }
    if(!IsRightFrontDoorClosed(m_isEnableCheckDoor))
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("右侧前门未关闭!",false);
        return;
    }
    if(!IsRightBackDoorClosed(m_isEnableCheckDoor))
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("右侧后门未关闭!",false);
        return;
    }
    //黄色指示灯亮
    if(!TowerLightYellowOn(true))
    {
        MessageInformation("黄灯亮失败!",false);
    }
    //不能有产品
    if(InputProductOn() || OutputProductOn())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("载具有产品!",false);

        return;
    }

    //IO重置
    //正压检查
    if(!IsAirOn())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("正压检查无气压!",false);

        return;
    }
    //检查有无产品
    //开真空吸
    if(!AxisAirOn(true))
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("开真空吸失败!",false);

        return;
    }
    //判断有无产品
    if(AxisProductOn(500))//等待一秒
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("旋转轴上有产品!",false);

        return;
    }
    //关闭真空吸
    if(!AxisAirOn(false))
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("关闭真空吸失败!",false);

        return;
    }
    //进料置下位
    if(!InputSideDownReady())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("进料置下位失败!",false);

        return;
    }
    //进料定位气缸-缩
//    if(!Orientated(false))
//    {
//        m_eRouteControlStatus = eRCS_ResetFail;
//        SendRouteStatus(m_eRouteControlStatus);
//        MessageInformation("进料定位气缸-缩失败!",false);

//        return;
//    }
    if(!OrientatedFrontBack(false))
    {

        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("前后进料定位气缸缩失败!",false);
        return;
    }
    if(!OrientatedLeftRight(false))
    {

        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("左右进料定位气缸缩失败!",false);
        return;
    }
    //出料置下位
    if(!OutputSideDownReady())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);

        MessageInformation("出料置下位失败!",false);

        return;
    }
    //翻转预备
    if(!CylinderReady())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);

        MessageInformation("翻转预备失败!",false);
        return;
    }

    //回到 判断前部光栅位置
    //判断前部光栅
    if(!GratingFront())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);

         MessageInformation("前部光栅遮挡!",false);
        return;
    }
    if(!GratingBack())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);

         MessageInformation("后部光栅遮挡!",false);
        return;
    }

    m_MotionCard.CoordinateLineMove(1,m_iFrontGrat + m_iLong/2 + 10000,0,0,m_iLineVel,m_iLineAcc);//此 长轴回零 位置需要实际验证
    m_MotionCard.CoordinateStart(1);
    m_MotionCard.CoordinateMovedForXR(1);
    //判断前部光栅
    if(!GratingFront())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);

        MessageInformation("前部光栅遮挡!",false);

        return;
    }
    //运动到夹点
    m_MotionCard.CoordinateLineMove(1,m_iResetPointOffSetX,m_iResetPointOffSetY,m_iResetPointOffSetZ,m_iLineVel,m_iLineAcc);//夹点需要实际验证
    m_MotionCard.CoordinateStart(1);
    m_MotionCard.CoordinateMovedForXR(1);


    //可放手机状态
    //进料置上位
    if(!InputSideUp())
    {
        m_eRouteControlStatus = eRCS_ResetFail;
        SendRouteStatus(m_eRouteControlStatus);

        MessageInformation("进料置上位失败!",false);
        return;
    }

    m_bMotionResetSuc = true;
    m_eRouteControlStatus = eRCS_ResetSuccess;
    SendRouteStatus(m_eRouteControlStatus);
    MessageInformation("RESET 成功!",false,false);
    /////////////////
    //黄色指示灯灭
    if(!TowerLightYellowOn(false))
    {

        MessageInformation("黄灯灭失败!",false);

    }


    }

}

void CRouteManager::FunThreadRouteRunFront() //前运行
{
    if(m_bIsThreadContinueRun)
    {
        m_eRouteControlStatus = eRCS_RunFrontBegin;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("Run检测进行中...",false,false);

        if(m_bPressEmergentStop)
        {
            m_bIsThreadContinueRun = false;
            m_eRouteControlStatus = eRCS_RunFrontFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("急停状态中！",false);
           
            m_bFrontRunSuc = false;
            return;
        }  
        bool bIsAlreadyFrontRun = false;
        do
        {

            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }

            //判断前部光栅
            if (!GratingFront())
            {

                MessageInformation("前部光栅有遮挡！", false, false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(1000);
                continue;
            }
            //判断有产品
            if(!InputProductOn(10))
            {

                m_bFrontRunSuc = false;
                MessageInformation("请放置产品！",false,false);
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bCodeType)
            {
                //判断有条码
                if(!m_bCodeValid)
                {
                    m_bFrontRunSuc = false;
                    MessageInformation("请扫码！",false,false);
                    bIsAlreadyFrontRun = false;
                    Sleep(200);
                    continue;
                }
            }

            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断前部光栅
            if (!GratingFront())
            {

                MessageInformation("前部光栅有遮挡！", false, false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            //进料定位气缸-伸
//            if(!Orientated(true))
//            {
//                MessageInformation("进料定位气缸-伸失败！", false);
//                m_bFrontRunSuc = false;
//                bIsAlreadyFrontRun = false;
//                Sleep(200);
//                continue;
//            }
            //进料定位气缸-伸
            if(!OrientatedLeftRight(true))
            {
                MessageInformation("左右进料定位气缸伸失败!",false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(!OrientatedFrontBack(true))
            {
                MessageInformation("前后进料定位气缸伸失败!",false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断前部光栅
            if (!GratingFront())
            {

                MessageInformation("前部光栅有遮挡！", false, false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //开始吸气
            if(!AxisAirOn(true))
            {

                MessageInformation("开始吸气失败！",false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断前部光栅
            if (!GratingFront())
            {

                MessageInformation("前部光栅有遮挡！", false, false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            //进料定位气缸-缩
//            if(!Orientated(false))
//            {
//                m_eRouteControlStatus = eRCS_RunFrontFail;
//                SendRouteStatus(m_eRouteControlStatus);
//                MessageInformation("进料定位气缸-缩失败！",false);
//                m_bFrontRunSuc = false;
//                bIsAlreadyFrontRun = false;
//                Sleep(200);
//                continue;
//            }
            if(!OrientatedFrontBack(false))
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前后进料定位气缸缩失败",false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(!OrientatedLeftRight(false))
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("左右进料定位气缸缩失败",false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断前部光栅
            if (!GratingFront())
            {

                MessageInformation("前部光栅有遮挡！", false, false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //进料上升气缸置下位，伸
            if(!InputSideDown())
            {

                MessageInformation("进料上升气缸置下位失败！",false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断前部光栅
            if (!GratingFront())
            {

                MessageInformation("前部光栅有遮挡！", false, false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            Sleep(50);
            //判断吸住产品
            if(!AxisProductOn(500))
            {

                MessageInformation("请放置产品！",false,false);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;
            }
            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);

                return;
            }
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //翻转气缸静点
            if(!CylinderSetStatic())
            {

                MessageInformation("翻转气缸静点失败！",false);


                SendRouteStatus(m_eRouteControlStatus);
                m_bFrontRunSuc = false;
                bIsAlreadyFrontRun = false;
                Sleep(200);
                continue;

            }

            bIsAlreadyFrontRun = true;

        }while(!bIsAlreadyFrontRun);


        //离子风
        if(!EnableClearSetting(0,true))
        {

            MessageInformation("离子风开失败!",false);

        }
        //更新界面显示状态
        SendRouteStatus(eRCS_StartCheck);
        if(m_bCodeType)
        {
            m_MutexCodeValid.lock();
            m_bCodeValid = false;
            m_MutexCodeValid.unlock();
        }

        MessageInformation("Run检测进行中...",false,false);


        SendRouteStatus(eRCS_RunCurrentStepNum,15);
        if(m_bIsThreadContinueRun)
        {

            if(!IPhonePath_1_Light())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("正面检测光源设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;

                //离子风
                if(!EnableClearSetting(0,false))
                {

                    MessageInformation("离子风开失败!",false);
                }

                return;
            }
            if(!IPhonePath_1())//手机正面
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("正面检测失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;

                //离子风
                if(!EnableClearSetting(0,false))
                {
                    MessageInformation("离子风开失败!",false);
                }

                return;
            }
        }
        else
        {

            m_SemaphoreContinueRun.release();

            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            //离子风
            if(!EnableClearSetting(0,false))
            {

                MessageInformation("离子风开失败!",false);
            }

            return;
        }

        //离子风
        if(!EnableClearSetting(0,false))
        {

            MessageInformation("离子风关失败!",false);
        }
        //离子风
        if(!EnableClearSetting(1,true))
        {

            MessageInformation("离子风开失败!",false);
        }
        SendRouteStatus(eRCS_RunCurrentStepNum,25);

        if(m_bIsThreadContinueRun)
        {
			if (!(WaitForSingleObject(m_HandleWaitForColor, 5000) == WAIT_OBJECT_0))
			{
				m_sErrorInfo.iErrorCode = 1;
				m_sErrorInfo.eErrorGrade = eEG_ErrorGenal;
				m_sErrorInfo.strErrorDes = "轨迹前摄像头位置未等到颜色信息";
				m_sErrorInfo.strErrorMark = "CRouteManager";
				m_sErrorInfo.GetTime();
				SendLastError();
			}
            if(!IPhonePath_Lisener_ExposureTime())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前摄像头曝光设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;


                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风开失败!",false);
                }

                return;
            }
            if(!IPhonePath_Lisener_Gain())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前摄像头增益设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;



                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风开失败!",false);
                }
                return;
            }

            if(!IPhonePath_1_Lisener())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前置摄像头检测失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;


                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风开失败!",false);
                }

                return;
            }
        }
        else
        {

            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            m_SemaphoreContinueRun.release();



            if(!EnableClearSetting(1,false))
            {

                MessageInformation("离子风关失败!",false);
            }

            return;
        }

        if(!EnableClearSetting(1,false))
        {

            MessageInformation("离子风关失败!",false);
        }
        SendRouteStatus(eRCS_RunCurrentStepNum,30);

        if(m_bIsThreadContinueRun)
        {

            if(!IPhonePath_2_Light())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("中框检测光源设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;



                return;
            }
            if(!IPhonePath_2_ExposureTime())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("中框检测曝光设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;




                return;
            }
            if(!IPhonePath_2_Gain())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("中框检测增益设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;




                return;
            }

            if(!IPhonePath_2())//中框
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("中框检测失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;



                return;
            }
        }
        else
        {

            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            m_SemaphoreContinueRun.release();


            return;
        }
        SendRouteStatus(eRCS_RunCurrentStepNum,35);//IPhonePath_CylinderCamera

        if(m_bIsThreadContinueRun)
        {
            if(!CylinderReady())
            {
                m_bIsThreadContinueRun = false;
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);

                MessageInformation("翻转机构准备失败！",false);
                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;

                //离子风
                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风关失败!",false);
                }


                return;
            }
            if(!IPhonePath_3_ExposureTime())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("摄像头检测曝光设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;


                return;
            }
            if(!IPhonePath_3_Gain())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("摄像头检测增益设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;

                return;
            }
            if(!IPhonePath_3())//翻转+摄像头
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("翻转&摄像头检测失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;

                //离子风
                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风关失败!",false);
                }


                return;
            }
        }
        else
        {

           m_SemaphoreContinueRun.release();

            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);



            return;
        }

        SendRouteStatus(eRCS_RunCurrentStepNum,50);
        if(m_bIsThreadContinueRun)
        {


            if(!IPhonePath_4_Light())
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("反面检测光源设置失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;


                //离子风
                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风开失败!",false);
                }

                return;
            }



            //开启进料口出料口准备线程
            QFuture<void> future = QtConcurrent::run(this, &CRouteManager::ThreadInputSideAndOutputSideReadyFun);


            if(!IPhonePath_4())//反面
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("反面检测失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;


                //离子风
                if(!EnableClearSetting(1,false))
                {

                    MessageInformation("离子风开失败!",false);
                }

                return;
            }
        }
        else
        {

            m_SemaphoreContinueRun.release();
            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);


            //离子风
            if(!EnableClearSetting(1,false))
            {

                MessageInformation("离子风开失败!",false);
            }

            return;
        }

        SendRouteStatus(eRCS_RunCurrentStepNum,65);

        if(m_bIsThreadContinueRun)
        {

            if(!IPhonePath_5())//走到出点判断光栅位置
            {
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("运动出口光栅失败",false);

                m_SemaphoreContinueRun.release();
                m_bIsThreadContinueRun = false;


                return;
            }
        }
        else
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);



            return;
        }
        SendRouteStatus(eRCS_RunCurrentStepNum,80);


        //判断出料口是否可进
        bool bIsAlreadyToOutside = false;
        do
        {

            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }

            //判断后部光栅
            if(!GratingBack())
            {

                MessageInformation("后光栅有遮挡！",false,false);
                m_bFrontRunSuc = false;
                bIsAlreadyToOutside = false;
                Sleep(2000);
                continue;
            }
            //判断出料无料
            if(OutputProductOn(10))
            {

                MessageInformation("出料口有产品！",false);
                m_bFrontRunSuc = false;
                bIsAlreadyToOutside = false;
                Sleep(2000);
                continue;
            }
            //出口状态
            if(!OutputSideDown())
            {
                MessageInformation("出口置下位失败！",false);
                m_bFrontRunSuc = false;
                bIsAlreadyToOutside = false;
                Sleep(200);
                continue;
            }
            bIsAlreadyToOutside = true;
			

        }while(!bIsAlreadyToOutside);




        if(m_bIsThreadContinueRun == false)
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }
        //走到取点
        m_MotionCard.CoordinateLineMove(1,m_iP5 + m_iGetPointOffSetX,m_iGetPointOffSetY,m_iGetPointOffSetZ-4*m_iCircle14,m_iLineVel,m_iLineAcc);//夹点需要实际验证
        m_MotionCard.CoordinateStart(1);
        m_MotionCard.CoordinateMoved(1);

        SendRouteStatus(eRCS_RunCurrentStepNum,90);

        if(m_bIsThreadContinueRun == false)
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }

        bool bIsOutSideAlreadyMove = false;
        do
        {
            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {

                MessageInformation("后光栅有遮挡！",false,false);
                m_bFrontRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }
            //停止吸气
            if(!AxisAirOn(false))
            {
                 MessageInformation("停止吸气失败！",false);

                m_bFrontRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }

            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);

                return;
            }
            //翻转气缸静点
            if(!CylinderSetStatic())
            {

                MessageInformation("翻转气缸静点失败！",false);


                m_bFrontRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;

            }


            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {

                MessageInformation("后光栅有遮挡！",false,false);
                m_bFrontRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }
            //出料夹紧气缸-紧、上
            if(!OutputSideUp())
            {

                MessageInformation("出料置上位失败！",false);

                m_bFrontRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;

            }

            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);

                return;
            }
            if(!OutputProductOn(1000))
            {

                MessageInformation("出料口无产品！",false);
                m_bFrontRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }
            bIsOutSideAlreadyMove = true;

        }while(!bIsOutSideAlreadyMove);



         if(m_bIsThreadContinueRun == false)
         {

             m_SemaphoreContinueRun.release();


             m_eRouteControlStatus = eRCS_StopSuccess;
             SendRouteStatus(m_eRouteControlStatus);
             MessageInformation("已结束运行",false,false);

             return;
         }
         m_bFrontRunSuc = true;
         SendRouteStatus(eRCS_RunCurrentStepNum,100);
         SendRouteStatus(eRCS_StopCheck);

         m_eRouteControlStatus = eRCS_RunFrontSuccess;
         SendRouteStatus(m_eRouteControlStatus);
         MessageInformation("到达出料口",false,false);
    }


}
void CRouteManager::FunThreadRouteRunBack() //后运行
{
    if(m_bIsThreadContinueRun)
    {
        m_eRouteControlStatus = eRCS_RunBackBegin;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("Run完毕回退中...",false,false);

        if(m_bPressEmergentStop)
        {
            m_bIsThreadContinueRun = false;
            m_eRouteControlStatus = eRCS_RunBackFail;
            SendRouteStatus(m_eRouteControlStatus);

            MessageInformation("急停状态中！",false);

            m_bBackRunSuc = false;
            return;
        }
        if(m_bIsThreadContinueRun == false)
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }

        bool bIsOutSideAlreadyMove = false;
        do
        {
            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {

                MessageInformation("后光栅有遮挡！",false,false);
                m_bBackRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }
            //停止吸气
            if(!AxisAirOn(false))
            {
                 MessageInformation("停止吸气失败！",false);

                m_bIsThreadContinueRun = false;

                m_bBackRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }

            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);

                return;
            }

            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();


                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断后部光栅
            if(!GratingBack())
            {


                MessageInformation("后光栅有遮挡！",false,false);
                m_bBackRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;
            }
            //出料夹紧气缸-紧、上
            if(!OutputSideUp())
            {

                MessageInformation("出料置上位失败！",false);

                m_bBackRunSuc = false;
                bIsOutSideAlreadyMove = false;
                Sleep(200);
                continue;

            }

            if(m_bIsThreadContinueRun == false)
            {

                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);

                return;
            }
            bIsOutSideAlreadyMove = true;

        }while(!bIsOutSideAlreadyMove);

        //更新状态
        MessageInformation("Run完毕回退中...",false,false);

        m_MotionCard.CoordinateLineMove(1,m_iFrontGrat + m_iLong/2 + 60000,m_iResetPointOffSetY,m_iResetPointOffSetZ,m_iLineVel,m_iLineAcc);//偏置2W以规避
        m_MotionCard.CoordinateStart(1);
        m_MotionCard.CoordinateMovedForXR(1);

        if(m_bIsThreadContinueRun == false)
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }

        //判断进料口是否可进
        bool bIsAlreadyToInside = false;
        do
        {
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }

            //判断前部光栅
            if(!GratingFront())
            {


                MessageInformation("前光栅有遮挡！",false,false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
                Sleep(200);
                continue;
            }

            /*
             //进料置上位
            if(!InputSideUp())
            {


                MessageInformation("进料置上位失败！",false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
                Sleep(200);
                continue;
            }
            */
            if(m_bIsThreadContinueRun == false)
            {
                m_SemaphoreContinueRun.release();
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);
                return;
            }
            //判断前部光栅
            if(!GratingFront())
            {


                MessageInformation("前光栅有遮挡！",false,false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
                Sleep(200);
                continue;
            }
            //进料定位气缸-缩
//            if(!Orientated(false))
//            {
//                m_eRouteControlStatus = eRCS_RunBackFail;
//                SendRouteStatus(m_eRouteControlStatus);

//                MessageInformation("进料定位气缸缩失败！",false);
//                m_bBackRunSuc = false;
//                bIsAlreadyToInside = false;
//                Sleep(200);
//                continue;
//            }
            if(!OrientatedFrontBack(false))
            {

                m_eRouteControlStatus = eRCS_RunBackFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("前后进料定位气缸缩失败!",false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
                Sleep(200);
                continue;
            }
            if(!OrientatedLeftRight(false))
            {

                m_eRouteControlStatus = eRCS_RunBackFail;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("左右进料定位气缸缩失败!",false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
                Sleep(200);
                continue;
            }
            bIsAlreadyToInside = true;

        }while(!bIsAlreadyToInside);

        if(m_bIsThreadContinueRun == false)
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }

        //运动到夹点
        m_MotionCard.CoordinateLineMove(1,m_iResetPointOffSetX,m_iResetPointOffSetY,m_iResetPointOffSetZ,m_iLineVel,m_iLineAcc);//夹点需要实际验证
        m_MotionCard.CoordinateStart(1);
        m_MotionCard.CoordinateMovedForXR(1);

        if(m_bIsThreadContinueRun == false)
        {

            m_SemaphoreContinueRun.release();


            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }

        //进料置上位
       if(!InputSideUp())
       {


//           HANDLE handle;

//           WaitForSingleObject(handle,5000);



           MessageInformation("进料置上位失败！",false);
           m_bBackRunSuc = false;
           bIsAlreadyToInside = false;
           Sleep(200);

       }
        m_bBackRunSuc = true;
        m_eRouteControlStatus = eRCS_RunBackSuccess;
        SendRouteStatus(m_eRouteControlStatus);
        MessageInformation("到达进料口",false,false);
    }
}

bool CRouteManager::MotionCardIOControl(unsigned int iStep)
{
    switch(iStep)
    {
        case GuGao_Setp_A0:
        {
            m_MotionCard.SetDoOutput(GuGao_DO_200_0_HANDLE,0,12);
            break;
        }
        case GuGao_Setp_B0:
        {

            break;
        }
        case GuGao_Setp_A1:
        {

            break;
        }
        case GuGao_Setp_B1:
        {

            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

bool CRouteManager::MotionStepControl(short sStep)
{
    e_SchemaMotionType MotionType = m_sRouteParam.vecRouteStep.at(sStep).sMotionParam.eMotionType;
    double x = m_sRouteParam.vecRouteStep.at(sStep).sMotionParam.iMoveDis[0];
    double y = m_sRouteParam.vecRouteStep.at(sStep).sMotionParam.iMoveDis[1];
    double z = m_sRouteParam.vecRouteStep.at(sStep).sMotionParam.iMoveDis[2];
    switch(MotionType)
    {
        case eSMT_MotionLine3:
        {
            m_MotionCard.CoordinateLineMove(m_iMotionCrdNumber,x,y,z);
            break;
        }
        case eSMT_MotionPlug2:
        {

            break;
        }
        case eSMT_MotionSpiral3:
        {
            m_MotionCard.CoordinateHeliMove(m_iMotionCrdNumber,x,y,z,0);
            break;
        }
        case eSMT_MotionPositionComp:
        {

            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

bool CRouteManager::InputSideDownReady()
{
    bool flag;
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    //进料夹紧气缸-松
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(0,7,Status[0]);
    m_MotionCard.GetExtMdlIoBit(0,9,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,5,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,4,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,7,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,9,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            return false;
        }
    }
    //进料上升气缸-下
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(0,3,Status[0]);
    m_MotionCard.GetExtMdlIoBit(0,5,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,3,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,2,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,3,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
             return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,5,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            return false;
        }
    }
    return true;
}
bool CRouteManager::InputSideDown()
{
    bool flag;
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    //进料上升气缸-下
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
//    m_MotionCard.GetExtMdlIoBit(0,3,Status[0]);
//    m_MotionCard.GetExtMdlIoBit(0,5,Status[1]);
//    if(Status[0]!=0 || Status[1]!=0)
//    {
        flag = m_MotionCard.SetExtMdlIoBit(0,3,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,2,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,3,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
             return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,5,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            return false;
        }
//    }
    //进料夹紧气缸-松
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
//    m_MotionCard.GetExtMdlIoBit(0,7,Status[0]);
//    m_MotionCard.GetExtMdlIoBit(0,9,Status[1]);
//    if(Status[0]!=0 || Status[1]!=0)
//    {
        flag = m_MotionCard.SetExtMdlIoBit(0,5,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,4,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,7,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,9,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            return false;
        }
//    }
    return true;
}
bool CRouteManager::InputSideUp()//
{
    bool flag;
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    //进料夹紧气缸-紧
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
//    m_MotionCard.GetExtMdlIoBit(0,6,Status[0]);
//    m_MotionCard.GetExtMdlIoBit(0,8,Status[1]);
//    if(Status[0]!=0 || Status[1]!=0)
//    {
        flag = m_MotionCard.SetExtMdlIoBit(0,4,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,5,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,6,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("进料夹紧左气缸未紧!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,8,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
         //   MessageInformation("进料夹紧右气缸未紧!");
            return false;
        }
//    }
    //进料上升气缸-上
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
//    m_MotionCard.GetExtMdlIoBit(0,2,Status[0]);
//    m_MotionCard.GetExtMdlIoBit(0,4,Status[1]);
//    if(Status[0]!=0 || Status[1]!=0)
//    {
        flag = m_MotionCard.SetExtMdlIoBit(0,2,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,3,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,2,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
          //  MessageInformation("进料上升左气缸未上位!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,4,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
         //  MessageInformation("进料上升右气缸未上位!");
            return false;
        }
//    }
    return true;

}
bool CRouteManager::OutputSideDownReady()
{
    bool flag;
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    //出料夹紧气缸-松
    //判断后部光栅
    if(!GratingBack())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(1,5,Status[0]);
    m_MotionCard.GetExtMdlIoBit(1,7,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,15,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,14,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,5,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("出料夹紧左气缸未松开!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,7,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("出料夹紧右气缸未松开!");
            return false;
        }
    }
    //出料上升气缸-下
    //判断后部光栅
    if(!GratingBack())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(1,1,Status[0]);
    m_MotionCard.GetExtMdlIoBit(1,3,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,13,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,12,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,1,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("出料上升左气缸未下位!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,3,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            //MessageInformation("出料上升右气缸未下位!");
            return false;
        }
    }
    return true;
}
bool CRouteManager::OutputSideDown()
{
    bool flag;
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    //出料上升气缸-下
    //判断后部光栅
    if(!GratingBack())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(1,1,Status[0]);
    m_MotionCard.GetExtMdlIoBit(1,3,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,13,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,12,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,1,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("出料上升左气缸未下位!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,3,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            //MessageInformation("出料上升右气缸未下位!");
            return false;
        }
    }
    //出料夹紧气缸-松
    //判断后部光栅
    if(!GratingBack())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(1,5,Status[0]);
    m_MotionCard.GetExtMdlIoBit(1,7,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,15,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,14,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,5,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("出料夹紧左气缸未松开!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,7,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("出料夹紧右气缸未松开!");
            return false;
        }
    }
    return true;
}
bool CRouteManager::OutputSideUp()
{
    bool flag;
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    //出料夹紧气缸-紧
    //判断后部光栅
    if(!GratingBack())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(1,4,Status[0]);
    m_MotionCard.GetExtMdlIoBit(1,6,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,14,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,15,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,4,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("出料夹紧左气缸未紧!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,6,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("出料夹紧右气缸未紧!");
            return false;
        }
    }
    //出料上升气缸-上
    //判断后部光栅
    if(!GratingBack())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(1,0,Status[0]);
    m_MotionCard.GetExtMdlIoBit(1,2,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,12,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,13,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,0,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("出料上升左气缸未上位!");
            return false;
        }
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(1,2,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("出料上升右气缸未上位!");
            return false;
        }
    }

    return true;
}

bool CRouteManager::GratingFront()
{
    short temp;
     //判断前部光栅
    m_MotionCard.GetSingleDiInput(7,temp);
    if(temp==1)
    {
         return false;
    }
    return true;

}
bool CRouteManager::GratingBack()
{
    short temp;
    //判断后部光栅
    m_MotionCard.GetSingleDiInput(8,temp);
    if(temp==1)
    {
       return false;
    }
    return true;
}
bool CRouteManager::CylinderReady()
{
    unsigned short OutValue;
    bool flag;
    int a;
    //翻转气缸静点
    m_MotionCard.GetExtMdlIoBit(0,14,OutValue);
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,11,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,10,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,14,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           // MessageInformation("翻转气缸置静点失败!");
            return false;
        }
    }
    //翻转上升气缸-下
    m_MotionCard.GetExtMdlIoBit(0,12,OutValue);
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,9,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,8,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,12,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            //MessageInformation("翻转气缸置下位失败!");
            return false;
        }
    }
    //翻转夹紧气缸-松
    m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,7,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,6,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
          //  MessageInformation("翻转气缸置松失败!");
            return false;
        }
    }
    return true;
}
bool CRouteManager::CylinderReadyUp()
{
    unsigned short OutValue = 1;
    bool flag;
    int a;
    //翻转气缸静点
 //   m_MotionCard.GetExtMdlIoBit(0,14,OutValue);
    OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,11,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,10,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,14,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           return false;
        }
    }
    //翻转上升气缸-上
   // m_MotionCard.GetExtMdlIoBit(0,13,OutValue);

     OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,8,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,9,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,13,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           return false;
        }
    }
    //翻转夹紧气缸-松
   // m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
    OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,7,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,6,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
           return false;
        }
    }
    return true;
}
bool CRouteManager::CylinderMove()
{
    bool flag;
    unsigned short OutValue;
    int a;
    //翻转夹紧气缸-紧
    //m_MotionCard.GetExtMdlIoBit(0,11,OutValue);
     OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,6,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,7,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,11,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转夹紧气缸未紧!");
            return false;
        }
    }
    //Sleep(50);
   // m_MotionCard.GetExtMdlIoBit(0,11,OutValue);

     OutValue = 1;
    if(OutValue==0)
    {
        m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
        if(OutValue==0)
        {
            MessageInformation("请检查手机是否放反!");
            return false;
        }
    }
    Sleep(50);
    //翻转上升气缸-上
   // m_MotionCard.GetExtMdlIoBit(0,13,OutValue);

     OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,8,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,9,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,13,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转上升气缸未上!");
            return false;
        }
    }
    Sleep(50);
    //翻转气缸动点
  //  m_MotionCard.GetExtMdlIoBit(0,15,OutValue);
     OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,10,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,11,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,15,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转气缸未置动点!");
            return false;
        }
    }
    Sleep(50);
    //翻转上升气缸-下
   // m_MotionCard.GetExtMdlIoBit(0,12,OutValue);
     OutValue = 1;
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,9,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,8,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,12,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转上升气缸未置下点!");
            return false;
        }
    }
    Sleep(50);
    //翻转夹紧气缸-松
    flag = m_MotionCard.SetExtMdlIoBit(0,7,1);
    flag = m_MotionCard.SetExtMdlIoBit(0,6,0);
    m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,7,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,6,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转气缸置松失败!");
            return false;
        }
    }
    //Sleep(50);
    m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
    if(OutValue==0)
    {
        m_MotionCard.GetExtMdlIoBit(0,11,OutValue);
        if(OutValue==0)
        {
            MessageInformation("请检查手机是否放反!");
            return false;
        }
    }
    return true;
}
bool CRouteManager::InputProductOn(short mWaitTime)
{
    short temp;
    int a = 0;
    do
    {
        m_MotionCard.GetSingleDiInput(10,temp);;
        Sleep(5);
        a++;
    }while(temp!=1 && a< mWaitTime/5);
    if(temp != 1)
    {
        return false;
    }
    return true;
}
bool CRouteManager::OutputProductOn(short mWaitTime)
{
    short temp;
    int a = 0;
    do
    {
        m_MotionCard.GetSingleDiInput(11,temp);;
        Sleep(5);
        a++;
    }while(temp!=1 && a< mWaitTime/5);
    if(temp != 1)
    {
        //MessageInformation("出料处无产品!");
        return false;
    }
    return true;
}
//判断旋转轴有无产品
bool CRouteManager::AxisProductOn(short mWaitTime)
{
    short temp;
    int a = 0;
    do
    {
        m_MotionCard.GetSingleDiInput(13,temp);;
        Sleep(5);
        a++;
    }while(temp!=1 && a< mWaitTime/5);
    if(temp != 1)
    {
        //MessageInformation("真空吸未检测到产品!");
        return false;
    }
    return true;
}
//判断是否有气压
bool CRouteManager::IsAirOn()
{
    short temp;
    m_MotionCard.GetSingleDiInput(9,temp);
    if(temp==1)
    {
        return true;
    }
    else
    {
        return false;
    }

}
bool CRouteManager::Orientated(bool flag)
{
    unsigned short OutValue;
    unsigned short Status[2];
    int a;
    if(flag)
    {
        switch(m_sProductType)
        {
        case 0:
            m_MotionCard.GetExtMdlIoBit(2,1,Status[0]);
            m_MotionCard.GetExtMdlIoBit(2,3,Status[1]);
            if(Status[0]!=0 || Status[1]!=0)
            {
                m_MotionCard.SetExtMdlIoBit(0,1,1);
                m_MotionCard.SetExtMdlIoBit(0,0,0);
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,1,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,3,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
            }
            break;
        case 1:
            //进料定位气缸-伸
            m_MotionCard.GetExtMdlIoBit(2,0,Status[0]);
            m_MotionCard.GetExtMdlIoBit(2,2,Status[1]);
            if(Status[0]!=0 || Status[1]!=0)
            {
                m_MotionCard.SetExtMdlIoBit(0,1,1);
                m_MotionCard.SetExtMdlIoBit(0,0,0);
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,0,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,2,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
            }
            break;
          default:
            return false;
        }
    }
    else
    {
        //进料定位气缸-缩
        m_MotionCard.GetExtMdlIoBit(0,0,Status[0]);
        m_MotionCard.GetExtMdlIoBit(2,4,Status[1]);
        if(Status[0]!=0 || Status[1]!=0)
        {
            m_MotionCard.SetExtMdlIoBit(0,0,1);
            m_MotionCard.SetExtMdlIoBit(0,1,0);
            a = 0;
            do
            {
                m_MotionCard.GetExtMdlIoBit(0,0,OutValue);
                Sleep(5);
                a++;
            }while(OutValue!=0 && a< DelayTime);
            if(OutValue != 0)
            {
                 return false;
            }
            a = 0;
            do
            {
                m_MotionCard.GetExtMdlIoBit(2,4,OutValue);
                Sleep(5);
                a++;
            }while(OutValue!=0 && a< DelayTime);
            if(OutValue != 0)
            {
                 return false;
            }
        }
    }
    return true;

}

bool CRouteManager::OrientatedFrontBack(bool flag)
{
    unsigned short OutValue;
    int a;
    if(flag)
    {
        switch(m_sProductType)
        {
        case 0:
             case 1:
           // m_MotionCard.GetExtMdlIoBit(2,3,OutValue);
           // if(OutValue!=0)
            {
                m_MotionCard.SetExtMdlIoBit(1,7,1);
                m_MotionCard.SetExtMdlIoBit(1,9,0);
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,3,OutValue);
                  //  OutValue = 0;
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
            }
            break;
       /* case 1:
            //进料定位气缸-伸
          //  m_MotionCard.GetExtMdlIoBit(2,2,OutValue);
          //  if(OutValue!=0)
            {
                m_MotionCard.SetExtMdlIoBit(1,7,1);
                m_MotionCard.SetExtMdlIoBit(1,9,0);
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,2,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
            }
            break;*/
          default:
            return false;
        }
    }
    else
    {
        //进料定位气缸-缩
       // m_MotionCard.GetExtMdlIoBit(2,4,OutValue);
       // if(OutValue!=0)
        {
            m_MotionCard.SetExtMdlIoBit(1,9,1);
            m_MotionCard.SetExtMdlIoBit(1,7,0);
            a = 0;
            do
            {
                m_MotionCard.GetExtMdlIoBit(2,2,OutValue);
                Sleep(5);
                a++;
            }while(OutValue!=0 && a< DelayTime);
            if(OutValue != 0)
            {
                 return false;
            }
        }
    }
    return true;

}
//bool CRouteManager::OrientatedFrontBack(bool flag)
//{
//    unsigned short OutValue;
//    int a;
//    if(flag)
//    {
//        switch(m_sProductType)
//        {
//        case 0:
//            //m_MotionCard.GetExtMdlIoBit(2,3,OutValue);
//            //if(OutValue!=0)
//            {
//                m_MotionCard.SetExtMdlIoBit(1,7,1);
//                m_MotionCard.SetExtMdlIoBit(1,9,0);
//                a = 0;
//                do
//                {
//                    m_MotionCard.GetExtMdlIoBit(2,3,OutValue);
//                    Sleep(5);
//                    a++;
//                }while(OutValue!=0 && a< DelayTime);
//                if(OutValue != 0)
//                {
//                    return false;
//                }
//            }
//            break;
//        case 1:
//            //进料定位气缸-伸
//            //m_MotionCard.GetExtMdlIoBit(2,2,OutValue);
//            //if(OutValue!=0)
//            {
//                m_MotionCard.SetExtMdlIoBit(1,7,1);
//                m_MotionCard.SetExtMdlIoBit(1,9,0);
//                a = 0;
//                do
//                {
//                    m_MotionCard.GetExtMdlIoBit(2,2,OutValue);
//                    Sleep(5);
//                    a++;
//                }while(OutValue!=0 && a< DelayTime);
//                if(OutValue != 0)
//                {
//                    return false;
//                }
//            }
//            break;
//          default:
//            return false;
//        }
//    }
//    else
//    {
//        //进料定位气缸-缩
//        //m_MotionCard.GetExtMdlIoBit(2,4,OutValue);
//        //if(OutValue!=0)
//        {
//            m_MotionCard.SetExtMdlIoBit(1,9,1);
//            m_MotionCard.SetExtMdlIoBit(1,7,0);
//            a = 0;
//            do
//            {
//                m_MotionCard.GetExtMdlIoBit(2,4,OutValue);
//                Sleep(5);
//                a++;
//            }while(OutValue!=0 && a< DelayTime);
//            if(OutValue != 0)
//            {
//                 return false;
//            }
//        }
//    }
//    return true;

//}
bool CRouteManager::OrientatedLeftRight(bool flag)
{
    unsigned short OutValue;
    int a;
    if(flag)
    {
        switch(m_sProductType)
        {
        case 0:
            m_MotionCard.GetExtMdlIoBit(2,1,OutValue);
            if(OutValue!=0)
            {
                m_MotionCard.SetExtMdlIoBit(0,1,1);
                m_MotionCard.SetExtMdlIoBit(0,0,0);
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,1,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
            }
            break;
        case 1:
            //进料定位气缸-伸
            m_MotionCard.GetExtMdlIoBit(2,0,OutValue);
            if(OutValue!=0)
            {
                m_MotionCard.SetExtMdlIoBit(0,1,1);
                m_MotionCard.SetExtMdlIoBit(0,0,0);
                a = 0;
                do
                {
                    m_MotionCard.GetExtMdlIoBit(2,0,OutValue);
                    Sleep(5);
                    a++;
                }while(OutValue!=0 && a< DelayTime);
                if(OutValue != 0)
                {
                    return false;
                }
            }
            break;
          default:
            return false;
        }
    }
    else
    {
        //进料定位气缸-缩
        m_MotionCard.GetExtMdlIoBit(0,0,OutValue);
        if(OutValue!=0)
        {
            m_MotionCard.SetExtMdlIoBit(0,0,1);
            m_MotionCard.SetExtMdlIoBit(0,1,0);
            a = 0;
            do
            {
                m_MotionCard.GetExtMdlIoBit(0,0,OutValue);
                Sleep(5);
                a++;
            }while(OutValue!=0 && a< DelayTime);
            if(OutValue != 0)
            {
                 return false;
            }
        }
    }
    return true;
}
//真空吸
bool CRouteManager::AxisAirOn(bool flag)
{
    if(flag)
    {
        return m_MotionCard.SetExtMdlIoBit(1,6,0);
    }
    else
    {
        return m_MotionCard.SetExtMdlIoBit(1,6,1);
    }

}
bool CRouteManager::TowerLightRedOn(bool flag)
{
    if(flag)
    {
        //红灯-亮
        return m_MotionCard.SetExtMdlIoBit(1,0,0);
    }
    else
    {
        //红灯-灭
        return m_MotionCard.SetExtMdlIoBit(1,0,1);
    }
}
bool CRouteManager::TowerLightGreenOn(bool flag)
{
    if(flag)
    {
        //绿灯-亮
        return m_MotionCard.SetExtMdlIoBit(1,2,0);
    }
    else
    {
        //绿灯-灭
        return m_MotionCard.SetExtMdlIoBit(1,2,1);
    }
}
bool CRouteManager::TowerLightYellowOn(bool flag)
{
    if(flag)
    {
        //黄灯-亮
        return m_MotionCard.SetExtMdlIoBit(1,1,0);
    }
    else
    {
        //黄灯-灭
        return m_MotionCard.SetExtMdlIoBit(1,1,1);
    }
}

//离子吹风
bool CRouteManager::EnableClearSetting(int iIndex,bool flag)
{
    if(!m_sMotionControl.bEnableMotion)
    {
        return true;
    }


    if(iIndex == 0 || iIndex == -1)
    {
        if(flag)
        {
            return m_MotionCard.SetExtMdlIoBit(1,10,0);
        }
        else
        {
            return m_MotionCard.SetExtMdlIoBit(1,10,1);
        }
    }


    if(iIndex == 1|| iIndex == -1)
    {
        if(flag)
        {
            return m_MotionCard.SetExtMdlIoBit(1,11,0);
        }
        else
        {
            return m_MotionCard.SetExtMdlIoBit(1,11,1);
        }
    }
    return false;
}

bool CRouteManager::TowerBuzzerOn(bool flag)
{
    if(!m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    if(flag)
    {
        //蜂鸣器-鸣叫
        return m_MotionCard.SetExtMdlIoBit(1,3,0);
    }
    else
    {
        //蜂鸣器-静默
        return m_MotionCard.SetExtMdlIoBit(1,3,1);
    }
}
bool CRouteManager::ManualLightRedOn(bool flag)
{
    if(!m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    if(flag)
    {
        //红灯-亮
        return m_MotionCard.SetExtMdlIoBit(1,4,0);
    }
    else
    {
        //红灯-灭
        return m_MotionCard.SetExtMdlIoBit(1,4,1);
    }
}
bool CRouteManager::ManualLightGreenOn(bool flag)
{
    if(!m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    if(flag)
    {
        //绿灯-亮
        return m_MotionCard.SetExtMdlIoBit(1,5,0);
    }
    else
    {
        //绿灯-灭
        return m_MotionCard.SetExtMdlIoBit(1,5,1);
    }
}

bool CRouteManager::FloodlightOn(bool flag)
{
    if(!m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    if(flag)
    {
        //绿灯-亮
        m_bFloodlightOn = true;
        return m_MotionCard.SetExtMdlIoBit(1,8,0);
    }
    else
    {
        //绿灯-灭
        m_bFloodlightOn = false;
        return m_MotionCard.SetExtMdlIoBit(1,8,1);
    }
}
bool CRouteManager::IsLeftFrontDoorClosed(bool isEnableCheck)
{
    if(!isEnableCheck || !m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    unsigned short OutValue;
    m_MotionCard.GetExtMdlIoBit(1,9,OutValue);
    if(OutValue!=0)
    {
        return false;
    }
    return true;
}
bool CRouteManager::IsLeftBackDoorClosed(bool isEnableCheck)
{
    if(!isEnableCheck || !m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    unsigned short OutValue;
    m_MotionCard.GetExtMdlIoBit(1,8,OutValue);
    if(OutValue!=0)
    {
        return false;
    }
    return true;
}
bool CRouteManager::IsRightFrontDoorClosed(bool isEnableCheck)
{
    if(!isEnableCheck || !m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    unsigned short OutValue;
    m_MotionCard.GetExtMdlIoBit(1,11,OutValue);
    if(OutValue!=0)
    {
        return false;
    }
    return true;
}
bool CRouteManager::IsRightBackDoorClosed(bool isEnableCheck)
{
    if(!isEnableCheck || !m_sMotionControl.bEnableMotion)
    {
        return true;
    }
    unsigned short OutValue;
    m_MotionCard.GetExtMdlIoBit(1,10,OutValue);
    if(OutValue!=0)
    {
        return false;
    }
    return true;
}
bool CRouteManager::CylinderSetStatic()
{
    unsigned short OutValue;
    bool flag;
    int a;
    //翻转气缸静点
    m_MotionCard.GetExtMdlIoBit(0,14,OutValue);
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,11,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,10,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,14,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转气缸置静点失败!");
            return false;
        }
    }
    return true;
}

bool CRouteManager::CylinderSetEmpty()//翻转夹紧置松
{
    unsigned short OutValue;
    bool flag;
    int a;
    //翻转夹紧气缸-松
    flag = m_MotionCard.SetExtMdlIoBit(0,7,1);
    flag = m_MotionCard.SetExtMdlIoBit(0,6,0);
    m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
    if(OutValue!=0)
    {
        flag = m_MotionCard.SetExtMdlIoBit(0,7,1);
        flag = m_MotionCard.SetExtMdlIoBit(0,6,0);
        a = 0;
        do
        {
            m_MotionCard.GetExtMdlIoBit(0,10,OutValue);
            Sleep(5);
            a++;
        }while(OutValue!=0 && a< DelayTime);
        if(OutValue != 0)
        {
            MessageInformation("翻转气缸置松失败!");
            return false;
        }
    }
    return true;
}

void CRouteManager::ThreadInputSideAndOutputSideReadyFun()
{
    //判断前部光栅
  /*  if(GratingFront())
    {
        //进料置上位
        InputSideUp();
    }

    */

    //进料定位气缸-缩
//    if(!Orientated(false))
//    {
//        m_eRouteControlStatus = eRCS_RunBackFail;
//        SendRouteStatus(m_eRouteControlStatus);

////        MessageInformation("进料定位气缸缩失败！",false);
////        MessageInformation("进料定位气缸缩失败!");
////        return ;
//    }
    //判断出料无料
    //判断后部光栅
    if(GratingBack())
    {
        if(!OutputProductOn(50))
        {
            if(!OutputSideDown())
            {
            }
        }

    }


    
    //翻转气缸静点
   /* if(!CylinderSetStatic())
    {
        Sleep(200);
    }*/
}
bool CRouteManager::IPhonePath_1()//正面检测  150800 + 9000 = 159800  156000=13*12  138500 + 9000 = 147500  144000
{
    bool flag;
    //走到正面检测
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-(m_iPublicLong/2+m_iLightOpen)+m_iFrontOffSetX,-4016+m_iFrontOffSetY,m_iFrontOffSetZ,m_iFrontVel,m_iFrontAcc,m_iFrontVel);
//	//开始运动
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);

    //正面同轴、补光、低角度
    //flag = m_MotionCard.CoordinateBufDelay(1,1000);//延迟100ms
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-m_iPublicLong/2+m_iFrontOffSetX,-4016+m_iFrontOffSetY,m_iFrontOffSetZ,m_iFrontVel,m_iFrontAcc,m_iFrontVel);//
    flag = m_MotionCard.CoordinateBufIO(1,0x0004,0x0000);//触发正背检测相机
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-m_iPublicLong/2+m_iLightOpen-8000+m_iFrontOffSetX,-4016+m_iFrontOffSetY,m_iFrontOffSetZ,m_iFrontVel,m_iFrontAcc,m_iFrontVel);//156000
    flag = m_MotionCard.CoordinateBufIO(1,0x0004,0xFFFF);//关闭 正背检测相机触发 正背检测同轴光、补光
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1+m_iPublicLong/2+m_iLightOpen+m_iFrontOffSetX,-4016+m_iFrontOffSetY,m_iFrontOffSetZ,m_iFrontVel,m_iFrontAcc);//156000
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);

    return flag;
}
bool CRouteManager::IPhonePath_1_Lisener()//听筒
{
    bool flag;
    //Lisener
    ///////Lisener///////
    flag = m_MotionCard.CoordinateLineMove(1,m_iLisenerX,m_iLisenerY,m_iLisenerZ,m_iFrontVel,m_iFrontAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    flag = m_MotionCard.CoordinateBufIO(1,0x4000,0x0000);//触发摄像头光源、相机
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟1s
    flag = m_MotionCard.CoordinateBufIO(1, 0x4000, 0xFFFF);//关闭 摄像头 相机、光源
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第一边---准备位置---m_iPublicLong+3*m_iFrameStep=150800+27000=177800-162000
    flag = m_MotionCard.CoordinateLineMove(1, m_iP3 - (m_iPublicLong / 2 + m_iFrameStep) + m_iFrameOffSetX1, m_MyLength - m_iWidth / 2 + m_iFrameOffSetY1, m_iFrameOffSetZ1, m_iLineVel, m_iLineAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.CoordinateBufDelay(1, 100);//延迟100ms
    return flag;
}
bool CRouteManager::IPhonePath_2()//中框
{
    /////////////////////////////等距一维位置比较////////////////////////////////
//    bool flag;
//    short sPlusTime = 500;
//    int StepLong = m_iLong/m_iFrameStep / 2 + 1;//9=8.3+1
//    int StepWidth = m_iWidth/m_iFrameStep / 2;//4.19
//    flag = m_MotionCard.ComparePort(1,11,0);
//    //走到第一边准备位置
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3-(m_iLong/2+m_iFrameStep)+ m_iFrameOffSetX1,10400+m_iFrameOffSetY1,m_iFrameOffSetZ1,m_iLineVel,m_iLineAcc);
//    //开始运动
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    //位置比较
//    flag = m_MotionCard.CompareLinear(1,1,0,StepLong,2*m_iFrameStep,sPlusTime,1);
//    //第一边
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iLong/2 + 2*m_iFrameStep + m_iFrameOffSetX1,10400+m_iFrameOffSetY1,m_iFrameOffSetZ1,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    //第一个R角
//    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 - LongOffsetX,m_FrameOffset-LongOffsetY,-m_Circle14/2,vel,acc);
//    flag = m_MotionCard.CoordinateLineMove(1,685720 + m_iFrameCornerOffSetX1,-16661-8900 + m_iFrameCornerOffSetY1,-m_iCircle14/2 + m_iFrameCornerOffSetZ1,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);

//    //第二边
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 - (m_iWidth/2 + m_iFrameStep) + 3600+ m_iFrameOffSetX2,10400+m_iFrameOffSetY2-m_W_H,m_iFrameOffSetZ2-m_iCircle14,m_iFrameVel,m_iFrameAcc);
//    //开始运动
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);

//    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//    //位置比较
//    flag = m_MotionCard.CompareLinear(1,1,0,StepWidth,2*m_iFrameStep,sPlusTime,1);
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iWidth/2 + 3600+ m_iFrameOffSetX2,10400+m_iFrameOffSetY2-m_W_H,m_iFrameOffSetZ2-m_iCircle14,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    //第二个R角20000+2610
//    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Width/2 - WidthOffsetX,m_FrameOffset-WidthOffsetY-m_W_H,-m_Circle14-m_Circle14/2,vel,acc);
//    flag = m_MotionCard.CoordinateLineMove(1,631395 + m_iFrameCornerOffSetX2,-16863-8900 + m_iFrameCornerOffSetY2,-m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ2,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);

//    //第三边
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3-(m_iLong/2+m_iFrameStep)+ m_iFrameOffSetX3,10400+m_iFrameOffSetY3,m_iFrameOffSetZ3-2*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//    //开始运动
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    //位置比较
//    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//    flag = m_MotionCard.CompareLinear(1,1,0,StepLong,2*m_iFrameStep,sPlusTime,1);
//    //第三边
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iLong/2 + 2*m_iFrameStep+ m_iFrameOffSetX3,10400+m_iFrameOffSetY3,m_iFrameOffSetZ3-2*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    //第三个R角
//    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 - LongOffsetX,m_FrameOffset-LongOffsetY,-2*m_Circle14-m_Circle14/2,vel,acc);
//    flag = m_MotionCard.CoordinateLineMove(1,685620 + m_iFrameCornerOffSetX3,-18561-8900 + m_iFrameCornerOffSetY3,-2*m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ3,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);
//    //第四边
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 - (m_iWidth/2 + m_iFrameStep) + 3600+ m_iFrameOffSetX4,10400+m_iFrameOffSetY4-m_W_H,m_iFrameOffSetZ4-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//    //位置比较
//    flag = m_MotionCard.CompareLinear(1,1,0,StepWidth,2*m_iFrameStep,sPlusTime,1);
//    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iWidth/2 + 3600+ m_iFrameOffSetX4,10400+m_iFrameOffSetY4-m_W_H,m_iFrameOffSetZ4-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    //第四个R角
//    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Width/2 - WidthOffsetX,m_FrameOffset-WidthOffsetY-m_W_H,-3*m_Circle14-m_Circle14/2,vel,acc);
//    flag = m_MotionCard.CoordinateLineMove(1,631380 + m_iFrameCornerOffSetX4,-19260-8900+m_iFrameCornerOffSetY4,-3*m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ4,m_iFrameVel,m_iFrameAcc);
//    flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//    flag = m_MotionCard.CoordinateStart(1);
//    flag = m_MotionCard.CoordinateMovedForXR(1);
//    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);

    /////////////////////////////非等距一维位置比较////////////////////////////////长框9张 短框4张

    bool flag;
    short sPlusTime = 500;
    long MyCompareData[20];
    m_W_H = (m_iPublicLong - m_iPublicWidth)/2;
	//int m_MyLength = 48150;//移动到成员变量
    for(int i =0;i<20;i++)
    {
        MyCompareData[i]=0;
    }
    //设置IO口
    flag = m_MotionCard.ComparePort(1,11,0);

    ////第一边---准备位置---m_iPublicLong+3*m_iFrameStep=150800+27000=177800-162000
    //flag = m_MotionCard.CoordinateLineMove(1,m_iP3-(m_iPublicLong/2+m_iFrameStep)+ m_iFrameOffSetX1,m_MyLength -m_iWidth/2+m_iFrameOffSetY1,m_iFrameOffSetZ1,m_iLineVel,m_iLineAcc);
    ////开始运动
    //flag = m_MotionCard.CoordinateStart(1);
    //flag = m_MotionCard.CoordinateMovedForXR(1);
    //flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    //位置比较---第一边数据
    MyCompareData[0] = m_iStep1[0];
    for(int i = 1;i < m_iStepCount[0];i++)
    {
        MyCompareData[i] = MyCompareData[i-1] + m_iStep1[i];
    }
    m_MotionCard.CompareData(1,1,0,0,sPlusTime,MyCompareData,m_iStepCount[0],nullptr,0);
    //第一边
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iPublicLong/2 + 2*m_iFrameStep + m_iFrameOffSetX1,m_MyLength -m_iWidth/2+m_iFrameOffSetY1,m_iFrameOffSetZ1,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);

    if(!IPhonePath_CylinderCamera())
    {
        return false;
    }


    //第一个R角 655000+75400+18000=748400 - 685720 = 62680 48780
    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 - LongOffsetX,m_FrameOffset-LongOffsetY,-m_Circle14/2,vel,acc);
    flag = m_MotionCard.CoordinateLineMove(1,m_iFrameCornerOffSetX1,m_iFrameCornerOffSetY1,-m_iCircle14/2 + m_iFrameCornerOffSetZ1,m_iFrameCornerVel,m_iFrameCornerAcc);
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.ComparePulse(1, 0, sPlusTime);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);

    //第二边---准备位置---m_iPublicWidth+m_iFrameStep=75500+9000=84500---72000
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 - (m_iPublicWidth/2 + m_iFrameStep) + 3600+ m_iFrameOffSetX2,m_MyLength -m_iLong/2+m_iFrameOffSetY2,m_iFrameOffSetZ2-m_iCircle14,m_iFrameCornerVel,m_iFrameCornerAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    //位置比较---第二边数据
    MyCompareData[0] = m_iStep2[0];
    for(int i = 1;i < m_iStepCount[1];i++)
    {
        MyCompareData[i] = MyCompareData[i-1] + m_iStep2[i];
    }
    m_MotionCard.CompareData(1,1,0,0,sPlusTime,MyCompareData,m_iStepCount[1],nullptr,0);
    //第二边---结束位置
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iPublicWidth/2 + 3600+ m_iFrameOffSetX2,m_MyLength -m_iLong/2+m_iFrameOffSetY2,m_iFrameOffSetZ2-m_iCircle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第二个R角20000+2610
    flag = m_MotionCard.CoordinateLineMove(1,m_iFrameCornerOffSetX2,m_iFrameCornerOffSetY2,-m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ2,m_iFrameCornerVel,m_iFrameCornerAcc);
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.ComparePulse(1, 0, sPlusTime);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);

    //第三边---准备位置---m_iPublicLong+3*m_iFrameStep=150800+27000=177800
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3-(m_iPublicLong/2+m_iFrameStep)+ m_iFrameOffSetX3,m_MyLength -m_iWidth/2+m_iFrameOffSetY3,m_iFrameOffSetZ3-2*m_iCircle14,m_iFrameCornerVel,m_iFrameCornerAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    //位置比较---第三边数据
    MyCompareData[0] = m_iStep3[0];
    for(int i = 1;i < m_iStepCount[2];i++)
    {
        MyCompareData[i] = MyCompareData[i-1] + m_iStep3[i];
    }
    m_MotionCard.CompareData(1,1,0,0,sPlusTime,MyCompareData,m_iStepCount[2],nullptr,0);
    //第三边---结束位置
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iPublicLong/2 + 2*m_iFrameStep+ m_iFrameOffSetX3,m_MyLength -m_iWidth/2+m_iFrameOffSetY3,m_iFrameOffSetZ3-2*m_iCircle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第三个R角
    flag = m_MotionCard.CoordinateLineMove(1,m_iFrameCornerOffSetX3, m_iFrameCornerOffSetY3,-2*m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ3,m_iFrameCornerVel,m_iFrameCornerAcc);
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.ComparePulse(1, 0, sPlusTime);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);

    //第四边---准备位置---m_iPublicWidth+m_iFrameStep=75500+9000=84500
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 - (m_iPublicWidth/2 + m_iFrameStep) + 3600+ m_iFrameOffSetX4,m_MyLength -m_iLong/2+m_iFrameOffSetY4,m_iFrameOffSetZ4-3*m_iCircle14,m_iFrameCornerVel,m_iFrameCornerAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    //位置比较---第四边数据
    MyCompareData[0] = m_iStep4[0];
    for(int i = 1;i < m_iStepCount[3];i++)
    {
        MyCompareData[i] = MyCompareData[i-1] + m_iStep4[i];
    }
    m_MotionCard.CompareData(1,1,0,0,sPlusTime,MyCompareData,m_iStepCount[3],nullptr,0);
    //第四边---结束位置
    flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iPublicWidth/2 + 3600+ m_iFrameOffSetX4,m_MyLength -m_iLong/2+m_iFrameOffSetY4,m_iFrameOffSetZ4-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第四个R角
	flag = m_MotionCard.CoordinateLineMove(1, m_iFrameCornerOffSetX4, m_iFrameCornerOffSetY4, -3 * m_iCircle14 - m_iCircle14 / 2 + m_iFrameCornerOffSetZ4, m_iFrameCornerVel, m_iFrameCornerAcc);
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.ComparePulse(1, 0, sPlusTime);
	flag = m_MotionCard.CoordinateBufDelay(1, 200);//延迟10ms
	flag = m_MotionCard.CoordinateStart(1);
	flag = m_MotionCard.CoordinateMovedForXR(1);


    return flag;


//    /////////////////////////////非等距二维位置比较////////////////////////////////长框9张 短框4张

//       bool flag;
//       short sPlusTime = 500;
//       My2DCompareData MyCompareData[20];
//       for(int i =0;i<20;i++)
//       {
//           MyCompareData[i].px=0;
//       }
//       My2DComparePrm MyPrm;
//       MyPrm.encx =2;
//       MyPrm.ency=1;//比较轴号
//       MyPrm.maxerr=100;//误差范围
//       MyPrm.outputType=0;//脉冲输出方式
//       MyPrm.source=1;//编码器
//       MyPrm.startLevel=0;
//       MyPrm.threshold=10;
//       MyPrm.time= sPlusTime;
//       m_MotionCard.Compare2DSetPrm(0,&MyPrm);
//       //设置IO口
//       flag = m_MotionCard.ComparePort(1,11,0);
//       flag = m_MotionCard.Compare2DMode(0,0);//mode：0为1D，1为2D

//       //第一边---准备位置---m_iLong+3*m_iFrameStep=150800+27000=177800-162000
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3-(m_iLong/2+m_iFrameStep)+ m_iFrameOffSetX1,10400+m_iFrameOffSetY1,m_iFrameOffSetZ1,m_iLineVel,m_iLineAcc);
//       //开始运动
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//       //位置比较---第一边数据
//       MyCompareData[0].py = m_iStep1[0];
//       for(int i = 1;i < m_iStepCount[0];i++)
//       {
//           MyCompareData[i].py = MyCompareData[i-1].py + m_iStep1[i];
//       }
//       flag = m_MotionCard.Compare2DClear(0);

//       m_MotionCard.Compare2DData(0,m_iStepCount[0],MyCompareData,0);
//       m_MotionCard.Compare2DStart(0);
//       //第一边
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iLong/2 + 2*m_iFrameStep + m_iFrameOffSetX1,10400+m_iFrameOffSetY1,m_iFrameOffSetZ1,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       //第一个R角 655000+75400+18000=748400 - 685720 = 62680 48780
//       //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 - LongOffsetX,m_FrameOffset-LongOffsetY,-m_Circle14/2,vel,acc);
//       flag = m_MotionCard.CoordinateLineMove(1,685720 + m_iFrameCornerOffSetX1,-16661-8900 + m_iFrameCornerOffSetY1,-m_iCircle14/2 + m_iFrameCornerOffSetZ1,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.Compare2DPulse(0,1,0,sPlusTime);

//       //第二边---准备位置---m_iWidth+m_iFrameStep=75500+9000=84500---72000
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3 - (m_iWidth/2 + m_iFrameStep) + 3600+ m_iFrameOffSetX2,10400+m_iFrameOffSetY2-m_W_H,m_iFrameOffSetZ2-m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       //开始运动
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//       //位置比较---第二边数据
//       MyCompareData[0].py = m_iStep2[0];
//       for(int i = 1;i < m_iStepCount[1];i++)
//       {
//           MyCompareData[i].py = MyCompareData[i-1].py + m_iStep2[i];
//       }
//       flag = m_MotionCard.Compare2DClear(0);
//       m_MotionCard.Compare2DData(0,m_iStepCount[1],MyCompareData,0);
//       m_MotionCard.Compare2DStart(0);
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iWidth/2 + 3600+ m_iFrameOffSetX2,10400+m_iFrameOffSetY2-m_W_H,m_iFrameOffSetZ2-m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       //第二个R角20000+2610
//       flag = m_MotionCard.CoordinateLineMove(1,631395 + m_iFrameCornerOffSetX2,-16863-8900 + m_iFrameCornerOffSetY2,-m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ2,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.Compare2DPulse(0,1,0,sPlusTime);

//       //第三边---准备位置---m_iLong+3*m_iFrameStep=150800+27000=177800
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3-(m_iLong/2+m_iFrameStep)+ m_iFrameOffSetX3,10400+m_iFrameOffSetY3,m_iFrameOffSetZ3-2*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//       //位置比较---第三边数据
//       MyCompareData[0].py = m_iStep3[0];
//       for(int i = 1;i < m_iStepCount[2];i++)
//       {
//           MyCompareData[i].py = MyCompareData[i-1].py + m_iStep3[i];
//       }
//       flag = m_MotionCard.Compare2DClear(0);
//       m_MotionCard.Compare2DData(0,m_iStepCount[2],MyCompareData,0);
//       m_MotionCard.Compare2DStart(0);
//       //第三边---结束位置
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iLong/2 + 2*m_iFrameStep+ m_iFrameOffSetX3,10400+m_iFrameOffSetY3,m_iFrameOffSetZ3-2*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       //第三个R角
//       flag = m_MotionCard.CoordinateLineMove(1,685620 + m_iFrameCornerOffSetX3,-18561-8900 + m_iFrameCornerOffSetY3,-2*m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ3,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.Compare2DPulse(0,1,0,sPlusTime);

//       //第四边---准备位置---m_iWidth+m_iFrameStep=75500+9000=84500
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3 - (m_iWidth/2 + m_iFrameStep) + 3600+ m_iFrameOffSetX4,10400+m_iFrameOffSetY4-m_W_H,m_iFrameOffSetZ4-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
//       //位置比较---第四边数据
//       MyCompareData[0].py = m_iStep4[0];
//       for(int i = 1;i < m_iStepCount[3];i++)
//       {
//           MyCompareData[i].py = MyCompareData[i-1].py + m_iStep4[i];
//       }
//       flag = m_MotionCard.Compare2DClear(0);
//       m_MotionCard.Compare2DData(0,m_iStepCount[3],MyCompareData,0);
//       m_MotionCard.Compare2DStart(0);
//       //第四边---结束位置
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP3 + m_iWidth/2 + 3600+ m_iFrameOffSetX4,10400+m_iFrameOffSetY4-m_W_H,m_iFrameOffSetZ4-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       //第四个R角
//       flag = m_MotionCard.CoordinateLineMove(1,631380 + m_iFrameCornerOffSetX4,-19260-8900+m_iFrameCornerOffSetY4,-3*m_iCircle14-m_iCircle14/2 + m_iFrameCornerOffSetZ4,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateBufDelay(1,10);//延迟10ms
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       flag = m_MotionCard.Compare2DPulse(0,1,0,sPlusTime);

//       ////////走到翻转机构/////
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP4-50000+m_iCylinderOffSetX,m_iCylinderOffSetY,m_iCylinderOffSetZ-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       flag = m_MotionCard.CoordinateLineMove(1,m_iP4+m_iCylinderOffSetX,m_iCylinderOffSetY,m_iCylinderOffSetZ-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
//       //开始运动
//       flag = m_MotionCard.CoordinateStart(1);
//       flag = m_MotionCard.CoordinateMovedForXR(1);
//       return flag;
}
bool CRouteManager::IPhonePath_CylinderCamera()//前置听筒
{
    bool flag;
    ///////前置听筒///////
    flag = m_MotionCard.CoordinateLineMove(1,m_iCylinderCameraX,m_iCylinderCameraY,m_iCylinderCameraZ,m_iFrameCornerVel,m_iFrameCornerAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.CoordinateBufIO(1,0x2000,0x0000);//触发听筒光源、相机
    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    flag = m_MotionCard.CoordinateBufIO(1, 0x2000, 0xFFFF);//关闭听筒 相机、光源
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
bool CRouteManager::IPhonePath_3()//翻转+摄像头
{
    bool flag;
    ////////走到翻转机构/////
    //flag = m_MotionCard.CoordinateLineMove(1,m_iP4-50000+m_iCylinderOffSetX,m_iCylinderOffSetY,m_iCylinderOffSetZ-3*m_iCircle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateLineMove(1,m_iP4+m_iCylinderOffSetX,m_iCylinderOffSetY,m_iCylinderOffSetZ-3*m_iCircle14,m_iUpDownCameraVel,m_iUpDownCameraAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    ////////翻转//////
    //判断真空吸有产品
    if(!AxisProductOn(1000))
    {
        MessageInformation("真空吸无产品！");
        return false;
    }
    //停止吸气
    if(!AxisAirOn(false))
    {
        MessageInformation("关闭真空吸失败！");
        return false;
    }
    //翻转夹紧气缸-紧
    //翻转上升气缸-上
    //翻转气缸动点
    //翻转上升气缸-下
    //翻转夹紧气缸-松
    if(!CylinderMove())
    {
        return false;
    }
    Sleep(100);
    //开始吸气
    if(!AxisAirOn(true))
    {
        MessageInformation("开启真空吸失败！");
        return false;
    }
    //判断真空吸有产品
    if(!AxisProductOn(5000))
    {
        MessageInformation("真空吸无产品！");
        return false;
    }
    //离子风
    if(!EnableClearSetting(1,true))
    {

        MessageInformation("离子风开失败!",false);
    }

    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    //走到反面检测
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1+(m_iPublicLong/2+2*m_iLightOpen)+ m_iBackOffSetX1, -3696+m_iBackOffSetY1,m_iBackOffSetZ1-4*m_iCircle14,m_iLineVel/3,m_iLineAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
bool CRouteManager::IPhonePath_4_Twice()
{
    //离子风
    if(!EnableClearSetting(1,true))
    {

        MessageInformation("离子风开失败!",false);
    }
    bool flag;
    //反面同轴、补光、低角度
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1+m_iPublicLong/2+ m_iBackOffSetX1, -3696+m_iBackOffSetY1,m_iBackOffSetZ1-4*m_iCircle14,m_iBackVel,m_iBackAcc);//
    flag = m_MotionCard.CoordinateBufIO(1,0x0004,0x0000);//触发正背检测相机
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1+m_iPublicLong/2+m_iLightOpen-12000+ m_iBackOffSetX1, -3696+m_iBackOffSetY1,m_iBackOffSetZ1-4*m_iCircle14,m_iBackVel,m_iBackAcc);//156000
    flag = m_MotionCard.CoordinateBufIO(1,0x0004,0xFFFF);//关闭 反背检测相机触发 背面检测同轴光、补光
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-(m_iPublicLong/2+m_iLightOpen)+ m_iBackOffSetX1, -3696+m_iBackOffSetY1,m_iBackOffSetZ1-4*m_iCircle14,m_iBackVel,m_iBackAcc);//156000
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);

    //离子风
    if(!EnableClearSetting(1,false))
    {

        MessageInformation("离子风关失败!",false);
    }
    if(!EnableClearSetting(0,true))
    {

        MessageInformation("离子风开失败!",false);
    }
    //回到准备位置
    flag = m_MotionCard.CoordinateLineMove(1,m_iResetPointOffSetX, -3696+m_iBackOffSetY,m_iBackOffSetZ-4*m_iCircle14,m_iBackVel,m_iBackAcc);//156000
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    if(!EnableClearSetting(0,false))
    {

        MessageInformation("离子风开失败!",false);
    }
    return flag;
}
bool CRouteManager::IPhonePath_4()//背面检测
{
    bool flag;

    if(m_bBackTwice)
    {
        if(!IPhonePath_4_Twice())
        {

            return false;
        }



        if(!EnableClearSetting(0,true))
        {

            MessageInformation("离子风开失败!",false);
        }
    }







    //走到反面检测
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-(m_iPublicLong/2+m_iLightOpen)+ m_iBackOffSetX, -3696+m_iBackOffSetY,m_iBackOffSetZ-4*m_iCircle14,m_iLineVel,m_iLineAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    if(m_bBackTwice == false)
    {
        //离子风
        if(!EnableClearSetting(1,false))
        {

            MessageInformation("离子风开失败!",false);
        }

    }


    //反面同轴、补光、低角度
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-m_iPublicLong/2+ m_iBackOffSetX, -3696+m_iBackOffSetY,m_iBackOffSetZ-4*m_iCircle14,m_iBackVel,m_iBackAcc);//
    flag = m_MotionCard.CoordinateBufIO(1,0x0004,0x0000);//触发正背检测相机
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1-m_iPublicLong/2+m_iLightOpen-8000+ m_iBackOffSetX, -3696+m_iBackOffSetY,m_iBackOffSetZ-4*m_iCircle14,m_iBackVel,m_iBackAcc);//156000
    flag = m_MotionCard.CoordinateBufIO(1,0x0004,0xFFFF);//关闭 反背检测相机触发 背面检测同轴光、补光
    flag = m_MotionCard.CoordinateLineMove(1,m_iP1+m_iPublicLong/2+m_iLightOpen+ m_iBackOffSetX, -3696+m_iBackOffSetY,m_iBackOffSetZ-4*m_iCircle14,m_iBackVel,m_iBackAcc);//156000
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);


    ///////摄像头///////
    flag = m_MotionCard.CoordinateLineMove(1,m_iP2 - m_iLong/2 + m_iLightOpen+7484+ m_iCameraOffSetX,m_iCameraOffSetY,m_iCameraOffSetZ-4*m_iCircle14,m_iBackVel,m_iBackAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    flag = m_MotionCard.CoordinateBufIO(1,0x4000,0x0000);//触发摄像头光源、相机
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟1s
    flag = m_MotionCard.CoordinateBufIO(1, 0x4000, 0xFFFF);//关闭 摄像头 相机、光源
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);

    ///////闪光灯///////
    if(m_bExposureValid[5])
    {
        flag = m_MotionCard.CoordinateLineMove(1,m_iFlashOffSetX,m_iFlashOffSetY,m_iFlashOffSetZ,m_iBackVel,m_iBackAcc);
        flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
        flag = m_MotionCard.CoordinateBufIO(1,0x2000,0x0000);//触发闪光灯光源、相机
        flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟1s
        flag = m_MotionCard.CoordinateBufIO(1, 0x2000, 0xFFFF);//关闭 闪光灯 相机、光源
        flag = m_MotionCard.CoordinateStart(1);
        flag = m_MotionCard.CoordinateMovedForXR(1);
    }
    if(m_bBackTwice)
    {
        if(!EnableClearSetting(0,false))
        {

            MessageInformation("离子风关失败!",false);
        }
    }

    return flag;
}
bool CRouteManager::IPhonePath_5()//出点检测位置
{
    bool flag;
    flag = m_MotionCard.CoordinateLineMove(1,m_iBackGrat - m_iLong/2 - 20000,0,m_iBackOffSetZ-4*m_iCircle14,m_iLineVel,m_iLineAcc);
    //flag = m_MotionCard.CoordinateBufDelay(1,50);//延迟50ms
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
