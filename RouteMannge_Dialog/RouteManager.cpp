#include "RouteManager.h"
#include "QtFileOperate.h"
#include "DefinedGuGaoIO.h"
#include <QSemaphore>//信号量
#include <sstream>
#include <QMessageBox>
#include "DlgRouteManage.h"
//提供了高层次的函数接口 (APIs)，使得编写的程序，可根据当前计算机中实际的 CPU 核数，自动调整运行的线程数目。
#define DelayTime 1000
CRouteManager::CRouteManager():
    m_funErrorInfo(nullptr),
    m_funRunStatus(nullptr), //状态回调
    m_bInitMotionSuc(false),
    m_bEnableMotionSuc(false),
    m_bMotionGoHomeSuc(false),
    m_bMotionResetSuc(false),
    m_bMotionStartSuc(false),
    m_bMotionStopSuc(false),
    m_bLoadRouteParamSuc(false),
    m_bIsThreadContinueRun(false),
    m_bStartMotionSignalRead(false),
    m_bMototionEmergency(false),
    m_bIsMotionInspectAuto(false),
    m_bFrontRunSuc(true),
    m_bBackRunSuc(true),
    m_iThreadContinueRunType(-1)
{
    //初始化变量
    //path1
    m_iFrontVel = 0;
    m_iFrontAcc = 0;
    //path2
    m_iFrameVel = 0;
    m_iFrameAcc = 0;
    //path3
    m_iUpDownCameraVel = 0;
    m_iUpDownCameraAcc = 0;
    //path4
    m_iBackVel = 0;
    m_iBackAcc = 0;
    //path5
    m_iLineVel = 0;
    m_iLineVel = 0;
    qRegisterMetaType<e_StatusInfoType>("e_StatusInfoType");

    m_eRouteControlStatus = eRCS_Exception;
    for(int i = 0;i< MAX_ROUTEMOTION_AXISCOUNT;i++)
    {
        m_bEnableAxsisSuc[i] = false;
    }

    m_iMotionCrdNumber = 1;


    m_bPressStart = false;
    m_bPressStop = false;
    m_bPressReset = false;
    m_bPressEmergentStop = false;
    m_bPressRunFront = false;
    m_bPressRunBack = false;

    //初始化成员变量
    m_p1 = 304400-3120;//正背同轴光
    m_p2 = 580000;//背面摄像头
    m_p3 = 655000;//中框同轴光
    m_p4 = 900000-770;//翻转机构
    m_OutJudge = 860000;//出口判断
    m_p5 = 1040000;//取点
    m_Long = 150800;
    m_Width = 75500;
    m_W_H = (m_Long - m_Width)/2;
    m_LightOpen = 10000;
    m_Circle14 = 25920;
    m_FrontGrat = 75000;
    m_BackGrat = 960000;
    m_CylinderOffset = -20000 + 2000;
    m_FrameStep = 9000;
    m_FrameOffset = 11100;//20000-11100 =8900
    m_CameraOffset = 14900;
    m_FrontBackImageHeight = 13000;
    m_FrontBackDDROffSet = 0;
    m_FrontBackYOffSet = -3696;
    connect(this,&CRouteManager::signalSentMessageInfomation,this,&CRouteManager::slotGetMessageInfomation,Qt::BlockingQueuedConnection);
}
bool CRouteManager::InitRoutePath(QString strRoutePath)
{
    m_strRoutePath = strRoutePath;

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


    //m_MotionCard.SetExtMdlIoBit(1,8,0);
    m_eRouteControlStatus = eRCS_Init;
    SendRouteStatus(m_eRouteControlStatus);
    MessageInformation("准备就绪",false,false);

    m_bStartMotionSignalRead = true;
    QFuture<bool> future = QtConcurrent::run(this, &CRouteManager::ThreadMotionSignalRead);




   
    return true;
}
void CRouteManager::ReadConfig()
{
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

   //path1
   m_iFrontVel = FileOperate.MyReadPrivateProfileInt("Path1Control","FrontVel",0,m_strRouteFile);
   m_iFrontAcc = FileOperate.MyReadPrivateProfileInt("Path1Control","FrontAcc",0,m_strRouteFile);
   //path2
   m_iFrameVel = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameVel",0,m_strRouteFile);
   m_iFrameAcc = FileOperate.MyReadPrivateProfileInt("Path2Control","FrameAcc",0,m_strRouteFile);
   //path3
   m_iUpDownCameraVel = FileOperate.MyReadPrivateProfileInt("Path3Control","UpDownCameraVel",0,m_strRouteFile);
   m_iUpDownCameraAcc = FileOperate.MyReadPrivateProfileInt("Path3Control","UpDownCameraAcc",0,m_strRouteFile);
   //path4
   m_iBackVel = FileOperate.MyReadPrivateProfileInt("Path4Control","BackVel",0,m_strRouteFile);
   m_iBackAcc = FileOperate.MyReadPrivateProfileInt("Path4Control","BackAcc",0,m_strRouteFile);
   //path5
   m_iLineVel = FileOperate.MyReadPrivateProfileInt("Path5Control","LineVel",0,m_strRouteFile);
   m_iLineAcc = FileOperate.MyReadPrivateProfileInt("Path5Control","LineAcc",0,m_strRouteFile);
}
void CRouteManager::SaveConfig()
{
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

    //path1
    FileOperate.MyWritePrivateProfileInt("Path1Control","FrontVel",m_iFrontVel,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("Path1Control","FrontAcc",m_iFrontAcc,m_strRouteFile);
    //path2
    FileOperate.MyWritePrivateProfileInt("Path2Control","FrameVel",m_iFrameVel,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("Path2Control","FrameAcc",m_iFrameAcc,m_strRouteFile);
    //path3
    FileOperate.MyWritePrivateProfileInt("Path3Control","UpDownCameraVel",m_iUpDownCameraVel,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("Path3Control","UpDownCameraAcc",m_iUpDownCameraAcc,m_strRouteFile);
    //path4
    FileOperate.MyWritePrivateProfileInt("Path4Control","BackVel",m_iBackVel,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("Path4Control","BackAcc",m_iBackAcc,m_strRouteFile);
    //path5
    FileOperate.MyWritePrivateProfileInt("Path5Control","LineVel",m_iLineVel,m_strRouteFile);
    FileOperate.MyWritePrivateProfileInt("Path5Control","LineAcc",m_iLineAcc,m_strRouteFile);
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

//获取最后的异常
const s_ErrorInfo & CRouteManager::GetLastError()
{
    return m_sErrorInfo;
}

 void CRouteManager::SendLastError()
 {
     return;
     if(m_funErrorInfo != nullptr)
     {
         m_funErrorInfo(m_sErrorInfo);
     }
 }

 void CRouteManager::SendRouteStatus(e_RouteControlStatus eStatus, int iValue)
 {
     return;
     if(m_funRunStatus != nullptr)
     {
         m_funRunStatus(eStatus,iValue);
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
 void CRouteManager::slotGetMessageInfomation(QString strAlarm)
 {
     QMessageBox::information(0,"警告",strAlarm);
 }

 void CRouteManager::MessageInformation(QString strAlarm, bool bMessageBox, bool bAlarm)
 {
     return;
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
        //进料置下位
        if(!InputSideDown())
        {
            m_eRouteControlStatus = eRCS_StartFail;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("进料置下位失败!",false);
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
        //出料置下位
        if(!OutputSideDown())
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
            flag = m_MotionCard.CoordinateLineMove(1,2885,-3520,0,50,20);//此 长轴回零 位置需要实际验证
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
    if(!InputSideDown())
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
    //出料置下位
    if(!OutputSideDown())
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

    m_MotionCard.CoordinateLineMove(1,m_FrontGrat + m_Long/2 + 10000,0,0,m_iLineVel,m_iLineAcc);//此 长轴回零 位置需要实际验证
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
    m_MotionCard.CoordinateLineMove(1,2885,-3520,0,m_iLineVel,m_iLineAcc);//夹点需要实际验证
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
                Sleep(2000);
                continue;
            }
            //判断有产品 等待2秒
            if(!InputProductOn(500))
            {

                m_bFrontRunSuc = false;
                MessageInformation("请放置产品！",false,false);
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
            //进料定位气缸-伸
//            if(!Orientated(true))
//            {

//				MessageInformation("进料定位气缸-伸失败！", false);
//                m_bFrontRunSuc = false;
//				bIsAlreadyFrontRun = false;
//				Sleep(200);
//	    		continue;
//            }
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
            //进料上升气缸置下位
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
            Sleep(500);
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

        //更新界面显示状态

        SendRouteStatus(eRCS_StartCheck);

        MessageInformation("Run检测进行中...",false,false);


        SendRouteStatus(eRCS_RunCurrentStepNum,15);
        if(m_bIsThreadContinueRun)
        {
            IPhonePath_1();//手机正面
        }
        else
        {

            m_SemaphoreContinueRun.release();

            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);

            return;
        }

        SendRouteStatus(eRCS_RunCurrentStepNum,25);

        if(m_bIsThreadContinueRun)
        {
            if(!IPhonePath_2())//中框
            {
                m_eRouteControlStatus = eRCS_StopSuccess;
                SendRouteStatus(m_eRouteControlStatus);
                MessageInformation("已结束运行",false,false);

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
        SendRouteStatus(eRCS_RunCurrentStepNum,35);

        if(m_bIsThreadContinueRun)
        {
            if(!CylinderReady())
            {
                m_bIsThreadContinueRun = false;
                m_eRouteControlStatus = eRCS_RunFrontFail;
                SendRouteStatus(m_eRouteControlStatus);

                MessageInformation("翻转机构准备失败！",false);



                return;
            }
            IPhonePath_3();//翻转+摄像头
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
            IPhonePath_4();//反面
        }
        else
        {

            m_SemaphoreContinueRun.release();
            m_eRouteControlStatus = eRCS_StopSuccess;
            SendRouteStatus(m_eRouteControlStatus);
            MessageInformation("已结束运行",false,false);


            return;
        }

        SendRouteStatus(eRCS_RunCurrentStepNum,65);

        if(m_bIsThreadContinueRun)
        {
            IPhonePath_5();//走到出点判断光栅位置
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

                MessageInformation("后光栅有遮挡！",false);
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
        m_MotionCard.CoordinateLineMove(1,m_p5,-3800,-4*m_Circle14,m_iLineVel,m_iLineAcc);//夹点需要实际验证
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

                MessageInformation("后光栅有遮挡！",false);
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

                MessageInformation("后光栅有遮挡！",false);
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

                MessageInformation("后光栅有遮挡！",false);
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


                MessageInformation("后光栅有遮挡！",false);
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

        m_MotionCard.CoordinateLineMove(1,m_FrontGrat + m_Long/2 + 10000,-3520,0,m_iLineVel,m_iLineAcc);//偏置2W以规避
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


                MessageInformation("前光栅有遮挡！",false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
                Sleep(200);
                continue;
            }
            //进料置上位
            if(!InputSideUp())
            {


                MessageInformation("进料置上位失败！",false);
                m_bBackRunSuc = false;
                bIsAlreadyToInside = false;
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
            if(!GratingFront())
            {


                MessageInformation("前光栅有遮挡！",false);
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
        m_MotionCard.CoordinateLineMove(1,2885,-3520,0,m_iLineVel,m_iLineAcc);//夹点需要实际验证
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
    m_MotionCard.GetExtMdlIoBit(0,6,Status[0]);
    m_MotionCard.GetExtMdlIoBit(0,8,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
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
    }
    //进料上升气缸-上
    //判断前部光栅
    if(!GratingFront())
    {
        return false;
    }
    m_MotionCard.GetExtMdlIoBit(0,2,Status[0]);
    m_MotionCard.GetExtMdlIoBit(0,4,Status[1]);
    if(Status[0]!=0 || Status[1]!=0)
    {
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
           return false;
        }
    }
    //翻转上升气缸-上
    m_MotionCard.GetExtMdlIoBit(0,13,OutValue);
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
    m_MotionCard.GetExtMdlIoBit(0,11,OutValue);
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
    Sleep(50);
    //翻转上升气缸-上
    m_MotionCard.GetExtMdlIoBit(0,13,OutValue);
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
    m_MotionCard.GetExtMdlIoBit(0,15,OutValue);
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
            MessageInformation("翻转上升气缸未置下点!");
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
    int a;
    if(flag)
    {
        //进料定位气缸-伸
        m_MotionCard.GetExtMdlIoBit(0,1,OutValue);
        if(OutValue!=0)
        {
            m_MotionCard.SetExtMdlIoBit(0,1,1);
            m_MotionCard.SetExtMdlIoBit(0,0,0);
            a = 0;
            do
            {
                m_MotionCard.GetExtMdlIoBit(0,1,OutValue);
                Sleep(5);
                a++;
            }while(OutValue!=0 && a< DelayTime);
            if(OutValue != 0)
            {
                 return false;
            }
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
bool CRouteManager::TowerBuzzerOn(bool flag)
{
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
    if(GratingFront())
    {
        //进料置上位
        InputSideUp();
    }

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
    if(!CylinderSetStatic())
    {
        Sleep(200);
    }
}
bool CRouteManager::IPhonePath_1()//正面检测
{
    bool flag;
    //走到正面检测
    flag = m_MotionCard.CoordinateLineMove(1,m_p1-(m_Long/2+m_LightOpen),m_FrontBackYOffSet,m_FrontBackDDROffSet,m_iLineVel,m_iLineAcc);
	//开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //开启进料口出料口准备线程
    QFuture<void> future = QtConcurrent::run(this, &CRouteManager::ThreadInputSideAndOutputSideReadyFun);
    //正面同轴、补光、低角度
    flag = m_MotionCard.CoordinateLineMove(1,m_p1-m_Long/2,m_FrontBackYOffSet,m_FrontBackDDROffSet,m_iFrontVel,m_iFrontAcc);//
    flag = m_MotionCard.CoordinateBufIO(1,0x0002,0x0000);//触发正背检测相机
    flag = m_MotionCard.CoordinateLineMove(1,m_p1-m_Long/2+m_LightOpen,m_FrontBackYOffSet,m_FrontBackDDROffSet,m_iFrontVel,m_iFrontAcc);//156000
    flag = m_MotionCard.CoordinateBufIO(1,0x0002,0xFFFF);//关闭 正背检测相机触发 正背检测同轴光、补光
    flag = m_MotionCard.CoordinateLineMove(1,m_p1+m_Long/2+m_LightOpen,m_FrontBackYOffSet,m_FrontBackDDROffSet,m_iFrontVel,m_iFrontAcc);//156000
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
bool CRouteManager::IPhonePath_2()//中框
{
    bool flag;
    short sPlusTime = 500;
    int StepLong = m_Long/m_FrameStep / 2 + 1;//16
    int StepWidth = m_Width/m_FrameStep / 2;//8
    flag = m_MotionCard.ComparePort(1,11,0);
    //走到第一边准备位置
    flag = m_MotionCard.CoordinateLineMove(1,m_p3-(m_Long/2+m_FrameStep),m_FrameOffset,0,m_iLineVel,m_iLineAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //位置比较
    flag = m_MotionCard.CompareLinear(1,1,0,StepLong,2*m_FrameStep,sPlusTime,1);
    //第一边
    flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 + 2*m_FrameStep ,m_FrameOffset+0,0,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第一个R角
    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 - LongOffsetX,m_FrameOffset-LongOffsetY,-m_Circle14/2,vel,acc);
    flag = m_MotionCard.CoordinateLineMove(1,685720,-16661-8900,-m_Circle14/2,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,1);//延迟1ms
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);

    //第二边
    flag = m_MotionCard.CoordinateLineMove(1,m_p3 - (m_Width/2 + m_FrameStep) + 3600,m_FrameOffset-m_W_H,-m_Circle14,m_iFrameVel,m_iFrameAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);

    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    //位置比较
    flag = m_MotionCard.CompareLinear(1,1,0,StepWidth,2*m_FrameStep,sPlusTime,1);
    flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Width/2 + 3600,m_FrameOffset-m_W_H,-m_Circle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第二个R角20000+2610
    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Width/2 - WidthOffsetX,m_FrameOffset-WidthOffsetY-m_W_H,-m_Circle14-m_Circle14/2,vel,acc);
    flag = m_MotionCard.CoordinateLineMove(1,631395,-16863-8900,-m_Circle14-m_Circle14/2,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,1);//延迟1ms
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);

    //第三边
    flag = m_MotionCard.CoordinateLineMove(1,m_p3-(m_Long/2+m_FrameStep),m_FrameOffset+0,-2*m_Circle14,m_iFrameVel,m_iFrameAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //位置比较
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    flag = m_MotionCard.CompareLinear(1,1,0,StepLong,2*m_FrameStep,sPlusTime,1);
    //第三边
    flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 + 2*m_FrameStep ,m_FrameOffset+0,-2*m_Circle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第三个R角
    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Long/2 - LongOffsetX,m_FrameOffset-LongOffsetY,-2*m_Circle14-m_Circle14/2,vel,acc);
    flag = m_MotionCard.CoordinateLineMove(1,685620,-18561-8900,-2*m_Circle14-m_Circle14/2,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,1);//延迟1ms
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);
    //第四边
    flag = m_MotionCard.CoordinateLineMove(1,m_p3 - (m_Width/2 + m_FrameStep) + 3600,m_FrameOffset-m_W_H,-3*m_Circle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟100ms
    //位置比较
    flag = m_MotionCard.CompareLinear(1,1,0,StepWidth,2*m_FrameStep,sPlusTime,1);
    flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Width/2 + 3600,m_FrameOffset-m_W_H,-3*m_Circle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    //第四个R角
    //flag = m_MotionCard.CoordinateLineMove(1,m_p3 + m_Width/2 - WidthOffsetX,m_FrameOffset-WidthOffsetY-m_W_H,-3*m_Circle14-m_Circle14/2,vel,acc);
    flag = m_MotionCard.CoordinateLineMove(1,631380,-19260-8900,-3*m_Circle14-m_Circle14/2,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,1);//延迟1ms
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    flag = m_MotionCard.ComparePulse(1,0,sPlusTime);

    ////////走到翻转机构/////
    flag = m_MotionCard.CoordinateLineMove(1,m_p4-50000,m_CylinderOffset,-3*m_Circle14,m_iFrameVel,m_iFrameAcc);
    flag = m_MotionCard.CoordinateLineMove(1,m_p4,m_CylinderOffset,-3*m_Circle14,m_iFrameVel,m_iFrameAcc);
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
bool CRouteManager::IPhonePath_3()//翻转+摄像头
{
    bool flag;
    ////////翻转//////
    //判断真空吸有产品
    if(!AxisProductOn(5000))
    {
        return false;
    }
    //停止吸气
    if(!AxisAirOn(false))
    {
        return false;
    }
    //翻转夹紧气缸-紧
    //翻转上升气缸-上
    //翻转气缸动点
    //翻转上升气缸-下
    if(!CylinderMove())
    {
        return false;
    }
    Sleep(50);
    //翻转夹紧气缸-松
    if(!CylinderSetEmpty())
    {
        return false;
    }
    Sleep(50);
    //开始吸气
    if(!AxisAirOn(true))
    {
        return false;
    }
    //判断真空吸有产品
    if(!AxisProductOn(5000))
    {
        return false;
    }

    ///////摄像头///////
    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    flag = m_MotionCard.CoordinateLineMove(1,m_p2 - m_Long/2 + 10*m_LightOpen,m_CameraOffset/2,-4*m_Circle14,m_iUpDownCameraVel,m_iUpDownCameraAcc);
    flag = m_MotionCard.CoordinateLineMove(1,m_p2 - m_Long/2 + m_LightOpen+7484,m_CameraOffset,-4*m_Circle14,m_iUpDownCameraVel,m_iUpDownCameraAcc);
    flag = m_MotionCard.CoordinateBufDelay(1,200);//延迟1s
    flag = m_MotionCard.CoordinateBufIO(1,0x4000,0x0000);//触发摄像头光源、相机
    flag = m_MotionCard.CoordinateBufDelay(1,100);//延迟1s
  
    flag = m_MotionCard.CoordinateLineMove(1,m_p2 - m_Long/2,m_CameraOffset,-4*m_Circle14,m_iUpDownCameraVel,m_iUpDownCameraAcc);
    flag = m_MotionCard.CoordinateBufIO(1, 0x4000, 0xFFFF);//关闭 摄像头 相机、光源

    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
bool CRouteManager::IPhonePath_4()//背面检测
{
    bool flag;
    //走到反面检测
    flag = m_MotionCard.CoordinateLineMove(1,m_p1-(m_Long/2+m_LightOpen),m_FrontBackYOffSet,m_FrontBackDDROffSet-4*m_Circle14,m_iLineVel,m_iLineAcc);
    //反面同轴、补光、低角度
    flag = m_MotionCard.CoordinateLineMove(1,m_p1-m_Long/2,m_FrontBackYOffSet,m_FrontBackDDROffSet-4*m_Circle14,m_iFrontVel,m_iFrontAcc);//
    flag = m_MotionCard.CoordinateBufIO(1,0x0002,0x0000);//触发正背检测相机
    flag = m_MotionCard.CoordinateLineMove(1,m_p1-m_Long/2+m_LightOpen,m_FrontBackYOffSet,m_FrontBackDDROffSet-4*m_Circle14,m_iFrontVel,m_iFrontAcc);//156000
    flag = m_MotionCard.CoordinateBufIO(1,0x0002,0xFFFF);//关闭 反背检测相机触发 背面检测同轴光、补光
    flag = m_MotionCard.CoordinateLineMove(1,m_p1+m_Long/2+m_LightOpen,m_FrontBackYOffSet,m_FrontBackDDROffSet-4*m_Circle14,m_iFrontVel,m_iFrontAcc);//156000
    //开始运动
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);
    return flag;
}
bool CRouteManager::IPhonePath_5()//出点检测位置
{
    bool flag;
    flag = m_MotionCard.CoordinateLineMove(1,m_BackGrat - m_Long/2 - 10000,0,-4*m_Circle14,m_iLineVel,m_iLineAcc);
    //flag = m_MotionCard.CoordinateBufDelay(1,50);//延迟50ms
    flag = m_MotionCard.CoordinateStart(1);
    flag = m_MotionCard.CoordinateMovedForXR(1);


    return flag;
}
