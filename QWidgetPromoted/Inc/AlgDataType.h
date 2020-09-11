#ifndef ALGDATATYPE_H
#define ALGDATATYPE_H
#pragma execution_character_set("utf-8")

#include <string>
#include <vector>
#include <windows.h>
#include <map>
#include <memory>
#include <functional>

/******************************************基本数据结构*******************************/

#define MAX_DEFECTNUM 200 //最大处理缺陷数目
#define GRAY_MULT  2
#define GRAY_BASE 100

#define GRAY_BYTE_MAX 255
#define GRAY_THRE_CONNECT_LENGHT 1000
#define MAX_DEFECT_NUM 300


typedef  void PHomMat2D;
#define FreePt(Pt) if(Pt!=nullptr){delete Pt;Pt=nullptr;}else{Pt=nullptr;}
class APoint
{
public:
    int nX;
    int nY;
    APoint()
    {
        nX=0;
        nY=0;
    }
    APoint(const int &x,const int &y)
    {
        nX=x;
        nY=y;
    }
    APoint(const APoint& pt)
    {
        nX=pt.nX;
        nY=pt.nY;
    }
    APoint& operator=(const APoint& pt)
    {
        nX=pt.nX;
        nY=pt.nY;
        return *this;
    }
    void setPoint(const int &x,const int &y)
    {
        nX=x;
        nY=y;
    }
};

//定位信息
struct s_ALocationInfo
{
    bool bIsLocat;
    std::vector<APoint> vPoints;//定位点，正左上，反右下
    float fAngle;//角度 范围
    bool bPositive;//正反
    bool bProAffine;
    PHomMat2D * pMat;//变换矩阵,只传递指针,内存在外部
    //定位建模提取参考信息
    float fRefThreadval;
    int nRefArea;
    int nRefWidth;
    int nRefHeight;
    int fRefGrayVal;
    s_ALocationInfo()
    {
        bProAffine = true;//默认透视变换 false仿射变换
        bIsLocat = false;
        fAngle=0.0;
        bPositive=true;
        fRefThreadval=-1;
        nRefArea=-1;
        nRefWidth=-1;
        nRefHeight=-1;
        fRefGrayVal=-1;
        pMat = nullptr;
    }
    s_ALocationInfo(const s_ALocationInfo& loc)
    {
        bProAffine = loc.bProAffine;
        fAngle=loc.fAngle;
        bPositive=loc.bPositive;
        fRefThreadval=loc.fRefThreadval;
        nRefArea=loc.nRefArea;
        nRefWidth=loc.nRefWidth;
        nRefHeight=loc.nRefHeight;
        fRefGrayVal=loc.fRefGrayVal;
        pMat = loc.pMat;
    }
    s_ALocationInfo& operator=(const s_ALocationInfo& loc){
        bProAffine = loc.bProAffine;
        fAngle=loc.fAngle;
        bPositive=loc.bPositive;
        fRefThreadval=loc.fRefThreadval;
        nRefArea=loc.nRefArea;
        nRefWidth=loc.nRefWidth;
        nRefHeight=loc.nRefHeight;
        fRefGrayVal=loc.fRefGrayVal;
        pMat = loc.pMat;
        return *this;
    }
    void Reset()
    {
        bProAffine = true;//默认透视变换 false仿射变换
        fAngle=0.0;
        bPositive=true;
        fRefThreadval=-1;
        nRefArea=-1;
        nRefWidth=-1;
        nRefHeight=-1;
        fRefGrayVal=-1;
        pMat = nullptr;
        vPoints.clear();
    }
};
/*封装多类型变量*/
class AVariant
{
public:
    enum DATATYPE{INT,FLOAT,STRING,NAL};
    AVariant(){
        pnVal=nullptr;
        pstrVal=nullptr;
        pfVal=nullptr;
        nType=NAL;
    }
    AVariant(const int& nVal){
        pnVal=new int(nVal);
        pstrVal = nullptr;
        pfVal = nullptr;
        nType=INT;
    }
    AVariant(const float &fVal){
        pfVal=new float(fVal);
        pnVal = nullptr;
        pstrVal = nullptr;
        nType=FLOAT;
    }
    AVariant(const std::string& strVal){
        pstrVal=new std::string(strVal);
        pnVal = nullptr;
        pfVal = nullptr;
        nType=STRING;
    }
    AVariant(const AVariant& val) {
        nType = val.nType;
        if (nType == INT&&val.pnVal != nullptr)
        {

            pnVal = new int(*val.pnVal);
            pfVal = nullptr;
            pstrVal = nullptr;
        }
        else if (nType == FLOAT&&val.pfVal != nullptr)
        {

            pfVal = new float(*val.pfVal);
            pnVal = nullptr;
            pstrVal = nullptr;

        }
        else if (nType == STRING&&val.pstrVal != nullptr)
        {

            pstrVal = new std::string(*val.pstrVal);
            pnVal = nullptr;
            pfVal = nullptr;
        }
        else
        {
            nType = NAL;
            pnVal = nullptr;
            pnVal = nullptr;
            pfVal = nullptr;
        }
    }
    ~AVariant(){
        if(nType == STRING)
        {
            FreePt(pstrVal);
        }
        if (nType == INT)
        {
            FreePt(pnVal);
        }
        if (nType == FLOAT)
        {
            FreePt(pfVal);
        }

    }

    AVariant& operator=(const int& nVal){
        if(pnVal==nullptr)
        {
            pnVal=new int(nVal);
        }
        else
        {
            *pnVal=nVal;
        }
        nType=INT;
        FreePt(pstrVal);
        FreePt(pfVal);
        return *this;
    }
    AVariant& operator=(const float& fVal){
        if(pfVal==nullptr)
        {
            pfVal=new float(fVal);
        }
        else
        {
            *pfVal=fVal;
        }
        nType=FLOAT;
        FreePt(pstrVal);
        FreePt(pnVal);
        return *this;
    }
    AVariant& operator=(const std::string& strVal){
        if(pstrVal==nullptr)
        {
            pstrVal=new std::string(strVal);
        }
        else
        {
            *pstrVal=strVal;
        }
        nType=STRING;
        FreePt(pfVal);
        FreePt(pnVal);
        return *this;
    }
    AVariant& operator=(const AVariant& val){
        nType=val.nType;
        if (nType == INT&&val.pnVal != nullptr)
        {
            if (pnVal == nullptr)
            {
                pnVal = new int(*val.pnVal);
            }
            else
            {
                *pnVal = (*val.pnVal);
            }
            FreePt(pstrVal);
            FreePt(pfVal);
        }
        else if(nType == FLOAT&&val.pfVal != nullptr)
        {
            if (pfVal == nullptr)
            {
                pfVal = new float(*val.pfVal);
            }
            else
            {
                *pfVal = (*val.pfVal);
            }
            FreePt(pstrVal);
            FreePt(pnVal);
        }
        else if (nType == STRING&&val.pstrVal != nullptr)
        {
            if (pstrVal == nullptr)
            {
                pstrVal = new std::string(*val.pstrVal);
            }
            else
            {
                *pstrVal = (*val.pstrVal);
            }
            FreePt(pfVal);
            FreePt(pnVal);
        }
        else
        {
            nType = NAL;
            FreePt(pfVal);
            FreePt(pstrVal);
            FreePt(pnVal);
        }
        return *this;
    }
    int GetIValue()
    {
        if(nType==INT&&pnVal!= nullptr)
        {
            return *pnVal;
        }
        return 0;
    }
    float GetFValue()
    {
        if(nType==FLOAT&&pfVal!= nullptr)
        {
            return *pfVal;
        }
        return 0;
    }
    std::string GetStrValue()
    {
        if(nType==STRING&&pstrVal!= nullptr)
        {
            return *pstrVal;
        }
        return "NAL";
    }
    DATATYPE GetType()
    {
        return nType;
    }
private:
    DATATYPE nType;
    int *pnVal;
    std::string *pstrVal;
    float *pfVal;
};

/*区域结构体*/
class ARect
{
public:
    int left;
    int top;
    int right;
    int bottom;
public:
    ARect(int l,int t,int w,int h)
    {
        left=l;
        right=l+max(w-1,0);//内部矫正
        top=t;
        bottom=t+max(h-1,0);//内部矫正
    }
    ARect(const ARect& rect)
    {
        left=rect.left;
        right=rect.right;
        top=rect.top;
        bottom=rect.bottom;
    }
    ARect(const RECT& rect)
    {
        left=rect.left;
        right=rect.right;
        top=rect.top;
        bottom=rect.bottom;
    }
    ARect()
    {
        left=0;
        right=0;
        top=0;
        bottom=0;
    }
    ARect& operator=(const ARect& rect){
        left=rect.left;
        right=rect.right;
        top=rect.top;
        bottom=rect.bottom;
        return *this;
    }
    ARect& operator=(const RECT& rect){
        left=rect.left;
        right=rect.right;
        top=rect.top;
        bottom=rect.bottom;
        return *this;
    }
    int Width()
    {
        return right-left;
    }
    int Height()
    {
        return bottom-top;
    }
    int getCenterX()
    {
        return (right+left)/2;
    }
    int getCenterY()
    {
        return (bottom+top)/2;
    }
    void Reset()
    {
        left=0;
        right=0;
        top=0;
        bottom=0;
    }
    ~ARect()
    {}
};

class ParARect
{
public:
    APoint ap_LTPoint;//左上
    APoint ap_RTPoint;
    APoint ap_RBPoint;
    APoint ap_LBPoint;
    ParARect():ap_LTPoint(),ap_RTPoint(),ap_RBPoint(),ap_LBPoint()
    {
    }
    ParARect(const ParARect& par)
    {
        ap_LTPoint=par.ap_LTPoint;
        ap_RTPoint=par.ap_RTPoint;
        ap_RBPoint=par.ap_RBPoint;
        ap_LBPoint=par.ap_LBPoint;
    }
    ParARect& operator=(const ParARect& par)
    {
        ap_LTPoint=par.ap_LTPoint;
        ap_RTPoint=par.ap_RTPoint;
        ap_RBPoint=par.ap_RBPoint;
        ap_LBPoint=par.ap_LBPoint;
        return *this;
    }
    void Reset()
    {
        ap_LTPoint.setPoint(0,0);
        ap_RTPoint.setPoint(0,0);
        ap_RBPoint.setPoint(0,0);
        ap_LBPoint.setPoint(0,0);
    }
};

//参数结构
class s_Params
{
public:
    std::string strParamName; //参数类型
    std::string strParamInfo; //参数说明
    //std::string strParamEnName; //参数英文字段,修改为索引关键字 20180217
    AVariant qvParamValue;    //参数值
    // AVariant qvDefaltParamValue;    //默认参数值
    AVariant qvParamMaxValue;    //最大参数值
    AVariant qvParamMinValue;    //最小参数值
    std::vector<std::string> vecComValue;//调用combox方式 从0开始编号
    s_Params()
    {
        strParamName="";
        strParamInfo="";
        qvParamValue=0;
        qvParamMaxValue=0;
        qvParamMinValue=0;
    }
    s_Params(const int& qvInValue, const int& qvMaxValue, const int &qvmMinValue,const std::string& strName="NAL",const std::string& strInfo="NAL",std::vector<std::string> *vecValue=NULL)
    {
        qvParamValue=qvInValue;
        qvParamMaxValue=qvMaxValue;
        qvParamMinValue=qvmMinValue;
        //strParamEnName=strEnName;
        strParamName=strName;
        strParamInfo=strInfo;
        if(vecValue!=NULL&&!vecValue->empty())
        {
            vecComValue.clear();
            vecComValue.assign(vecValue->begin(), vecValue->end());//拷贝数据
        }
    }
    s_Params(const float& qvInValue,const float& qvMaxValue, const float& qvmMinValue,const std::string& strName="NAL",const std::string& strInfo="NAL",std::vector<std::string> *vecValue=NULL)
    {
        qvParamValue=qvInValue;
        qvParamMaxValue=qvMaxValue;
        qvParamMinValue=qvmMinValue;
        //strParamEnName=strEnName;
        strParamName=strName;
        strParamInfo=strInfo;
        if(vecValue!=NULL&&!vecValue->empty())
        {
            vecComValue.clear();
            vecComValue.assign(vecValue->begin(), vecValue->end());//拷贝数据
        }
    }
    void Reset()
    {
        strParamName="";
        strParamInfo="";
        qvParamValue=0;
        qvParamMaxValue=0;
        qvParamMinValue=0;
        vecComValue.clear();
    }
    
};
enum MASK_TYPE{MASK_TYPE_FROMINSP/*来自其他检测Rect*/,MASK_TYPE_FROMRECT/*自定义RECT*/,MASK_TYPE_FROMREGFILE/*来自外部文件异形REGION使用*/};
/*检测算法掩模参数*/
struct s_MaskParam
{
    MASK_TYPE eType;
    int nInspID;
    ARect rRect;
    std::string strFileName;
};
/*掩模管理参数*/
class CMaskParams
{
public:
    bool bOpenState;
    std::vector<s_MaskParam> vMaskParams;
    CMaskParams()
    {
        bOpenState=false;
    }
    CMaskParams(const CMaskParams& param)
    {
        vMaskParams.clear();
        bOpenState=param.bOpenState;
        vMaskParams.assign(param.vMaskParams.begin(),param.vMaskParams.end());
    }
    CMaskParams& operator =(const CMaskParams& param)
    {
        vMaskParams.clear();
        bOpenState=param.bOpenState;
        vMaskParams.assign(param.vMaskParams.begin(),param.vMaskParams.end());
        return *this;
    }
    void Reset()
    {
        bOpenState=false;
        vMaskParams.clear();
    }
};
struct stag_ColorCombin
{
    //gray = 0.299 * red + 0.587 * green + 0.114 * blue .
    double fRrat;
    double fGrat;
    double fBrat;
    stag_ColorCombin()
    {
        fRrat=0.299;
        fGrat=0.587;
        fBrat=0.114;
    }

};
struct stag_MatchParams
{
    std::string strModelIDFilePath;
    void* phvModelID;//匹配模板p
    std::string strVarModelIDFilePath;
    void* phvVarModelID;//检测模板
    bool bModelIsOk;
    stag_MatchParams()
    {
        strModelIDFilePath="";
        strVarModelIDFilePath="";
        phvModelID=nullptr;
        phvVarModelID=nullptr;
        bModelIsOk=false;
    }
     stag_MatchParams& operator =(const stag_MatchParams& param)
     {
         strModelIDFilePath=param.strModelIDFilePath;
         strVarModelIDFilePath=param.strVarModelIDFilePath;
         phvModelID=param.phvModelID;
         phvVarModelID=param.phvVarModelID;
         bModelIsOk=param.bModelIsOk;
     }
    void Reset()
     {
        strModelIDFilePath="";
        strVarModelIDFilePath="";
        phvModelID=nullptr;
        phvVarModelID=nullptr;
        bModelIsOk=false;
     }
};
//检测参数
class sInspParams
{
public:
    std::map<std::string,s_Params>* pvParams;//修改为map形式方便快速查找
    ARect RoiRect;
    bool bFlagUsingState;  //是否开启检测状态 false关闭 true开启检测
    bool bFlagDebugState;  //是否开启调试状态 false关闭 true开启检测
    CMaskParams sMaskParams;//掩模参数
    void* pInspRegion;
    stag_MatchParams sMatchParams;//搜索匹配参数
    sInspParams():sMaskParams(),sMatchParams()
    {
        pInspRegion= nullptr;
        pvParams = nullptr;
        bFlagUsingState = false;
        bFlagDebugState = false;
    }
    sInspParams(const sInspParams& inParam)
    {
        pInspRegion=inParam.pInspRegion;//只传递指针
        RoiRect = inParam.RoiRect;
        pvParams = inParam.pvParams;//只传递指针
        bFlagUsingState = inParam.bFlagUsingState;
        bFlagDebugState = inParam.bFlagDebugState;
        sMaskParams=inParam.sMaskParams;
        sMatchParams=inParam.sMatchParams;
    }
    sInspParams& operator=(const sInspParams& inParam)
    {
        pInspRegion=inParam.pInspRegion;
        RoiRect=inParam.RoiRect;
        pvParams = inParam.pvParams;//只传递指针
        bFlagUsingState = inParam.bFlagUsingState;
        bFlagDebugState = inParam.bFlagDebugState;
        sMaskParams=inParam.sMaskParams;
        sMatchParams=inParam.sMatchParams;
        return *this;
    }
};
struct s_AlgErrorInfo
{
    int nErrorType;		              //返回函数状态 0:正常 1:异常
    std::string strErrorDes;	     //状态描述
    std::string chErrorContext;      //备注信息
    s_AlgErrorInfo()
    {
        nErrorType=0;
        strErrorDes="OK";
        chErrorContext="OK";
    }
    s_AlgErrorInfo(int nE,std::string strEdes,std::string strCt)
    {
        nErrorType=nE;
        strErrorDes=strEdes;
        chErrorContext=strCt;
    }
};
struct s_StatusModelDlg
{
    int nErorType; //返回函数状态 0:正常 1:异常
    int nResult;   //0：未发生更改未添加 1：更改参数或者模板
    s_StatusModelDlg()
    {
        nErorType = 0;
        nResult = 0;
    }
    s_StatusModelDlg(int nE,int nR)
    {
        nErorType = nE;
        nResult = nR;
    }
};


//初始化结构体
struct s_AlgInitParam
{
    int iPageIndex;  //画面号,画面路径命名规则PageNo*
    int iImageWidth; //图像宽
    int iImageHeight;//图像高
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH;//横向分辨率 1个像素 mm
    double dbResolutionV;                      //纵向分辨率 1个像素 mm
    std::string strParamPath;                  //默认参数路径 例如 D:/Bin/AlgConfig
    std::string strModelPath;                  //20190220 公共模板路径使用 例如D:/User/Model
    std::vector<std::string> vstrModelName;    //20190220 多个模板路径名称，注意不是路径,如果只有一个模板就压入一个
    std::string strLogPath;                    //日志路径 例如 D:/User/Log/AlgLog
    s_AlgInitParam()
    {
        Reset();
    }
    void Reset()
    {
        iPageIndex=-1;
        iImageWidth=16000;
        iImageHeight=20000;
        iImageChannel=1;
        dbResolutionH=0.007;
        dbResolutionV=0.007;
        strParamPath="";
        strModelPath="";
        vstrModelName.clear();
        strLogPath="";
    }
};
//缺陷位置信息代码
enum DEFECT_LOCATION_CODE
{
    D1=0,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,
    H1=20,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,
    T1=40,T2,T3,
    B1=50,B2,B3,B4,B5,B6,B7,B8,
    L1=60,L2,L3,L4,L5,L6,
    R1=70,R2,R3,R4,R5
};
//缺陷类型索引表常量

const std::vector<std::string> vecDefectList={"良品","划伤","灰尘","脏污","崩边","白点","异物","雨滴","缺失"};
//检出缺陷信息 该部分信息为缺陷结果
enum DEFECT_GRAYTYPE{ DEFECT_GRAYTYPE_BLACK, DEFECT_GRAYTYPE_WHITE, DEFECT_GRAYTYPE_LIGHTABNORMAL, DEFECT_GRAYTYPE_OTHER };
struct s_AlgDefectInfo
{
    int nId;          //画面号
    int nLayerId;     //多层图像检测时层id，从0开始  CH20190121
    int iDefectID;    //缺陷类型编号 0,1,2,3···详细见索引vecDefectList
    DEFECT_LOCATION_CODE eLocCode;
    DEFECT_GRAYTYPE eGrayType;
    ARect nRect;      //缺陷位置，相对图像左上位置
    std::string strDefectName;
    float fArea;      //缺陷面积
    float fLength;    //缺陷长度
    float fWidth;     //缺陷宽度
    float fConstract; //缺陷对比度
    float fCirRat;    //缺陷圆度
    float fRectRat;   //缺陷矩形度
    float fJnd;       //缺陷JND值
    float fEnergy;    //缺陷能量
    s_AlgDefectInfo()
    {
        Reset();
    }
    void Reset()
    {
        eLocCode=D1;
        nId=-1;
        nLayerId=-1;
        iDefectID=0;
        strDefectName="NAL";
        nRect=ARect(0,0,10,10);
        fArea=10.0;
        fLength=10.0;
        fWidth=5.0;
        fConstract=1.0;
        fCirRat=0.5;
        fRectRat=0.5;
        fJnd=1.0;
    }
};

//定位结果
enum LOCATION_RESULT
{
    LOCATIONRESULT_INPARAM_ERROR,//输入参数异常
    LOCATIONRESULT_ERROR,//程序异常
    LOCATIONRESULT_LIGHT,//亮度异常
    LOCATIONRESULT_LOCATION_ERR,//定位异常
    LOCATIONRESULT_DIRECTION_ERR,//产品放反异常
    LOCATIONRESULT_PAGE_ERR,//画面异常
    LOCATIONRESULT_OK,//定位成功
};
//结果标志
enum CHECK_RESULT
{
    RESULT_INERPARAM_ERROR,//参数异常
    RESULT_ERROR,//程序异常
    RESULT_LIGHT,//亮度异常
    RESULT_LOCATION_ERR,//定位异常
    RESULT_DIRECTION_ERR,//产品放反异常
    RESULT_PAGE_ERR,//画面异常
    RESULT_OK,//良品
    RESULT_NG,//NG品
    RESULT_DUSTWARNING,//灰尘过多
    RESULT_MODELNG     //模型错误
};

//标准图像数据
struct s_Alg_DataImg
{
public:
    int nWidth;     //宽高
    int nHeight;
    int nChannel;   //图像位数 1：灰度  3：RGB 4:RGBA
    int nTaiTop;    //顶部重叠尺寸
    int nTaiBottom; //顶部重叠尺寸
    int nPixWidth;  //内存宽度
    ARect rect;     //有效roi区域，默认无需设置
    bool bDataState;//是否有内存数据
    bool bMemoryDirect;//是否有内存数据,true 正向
    BYTE* pDATA;     //图像数据
public:
    s_Alg_DataImg()
    {
        pDATA = nullptr;
        nTaiTop = 0;
        nTaiBottom = 0;
        nPixWidth = 0;
        nWidth = 0;
        nHeight = 0;
        nChannel=1;
        rect = ARect(0, 0, 0, 0);
        bDataState = false;
        bMemoryDirect=false;
    }
    s_Alg_DataImg(const s_Alg_DataImg& inData)
    {
        pDATA = inData.pDATA;
        nTaiTop = inData.nTaiTop;
        nTaiBottom = inData.nTaiBottom;
        nPixWidth = inData.nPixWidth;
        nHeight = inData.nHeight;
        nWidth = inData.nWidth;
        nChannel = inData.nChannel;
        rect = inData.rect;
        bDataState = inData.bDataState;
        bMemoryDirect=inData.bMemoryDirect;
    }
    s_Alg_DataImg(BYTE* InDATA,int nwidth,int nheight,int nT=0,int nB=0,int nchannel=1,int npixwidth=-1,bool bMemoryDt=true)
    {
        pDATA= InDATA;
        nPixWidth = npixwidth;
        nWidth = nwidth;
        nHeight = nheight;
        nChannel=nchannel;
        nTaiTop = nT;
        nTaiBottom = nB;
        rect = ARect(0, 0, 0, 0);
        if (nullptr!=pDATA)
        {
            bDataState = true;
        }
        bMemoryDirect=bMemoryDt;
    }
    s_Alg_DataImg& operator=(const s_Alg_DataImg& inData)
    {
        pDATA = inData.pDATA;
        nTaiTop = inData.nTaiTop;
        nTaiBottom = inData.nTaiBottom;
        nPixWidth = inData.nPixWidth;
        nHeight = inData.nHeight;
        nWidth = inData.nWidth;
        nChannel = inData.nChannel;
        rect = inData.rect;
        bDataState = inData.bDataState;
        bMemoryDirect=inData.bMemoryDirect;
        return *this;
    }
    bool IsDataValid()
    {
        return bDataState;
    }
    //添加拼接小图,nTop 上部分切割尺寸；nBottom 下部分切割尺寸	//添加整图
    void setRoi(ARect &rt)
    {
        rect = rt;
    }
    void ClearRoi()
    {
        rect = ARect(0, 0, 0, 0);
    }
    void Reset()
    {
        pDATA = nullptr;
        nTaiTop = 0;
        nTaiBottom = 0;
        nPixWidth = 0;
        nWidth = 0;
        nHeight = 0;
        nChannel = 1;
        rect = ARect(0, 0, 0, 0);
        bDataState = false;
        bMemoryDirect=false;
    }
    BYTE* GetData()
    {
        return pDATA;
    }
    void SetDataVal(int nVal)
    {
        if (bDataState)
        {
            if (-1==nPixWidth)
            {
                memset(pDATA, nVal, nWidth*nHeight);
            }
            else
            {
                memset(pDATA, nVal, nPixWidth*nHeight);
            }
        }
    }
};
//检测输出
struct s_AlgCheckOutputParam
{
    //通用结果参数
    int iPageIndex;                          //画面号
    CHECK_RESULT eResultFlag;                //检出结果标志
    void *pData;                             //结果数据
    ParARect Loc_Rect;                       //定位信息，相对图像
    bool bMultlayer;                         //多层模式
    std::vector<s_AlgDefectInfo> vecDefInfo;
    //std::vector<std::vector<s_AlgDefectInfo>> vecDefInfo; //算法改动量太大暂不采用缺陷列表二维素组，第一维表示图像层数,第二维为缺陷数目
    s_AlgCheckOutputParam()
    {
        Reset();
    }
    s_AlgCheckOutputParam(const s_AlgCheckOutputParam& inParam)
    {
        iPageIndex=inParam.iPageIndex;       //画面号
        eResultFlag=inParam.eResultFlag;     //检出结果标志
        Loc_Rect=inParam.Loc_Rect;           //定位信息，相对图像
        pData=inParam.pData;
        bMultlayer=inParam.bMultlayer;
        vecDefInfo.clear();
        vecDefInfo.assign(inParam.vecDefInfo.begin(), inParam.vecDefInfo.end());

        //        if(!vecDefInfo.empty())     //二维vect清空
        //        {
        //            for(int i=0;i<vecDefInfo.size();i++)
        //            {
        //                vecDefInfo[i].clear();
        //            }
        //            vecDefInfo.clear();
        //        }
        //        if (!inParam.vecDefInfo.empty())//二维复制
        //        {
        //            vecDefInfo.resize(inParam.vecDefInfo.size());
        //            for(int i=0;i<vecDefInfo.size();i++)
        //            {
        //                vecDefInfo[i].assign(inParam.vecDefInfo[i].begin(), inParam.vecDefInfo[i].end());
        //            }
        //        }
    }
    s_AlgCheckOutputParam& operator =(const s_AlgCheckOutputParam& inParam)
    {
        iPageIndex=inParam.iPageIndex;  //画面号
        eResultFlag=inParam.eResultFlag;                //检出结果标志
        Loc_Rect=inParam.Loc_Rect;//定位信息，相对图像
        pData=inParam.pData;
        bMultlayer=inParam.bMultlayer;
        vecDefInfo.clear();
        vecDefInfo.assign(inParam.vecDefInfo.begin(), inParam.vecDefInfo.end());

        //        if(!vecDefInfo.empty())     //二维vect清空
        //        {
        //            for(int i=0;i<vecDefInfo.size();i++)
        //            {
        //                vecDefInfo[i].clear();
        //            }
        //            vecDefInfo.clear();
        //        }
        //        if (!inParam.vecDefInfo.empty())//二维复制
        //        {
        //            vecDefInfo.resize(inParam.vecDefInfo.size());
        //            for(int i=0;i<vecDefInfo.size();i++)
        //            {
        //                vecDefInfo[i].assign(inParam.vecDefInfo[i].begin(), inParam.vecDefInfo[i].end());
        //            }
        //        }
        return *this;
    }

    void Reset()
    {
        iPageIndex=-1;
        eResultFlag=RESULT_OK;
        pData=nullptr;
        bMultlayer=false;
        Loc_Rect.Reset();
        vecDefInfo.clear();
        //        if(!vecDefInfo.empty())     //二维vect清空
        //        {
        //            for(int i=0;i<vecDefInfo.size();i++)
        //            {
        //                vecDefInfo[i].clear();
        //            }
        //            vecDefInfo.clear();
        //        }
    }
};
//参考参数
struct s_AlgCheckInputParam;
struct s_ReferenceParam
{
    bool bNeedRefParam;
    s_AlgCheckInputParam  *pInputParam; //外部内存
    s_AlgCheckOutputParam *pOutParam;   //外部内存
    s_ReferenceParam()
    {
        bNeedRefParam=false;
        pInputParam=nullptr;
        pOutParam=nullptr;
    }
    s_ReferenceParam(const s_ReferenceParam& inParam)
    {
        bNeedRefParam=inParam.bNeedRefParam;
        pInputParam=inParam.pInputParam;
        pOutParam=inParam.pOutParam;
    }

    s_ReferenceParam& operator =(const s_ReferenceParam& inParam)
    {
        bNeedRefParam=inParam.bNeedRefParam;
        pInputParam=inParam.pInputParam;
        pOutParam=inParam.pOutParam;
        return *this;
    }
    void Reset()
    {
        bNeedRefParam=false;
        pInputParam=nullptr;
        pOutParam=nullptr;
    }
};
struct  s_Color
{
    int r;
    int g;
    int b;
     s_Color() {
         r=255;
         g=255;
         b=255;
     }
     s_Color(int nr,int ng,int nb) {
         r=nr;
         g=ng;
         b=nb;
     }
};
enum ALG_COLOR
{
    ALG_COLOR_Red,
    ALG_COLOR_Green,
    ALG_COLOR_Blue,
    ALG_COLOR_White,
    ALG_COLOR_Black,
    ALG_COLOR_Gray,
};
//颜色识别参数
struct s_CheckColorParams
{
	ARect roiRect;
	int nThre;
	int nLenth;
	int nBaseArea;
	std::vector<s_Color> InspColorClass;
        bool bDebug;
	s_CheckColorParams() :roiRect(5336, 2374, 1767, 3200)
	{
		nThre = 50;//基本阈值
		nLenth = 1264;
		nBaseArea = 49960;
                bDebug=false;
	}
	void Reset()
	{
		nThre = 50;//基本阈值
		nLenth = 1264;
		nBaseArea = 49960;
		InspColorClass.clear();
                bDebug=false;
	}
};
/*返回颜色编号*/
enum PAGE_COLOR
{
    COLOR_YELLOW=1,//黄色
    COLOR_WHITE=2,//白色
    COLOR_BLACK=3,//黑色
    COLOR_RED=4,//红色
    COLOR_ORANGE=5,//橘红色
    COLOR_GLOD=6,//金色
	COLOR_BLUE=7,
    COLOR_NO=8,//默认无颜色
    COLOR_FALSE=9,
	COLOR_PARAM_NG = 10//参数无效
};
//检测输入
struct s_AlgCheckInputParam
{
    int iPageIndex;                //画面号
    std::string strInspName;       //检测区域名称
    int iInspId;                   //检测id
    std::string strAlgName;        //检测算法名称
    std::string strBatchNo;        //当前批号
    std::string strProductNo;      //产品编号
    double dbResolutionH;          //横向分辨率 1个像素 mm
    double dbResolutionV;          //纵向分辨率 1个像素 mm
    s_ALocationInfo sLocationParam;//定位信息
    std::vector<s_Alg_DataImg> vImageData;//图像数据
    bool bMergel;                  //'true' 拼接画面
    bool bMultlayer;               //多层参考图检测模式，单画面下多层图像模式
	bool bDustFilterMultLayer;     //两层图像擦拭前后图像 20190228
    s_ReferenceParam sRefPageData; //参考画面信息
    int nMaxNumOfDefects;          //缺陷最大处理数目,内部传递参数，外部忽略
    int nAbnormalNum;              //抛出屏幕异常的数目阈值
    std::string strModelName;      //模板名称，空时调用默认第一个模板
    s_AlgCheckInputParam():sRefPageData()
    {
        nMaxNumOfDefects=150;
        nAbnormalNum=200;
        iPageIndex=-1;
        strBatchNo="N";
        strProductNo="N";
        dbResolutionH=-1;
        dbResolutionV=-1;
        bMergel=false;
        bMultlayer=false;
		bDustFilterMultLayer = false;
        iInspId= - 1;
       strModelName="NAL";
    }
    s_AlgCheckInputParam(const s_AlgCheckInputParam& inParam)
    {
        nMaxNumOfDefects=inParam.nMaxNumOfDefects;
        nAbnormalNum=inParam.nAbnormalNum;
        iPageIndex=inParam.iPageIndex;
        strBatchNo=inParam.strBatchNo;
        strProductNo=inParam.strProductNo;
        dbResolutionH=inParam.dbResolutionH;
        dbResolutionV=inParam.dbResolutionV;
        sLocationParam=inParam.sLocationParam;
        bMergel=inParam.bMergel;
        bMultlayer=inParam.bMultlayer;
		bDustFilterMultLayer = inParam.bDustFilterMultLayer;
        if(!inParam.vImageData.empty())
        {
            vImageData.assign(inParam.vImageData.begin(), inParam.vImageData.end());
        }
        sRefPageData=inParam.sRefPageData;
        iInspId = inParam.iInspId;
         strModelName=inParam.strModelName;
    }
    s_AlgCheckInputParam& operator =(const s_AlgCheckInputParam& inParam)
    {
        nMaxNumOfDefects=inParam.nMaxNumOfDefects;
        nAbnormalNum=inParam.nAbnormalNum;
        iPageIndex=inParam.iPageIndex;
        strBatchNo=inParam.strBatchNo;
        strProductNo=inParam.strProductNo;
        dbResolutionH=inParam.dbResolutionH;
        dbResolutionV=inParam.dbResolutionV;
        sLocationParam=inParam.sLocationParam;
        bMergel=inParam.bMergel;
        bMultlayer=inParam.bMultlayer;
		bDustFilterMultLayer = inParam.bDustFilterMultLayer;
        if(!inParam.vImageData.empty())
        {
            vImageData.assign(inParam.vImageData.begin(), inParam.vImageData.end());
        }
        sRefPageData=inParam.sRefPageData;
        iInspId = inParam.iInspId;
         strModelName=inParam.strModelName;
        return *this;
    }
    void SetLocation(s_ALocationInfo& sloc)
    {
        sLocationParam=sloc;
    }
    void Reset()
    {
        nMaxNumOfDefects=150;
        nAbnormalNum=200;
        iPageIndex=-1;
        strBatchNo="N";
        strProductNo="N";
        dbResolutionH=-1;
        dbResolutionV=-1;
        bMergel=false;
        bMultlayer=false;
        bDustFilterMultLayer = false;
        iInspId = -1;
        vImageData.clear();
        sRefPageData.Reset();
        sLocationParam.Reset();
        strModelName="NAL";

    }
};
//参数建模参数表，内部维护
struct s_AlgModelList
{
    std::string strAlgParamName;//算法名称
    std::string strAlgInspName;//区域名，检测名称
    ARect rect;//区域
    bool bIsValid;//true 开启 false 禁用

    s_AlgModelList()
    {
        strAlgParamName = "NAL";
        strAlgInspName = "NAL";
        bIsValid=true;
        rect = ARect(0,0,10,10);
    }
};
#define sAlgParamNamelist std::vector<std::string>
#define sAlgNamelist std::vector<std::string>

//参数建模参数输入参数
struct s_AlgModelTranIn
{
    int iPageIndex;  //画面号
    bool bIsCreateMstate;//建模调用标志 true 建模调用  false 修改参数调用
    int	nAlgParamId;//参数id 修改参数有效
    std::vector<s_Alg_DataImg> stvImageData;//支持多层图像20190304
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH;//横向分辨率 1个像素 mm
    double dbResolutionV;//纵向分辨率 1个像素 mm
    std::string strModelName;   //新添加模型名称
    s_AlgModelTranIn() {
        iPageIndex=-1;
        nAlgParamId = -1;
        bIsCreateMstate=false;
        iImageChannel=1;
        dbResolutionH=0.0;
        dbResolutionV=0.0;
        strModelName="NAL";
    }
    s_AlgModelTranIn(const s_AlgModelTranIn& inParam)
    {
        iPageIndex=inParam.iPageIndex;
        nAlgParamId = inParam.nAlgParamId;
        bIsCreateMstate=inParam.bIsCreateMstate;
        iImageChannel=inParam.iImageChannel;
        dbResolutionH=inParam.dbResolutionH;
        dbResolutionV=inParam.dbResolutionV;
        strModelName=inParam.strModelName;
        stvImageData.assign(inParam.stvImageData.begin(),inParam.stvImageData.end());
    }
    s_AlgModelTranIn& operator =(const s_AlgModelTranIn& inParam)
    {
        iPageIndex=inParam.iPageIndex;
        nAlgParamId = inParam.nAlgParamId;
        bIsCreateMstate=inParam.bIsCreateMstate;
        iImageChannel=inParam.iImageChannel;
        dbResolutionH=inParam.dbResolutionH;
        dbResolutionV=inParam.dbResolutionV;
        strModelName=inParam.strModelName;
        stvImageData.assign(inParam.stvImageData.begin(),inParam.stvImageData.end());
        return *this;
    }

};

/*返回状态*/
enum INIT_STATE{
    STATE_OK=1,//状态OK
    STATE_CRASH=2,//状态异常，过程异常
    STATE_EMPTY=3,//配置为空
    STATE_LOADFAIL=4//加载失败配置异常
};


class ScopeGuard
{
public:
    explicit ScopeGuard(std::function<void()> onExitScope)
        : onExitScope_(onExitScope), dismissed_(false)
    { }

    ~ScopeGuard()
    {
        if(!dismissed_)
        {
            onExitScope_();
        }
    }

    void Dismiss()
    {
        dismissed_ = true;
    }

private:
    std::function<void()> onExitScope_;
    bool dismissed_;

private: // noncopyable
    ScopeGuard(ScopeGuard const&);
    ScopeGuard& operator=(ScopeGuard const&);
};
#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)
#endif // ALGDATATYPE_H
