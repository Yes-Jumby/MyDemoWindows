#ifndef SCHEMATYPE_H
#define SCHEMATYPE_H

#include <windows.h>
#include <QString>
#include <vector>
#pragma execution_character_set("utf-8")

#define MAX_SCHEMA_AXLE_COUNT 8

enum e_SchemaPageMode
{
    eSPM_Normal=0,
    eSPM_GoAndBack,
    eSPM_FreQuency,
    eSMP_Combin,
    eSPM_GoAndBack_FreQuency_CheckAlone,
    eSPM_GoAndBack_FreQuency_CheckTogether

};
//初始化
struct s_SchemaPathInit
{

    QString strSchemaPath;
    QString strCommomPath;
    s_SchemaPathInit()
    {
        strCommomPath = ""; //Commom所在路径
        strSchemaPath = "";
    }
};

//错误参数
struct s_SchemaErrInfo
{
    int iErrorCode;	//错误代码（0：正常）
    QString strErrorDes;	//错误描述
    QString strErrorMark;		//附加信息
    s_SchemaErrInfo()
    {
        iErrorCode = 0;
        strErrorDes = "";
        strErrorMark = "";
    }
};

//采图方案信息
struct s_SchemaBaseInfo
{
    bool bValid;
    QString strSchemaName;
    int iPageCount;
    int iCameraCount;
    s_SchemaBaseInfo()
    {
        Reset();

    }

    void Reset()
    {
        bValid = false;
        strSchemaName = "";
        iPageCount = 0;
        iCameraCount = 0;
    }

};

struct s_SchemaCombinImgInfo
{
    int iImgStartLine; //从0开始
    int iImgCutHeight;//图像裁切高度
    s_SchemaCombinImgInfo() {}
};

//采图方案——Page信息
struct s_SchemaCombinInfo
{
    int iCombineCount;
    int iCombinStartNo;
    int iPageNo;
    std::vector<s_SchemaCombinImgInfo> vecCombinImgInfo;

    s_SchemaCombinInfo() {}
};
struct s_SchemaPageInfo
{
    int iPageNo;
    QString strPageName;
    int iClientNo;
    int iStationNo;
    int iCameraSelfNo;
    int iImageWidth;
    int iImageHeight;
    int iImageChannel;
    double dbResolutionH;
    double dbResolutionV;
    e_SchemaPageMode ePageMode;
    std::vector<s_SchemaCombinInfo> vecCombinInfo;
    int iGrabNormalNo;
    int iGoAndBackNo;
    int iFrequencyNo;

    s_SchemaPageInfo() {}

};


//采图方案——相机信息
struct s_SchemaCameraInfo
{
    int iCameraSelfNo;
    int iClientNo;
    int iStationNo;
    e_SchemaPageMode ePageMode;
    int iNormalGrabCount;
    int iCombineGrabCount;
    int iGoAndBackCount;
    int iFrequencyCount;
    int iImageWidth;
    int iImageHeight;
    int iImageChannel;


    s_SchemaCameraInfo()
    {
        iCameraSelfNo = -1;
        iClientNo = -1;
        iStationNo = -1;
        ePageMode = eSPM_Normal;
        iNormalGrabCount = -1;
        iCombineGrabCount = -1;
        iGoAndBackCount = -1;
        iFrequencyCount = -1;
        iImageWidth = -1;
        iImageHeight = -1;
        iImageChannel = -1;
    }

};

/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///轨迹控制
///
enum e_SchemaRouteMode
{
    eSRM_DefaultMode = 0, //默认方式
    eSRM_CustomMode, //自定义
    eSRM_AppearanceMode, //全检方式
    eSRM_FrameOnlyMode   //中框方式
};

enum e_SchemaRouteType
{
    eSRT_Motion = 0,
    eSRT_Light,         //光源控制
    eSRT_Camera
};

enum e_SchemaMotionType
{
    eSMT_MotionGoHome = 0, //运动卡回零
    eSMT_MotionStart, //到达开始位置
    eSMT_MotionLine3,    //3轴直线插补
    eSMT_MotionPlug2,  //2轴插补
    eSMT_MotionSpiral3,  //3轴螺旋插补
    eSMT_MotionPositionComp, //位置比较
};

enum e_SchemaLightType
{
    eSLT_Open = 0,
    eSLt_CLose,
    eSLt_ChangeValue
};

enum e_SchemaCameraType
{
    eSLT_FrameTrigger = 0
};

//
struct s_SchemaMotionParam
{
    e_SchemaMotionType eMotionType;
    int iMotionGroupNo;
    int iMoveCount;
    int iMoveDis[MAX_SCHEMA_AXLE_COUNT];
};

struct s_SchemaLightParam
{
    e_SchemaLightType eLightType;
    int iLightGroupNo; //光源编号
    int iLightValue;
};

struct s_SchemaCameraParam
{
    e_SchemaCameraType eCameraType;
    int iCameraGroupNO;
};

struct  s_SchemaRoute
{
    e_SchemaRouteType eRouteType;
    QString strRouteName;
    s_SchemaMotionParam sMotionParam;
    s_SchemaLightParam sLightParam;
    s_SchemaCameraParam sCamraType;

    s_SchemaRoute() {}
};

typedef std::vector<s_SchemaRoute> V_SchemaRouteStep;
struct s_SchemaRouteMode
{
    e_SchemaRouteMode eRouteMode;

    int iRouteResetX;
    int iRouteResetY;
    int iRouteResetZ;

    V_SchemaRouteStep vecRouteStep;
    s_SchemaRouteMode() {}
};


#endif // SCHEMATYPE_H
