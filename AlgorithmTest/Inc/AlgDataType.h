#ifndef ALGDATATYPE_H
#define ALGDATATYPE_H
#pragma execution_character_set("utf-8")

#include <string>
#include <vector>
#include <windows.h>
#include <map>
#include <memory>

/******************************************基本数据结构*******************************/
#define FreePt(Pt) if(Pt!=nullptr){delete Pt;Pt=nullptr;}else{Pt=nullptr;}
#define MAX_DEFECTNUM 200
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
    AVariant(const int& val){
        pnVal=new int(val);
		pstrVal = nullptr;
		pfVal = nullptr;
        nType=INT;
    }
    AVariant(const float &val){
        pfVal=new float(val);
		pnVal = nullptr;
		pstrVal = nullptr;
        nType=FLOAT;
    }
    AVariant(const std::string& val){
        pstrVal=new std::string(val);
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

    AVariant& operator=(const int& val){
        if(pnVal==nullptr)
        {
            pnVal=new int(val);
        }
        else
        {
            *pnVal=val;
        }
        nType=INT;
        FreePt(pstrVal);
        FreePt(pfVal);
        return *this;
    }
    AVariant& operator=(const float& val){
        if(pfVal==nullptr)
        {
            pfVal=new float(val);
        }
        else
        {
            *pfVal=val;
        }
        nType=FLOAT;
        FreePt(pstrVal);
        FreePt(pnVal);
        return *this;
    }
    AVariant& operator=(const std::string& val){
        if(pstrVal==nullptr)
        {
            pstrVal=new std::string(val);
        }
        else
        {
            *pstrVal=val;
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
    }
    float GetFValue()
    {
        if(nType==FLOAT&&pfVal!= nullptr)
        {
            return *pfVal;
        }
    }
    std::string GetStrValue()
    {
        if(nType==STRING&&pstrVal!= nullptr)
        {
            return *pstrVal;
        }
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

class ARect
{
public:
    int left;
    int top;
    int right;
    int bottom;
    ARect(int l,int t,int w,int h)
    {
        left=l;
        right=l+w-1;
        top=t;
        bottom=t+h-1;
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
    ~ARect()
    {}
};

class CAlgInspectorBase;
class CAlgInspParamBase;
//状态结果
#ifndef ALG_RESULT_INFO
#define ALG_RESULT_INFO
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
};
struct s_StatusModelDlg
{
    int nErorType; //返回函数状态 0:正常 1:异常
    int nResult;   //0：未发生更改 1：更改参数或者模板
};
#endif

//初始化结构体
struct s_AlgInitParam
{
    int iPageIndex;  //画面号
    int iImageWidth; //图像宽
    int iImageHeight;//图像高
    int iImageChannel; //图像位数 1：灰度  3：RGB 4:RGBA
    double dbResolutionH;//横向分辨率 1个像素 mm
    double dbResolutionV;//纵向分辨率 1个像素 mm
    std::string strParamPath; //参数路径 例如 D:/Bin/AlgConfig
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

//对象注册函数
typedef std::shared_ptr<CAlgInspectorBase> (*CreateAlgFunction)();
typedef std::map<std::string, CreateAlgFunction> CreateAlgMap;
static CreateAlgMap g_CreateAlgMap;

//对象注册用
#define RegisterAlg(AlgName) \
    static std::shared_ptr<CAlgInspectorBase> Create##AlgName()\
    {\
     return std::make_shared<AlgName>();\
    }\
    class __Registerer_##AlgName { \
     public: /* NOLINT */ \
      __Registerer_##AlgName() { \
        g_CreateAlgMap[#AlgName] = &Create##AlgName; \
      } \
    };\
  static __Registerer_##AlgName Registerer##AlgName;


class CAlgParamBase;
class CAlgInspectorBase
{
public:
    CAlgInspectorBase() {}

    virtual ~CAlgInspectorBase(){}
    //系统初始化
    virtual bool Init(const s_AlgInitParam & sAlgInitParam)=0;

    //检测函数
    virtual bool  GCheck(const s_AlgCheckInputParam &sAlgCheckInputParam, s_AlgCheckOutputParam &sAlgCheckOutputResult,const CAlgParamBase* pAlgParam) = 0;

    //参数对话框
    virtual s_StatusModelDlg CallAlgModelDlg() = 0;

    //更新参数,根据配置文件信息决定1：加载模板 2：加载参数 ；约束：调用者保证UpdateAlgParam和GCheck串行调用
    virtual bool UpdateAlgParam() = 0;

    //系统退出，释放资源
    virtual bool Free() = 0;

    //获取最后的状态信息
    virtual const s_AlgErrorInfo &GetLastStatus() = 0;
};



#endif // ALGDATATYPE_H
