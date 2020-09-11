/*
* Copyright (c) 2018, 博众精工北京技术研究院
* All rights reserved.
*
* 文件名称： 固高八轴控制卡调试动态库
* 文件标识： 见配置管理计划书
* 摘要： 简要描述本文件的内容
*
* 当前版本： 1.0_20190123
* 作者： 李朋辉
* 完成日期： 2018年09月01日
*/

#ifndef MOTIONCARD_H
#define MOTIONCARD_H

#if defined(MOTIONCARD_LIBRARY)
#  define MOTIONCARDSHARED_EXPORT __declspec(dllexport)
#else
#  define MOTIONCARDSHARED_EXPORT __declspec(dllimport)
#endif

#include <memory>
#include <string>
#include <functional>
#include "MotionDataType.h"
class CMotionCardImpl;
class CCoordinateSys;

class MOTIONCARDSHARED_EXPORT CMotionCard
{
public:
    struct s_MotionErrorInfo
    {
        int iErrorCode = 0;	//错误代码（0：正常）
        int iErrorGrade = 0; // 报警级别 0:操作 1：提示 2：报警 3错误， 4：异常
        std::string strErrorDes;	//错误描述
        std::string strErrorMark;		//附加信息
    };

    struct s_MotionInitParam
    {
        int iCardNum = 0;  //iCardNum:运动卡号
        bool bExtMdlFlag = false;
        std::string strGTFilePath;//运动卡初始化路径，传给固高库
        std::string strGTExtMdlFilePath;//运动卡扩展模块初始化路径，传给固高库
        std::string strMotionFilePath; //运动卡参数路径
        std::function<void(int)> funCallBackInfo; //回调信息
        std::function<void(const s_MotionErrorInfo &)> funErrorInfo; //报警信息

    };

    struct s_CoordinateSysOut
    {
        short CrdNumber = 0;  //坐标系号 只能为1 或 2
        short  LineAxisX = 0;
        short  LineAxisY = 0;
        short  DDRAxisZ = 0;

    };

public:
    CMotionCard();
    ~CMotionCard();
    bool InitMotionCard(const s_MotionInitParam &sInitParam);

    /////////////////////////单轴运动//////////////////////////
    bool AxisEnabled(short  AxisNum,bool flag);
    bool AxisStop(short  AxisNum,long option = 0);
    // option:0为平滑停止 1为急停 AxisNum 1~8轴 9坐标系1 10坐标系2
    bool AxisGoHome(short AxisNum);
    bool AxisEncPos(double &value,short AxisNum);
    bool AxisP2p(long step, double vel,short AxisNum);
    bool ClearDriverAlarm(short AxisNum);
    ///////////////////读写IO口 通用数字输入输出 doIndex[1 16]//////////////////////
    bool GetDoOutput(long &outValue,short diType = 12);
    bool GetDiInput(long &outValue,short diType = 4);
    bool GetSingleDoOutput(short doIndex, short &outValue,short diType = 12);
    bool GetSingleDiInput(short doIndex, short &outValue,short diType = 4);
    bool SetDoOutput(short doIndex, short value, short doType = 12);
    bool SetDoOutput(long value,short doType = 12);
    ///////////////////扩展模块 数字输入输出 ExtMdlNum[0 15] index[0 15]//////////////////////
    bool SetExtMdlIoValue(short ExtMdlNum,unsigned short value);//设置输出
    bool GetExtMdlIoValue(short ExtMdlNum,unsigned short &outValue);//读取输入
    bool GetExtDoValue(short ExtMdlNum,unsigned short &outValue);//读取输出
    bool SetExtMdlIoBit(short ExtMdlNum,short index,unsigned short value);//设置输出
    bool GetExtMdlIoBit(short ExtMdlNum,short index,unsigned short &outValue);//读取输入
    /////////////////////////调用对话框///////////////////////////
    bool CallModelDlg();
    bool CallDebugDlg();
    ////////////////////////坐标系相关//////////////////////////////
    //坐标系相关 CrdNumber为坐标系，只能为1 2
    bool CoordinateEnable(short CrdNumber);
    bool CoordinateStart(short CrdNumber);
    bool CoordinateClear(short CrdNumber);
    bool CreatCoordinate(short CrdNumber,short  LineAxisX,short  LineAxisY,short  DDRAxisZ);
    bool CoordinateLineMove(short CrdNumber,double x_pos, double y_pos, double z_pos, double vel, double acc,double velEnd=0.0);//最后·两个参数不要 跟轴同步
    bool CoordinateHeliMove(short CrdNumber,double x_pos, double y_pos, double z_pos, double r, double vel, double acc,double velEnd=0.0);
    bool CoordinateLineMove(short CrdNumber,double x_pos, double y_pos, double z_pos,double velEnd=0.0);//最后·两个参数不要 跟轴同步
    bool CoordinateHeliMove(short CrdNumber,double x_pos, double y_pos, double z_pos, double r,double velEnd=0.0);
    bool CoordinateMoved(short CrdNumber);
    bool CoordinateMovedForXR(short CrdNumber);//特种函数
    bool CoordinateMovedStop(short CrdNumber);
    bool CoordinateGoHome(short CrdNumber);
    bool GetCoordinateParam(short CrdNumber,s_CoordinateSysOut &s_CoordinateSysOut);
    bool CoordinateBufIO(short CrdNumber,unsigned short doMask,unsigned short doValue,unsigned short doType = 12);//坐标系号 是否有操作 操作值 输出类型默认为12
    bool CoordinateBufDelay(short CrdNumber,unsigned short delayTime);//坐标系号 延迟时间
    bool SetCoordinateAcc(short CrdNumber,double acc);
    bool SetCoordinateVel(short CrdNumber,double vel);

    ////////////////////////位置比较//////////////////////////////
    bool ComparePort(short channel,short hsio0,short hsio1);//channel：0为HSIO 1为GPO
    //二维位置比较
    bool Compare2DClear(short chn);
    bool Compare2DMode(short chn,short mode);//mode：0为1D，1为2D
    bool Compare2DPulse(short chn,short level,short outputType,short time);
    bool Compare2DStop(short chn);
    bool Compare2DStatus(short chn,short *pStatus,long *pCount,short *pFifo,short *pFifoCount);
    bool Compare2DSetPrm(short chn,My2DComparePrm *pPrm);
    bool Compare2DData(short chn,short count,My2DCompareData *pBuf,short fifo);
    bool Compare2DStart(short chn);
    bool Compare2DClearData(short chn);

    //一维位置比较
    bool ComparePulse(short level,short outputType,short time);
    bool CompareStop();
    bool CompareStatus(short *pStatus,long *pCount);
    bool CompareData(short encoder,short source,short pulseType,short startLevel,short time,long *pBuf1,short count1,long *pBuf2,short count2);
    bool CompareLinear(short encoder,short channel,long startPos,long repeatTimes,long interval,short time,short source);
    bool CompareContinuePulseMode(short mode,short count,short standTime);
private:
    std::shared_ptr<CMotionCardImpl> m_pMotionImpl;
};

#endif // MOTIONCARD_H
