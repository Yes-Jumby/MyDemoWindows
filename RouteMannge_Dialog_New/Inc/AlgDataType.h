#ifndef ALGDATATYPE_H
#define ALGDATATYPE_H
#pragma execution_character_set("utf-8")

#include <string>
#include <vector>
#include <windows.h>
#include <map>
#include <memory>


/******************************************基本数据结构*******************************/

#define MAX_DEFECTNUM 200 //最大处理缺陷数目

#define FreePt(Pt) if(Pt!=nullptr){delete Pt;Pt=nullptr;}else{Pt=nullptr;}
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
    ~ARect()
    {}
};


//参数结构
class s_Params
{
public:
    std::string strParamName; //参数类型
    std::string strParamInfo; //参数说明
    std::string strParamEnName; //参数英文字段
    AVariant qvParamValue;    //参数值
    // AVariant qvDefaltParamValue;    //默认参数值
    AVariant qvParamMaxValue;    //最大参数值
    AVariant qvParamMinValue;    //最小参数值
    std::vector<std::string> vecComValue;//调用combox方式 从0开始编号
    s_Params(const int& qvInValue,int& qvMaxValue, int qvmMinValue,const std::string& strName="NAL",const std::string& strInfo="NAL", const std::string& strEnName="NAL",std::vector<std::string> *vecValue=NULL)
    {
        qvParamValue=qvInValue;
        qvParamMaxValue=qvMaxValue;
        qvParamMinValue=qvmMinValue;
        strParamEnName=strEnName;
        strParamName=strName;
        strParamInfo=strInfo;
        if(vecValue!=NULL&&!vecValue->empty())
        {
            vecComValue.clear();
            vecComValue.assign(vecValue->begin(), vecValue->end());//拷贝数据
        }
    }
    s_Params(const float& qvInValue,const float& qvMaxValue, const float& qvmMinValue,const std::string& strName="NAL",const std::string& strInfo="NAL", const std::string& strEnName="NAL",std::vector<std::string> *vecValue=NULL)
    {
        qvParamValue=qvInValue;
        qvParamMaxValue=qvMaxValue;
        qvParamMinValue=qvmMinValue;
        strParamEnName=strEnName;
        strParamName=strName;
        strParamInfo=strInfo;
        if(vecValue!=NULL&&!vecValue->empty())
        {
            vecComValue.clear();
            vecComValue.assign(vecValue->begin(), vecValue->end());//拷贝数据
        }
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
    int iPageIndex;  //画面号
    int iImageWidth; //图像宽
    int iImageHeight;//图像高
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH;//横向分辨率 1个像素 mm
    double dbResolutionV;//纵向分辨率 1个像素 mm
    std::string strParamPath; //默认参数路径 例如 D:/Bin/AlgConfig
    std::string strModelPath; //模板路径 例如D:/User/Model/苹果x
    std::string strLogPath;   //日志路径 例如 D:/User/Log/AlgLog
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
        strLogPath="";
    }
};
//缺陷类型索引表常量
const std::vector<std::string> vecDefectList={"良品","划伤","灰尘","脏污","崩边","白点","异物","雨滴","缺失"};
//检出缺陷信息 该部分信息为缺陷结果
struct s_AlgDefectInfo
{
    int nId;  //画面号
    int iDefectID;//缺陷类型编号 0,1,2,3···详细见索引vecDefectList
    ARect nRect; //缺陷位置
    std::string strDefectName;
    float fArea;//缺陷面积
    float fLength;//缺陷长度
    float fWidth;//缺陷长度
    float fConstract;//缺陷长度
    float fCirRat;//缺陷长度
    float fRectRat;//缺陷长度
    float fJnd;//缺陷长度
    float fEnergy;//缺陷能量
    s_AlgDefectInfo()
    {
        Reset();
    }
    void Reset()
    {
        nId=-1;
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
//检出结果标志
enum CHECK_RESULT
{
    RESULT_LIGHT,//亮度异常
    RESULT_LOCATION_ERR,//定位异常
    RESULT_PAGE_ERR,//画面异常
    RESULT_OK,//良品
    REULT_NG,//NG品
    REULT_DUSTWARNING//灰尘过多
};
//检测输出
struct s_AlgCheckOutputParam
{
    //通用结果参数
    int iPageIndex;  //画面号
    int iImageWidth; //图像宽
    int iImageHeight;//图像高
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    CHECK_RESULT eResultFlag;                //检出结果标志

    int ibufferSize;
    BYTE *pbuffer;           //图像Buffer 内部创建内存空间 注意释放调用Reset()
    //专用结果
    std::vector<s_AlgDefectInfo> vecDefInfo; //图像Buffer，该部分信息为缺陷结果列表显示
    s_AlgCheckOutputParam()
    {
        pbuffer = nullptr;
        Reset();
    }
    void Reset()
    {
        iPageIndex=-1;
        iImageWidth=16000;
        iImageHeight=20000;
        iImageChannel=1;
        eResultFlag=RESULT_OK;
        vecDefInfo.clear();
        ibufferSize = 0;
        if(pbuffer != nullptr)
        {
            delete []pbuffer;
            pbuffer = nullptr;
        }

    }
};
//参考参数
struct s_AlgCheckInputParam;
struct s_ReferenceParam
{
    bool bNeedRefParam;
    s_AlgCheckInputParam  *pInputParam;
    s_AlgCheckOutputParam *pOutParam;
};
//完整图像数据
struct s_Alg_DataImg
{
    std::vector<BYTE *> DATA;//传递指针,支持多张图
    int nPixWidth;
    int nWidth;
    int nHeight;
    int nChannel;
    ARect rect;//有效roi区域
    s_Alg_DataImg()
    {
        nPixWidth = 0;
        nWidth = 0;
        nHeight = 0;
        nChannel=1;
        rect = ARect(0, 0, 0, 0);
    }
	s_Alg_DataImg(const s_Alg_DataImg& inData)
	{
		nHeight = inData.nHeight;
		nPixWidth = inData.nPixWidth;
		nWidth = inData.nWidth;
		rect = inData.rect;
		nChannel = inData.nChannel;
		DATA.clear();
		if (!inData.DATA.empty())
		{
			DATA.assign(inData.DATA.begin(), inData.DATA.end());
		}
	}
    s_Alg_DataImg(std::vector<BYTE *>& InDATA,int nwidth,int nheight,int nchannel,int npixwidth)
    {
        if(InDATA.empty())
        {
            return;
        }
        DATA.assign(InDATA.begin(), InDATA.end());
        nPixWidth = npixwidth;
        nWidth = nwidth;
        nHeight = nheight;
        nChannel=nchannel;
        rect = ARect(0, 0, 0, 0);
    }
    s_Alg_DataImg(BYTE * InDATA,int nwidth,int nheight,int nchannel,int npixwidth)
    {
        DATA.push_back(InDATA);
        nPixWidth = npixwidth;
        nWidth = nwidth;
        nHeight = nheight;
        nChannel=nchannel;
        rect = ARect(0, 0, 0, 0);
    }
    void setRoi(ARect &rt)
    {
        rect = rt;
    }
    void ClearRoi()
    {
        rect = ARect(0, 0, 0, 0);
    }
    s_Alg_DataImg& operator=(const s_Alg_DataImg& inData)
    {
        nHeight=inData.nHeight;
        nPixWidth=inData.nPixWidth;
        nWidth=inData.nWidth;
        rect=inData.rect;
        nChannel=inData.nChannel;
        DATA.clear();
        if (!inData.DATA.empty())
        {
            DATA.assign(inData.DATA.begin(), inData.DATA.end());
        }
        return *this;
    }
};
//检测输入
struct s_AlgCheckInputParam
{
    int iPageIndex;  //画面号
    std::string strBatchNo;   //当前批号
    std::string strProductNo; //产品编号
    int iImageWidth; //图像宽
    int iImageHeight;//图像高
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH;//横向分辨率 1个像素 mm
    double dbResolutionV;//纵向分辨率 1个像素 mm
    std::vector<BYTE *>vecPbuffer; //图像Buffer
    s_ReferenceParam sReferParam;
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
    s_Alg_DataImg stImageData;
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH;//横向分辨率 1个像素 mm
    double dbResolutionV;//纵向分辨率 1个像素 mm

    s_AlgModelTranIn():stImageData() {
        iPageIndex=-1;
        nAlgParamId = -1;
        bIsCreateMstate=false;
        iImageChannel=1;
        dbResolutionH=0.0;
        dbResolutionV=0.0;
    }
};

/*返回状态*/
enum INIT_STATE{
    STATE_OK=1,//状态OK
    STATE_CRASH=2,//状态异常，过程异常
    STATE_EMPTY=3,//配置为空
    STATE_LOADFAIL=4//加载失败配置异常
};

#endif // ALGDATATYPE_H
