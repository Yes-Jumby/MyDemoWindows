#ifndef ALGINSPECTOR_H
#define ALGINSPECTOR_H
#include<assert.h>
#include "AlgDataType.h"


#if defined(ALGINSPECTOR_LIBRARY)
#  define ALGINSPECTORSHARED_EXPORT __declspec(dllexport)
#else
#  define ALGINSPECTORSHARED_EXPORT __declspec(dllimport)
#endif

class CAlgPageParam;

class ALGINSPECTORSHARED_EXPORT CAlgInspector
{

public:
    CAlgInspector();

    //系统初始化
    bool Init(const s_AlgInitParam & sAlgInitParam);
    //检测函数
    bool  GCheck(const s_AlgCheckInputParam &sAlgCheckInputParam, s_AlgCheckOutputParam &sAlgCheckOutputResult);
    //参数对话框
    s_StatusModelDlg CallAlgModelDlg();

    //更新参数,根据配置文件信息决定1：加载模板 2：加载参数 ；约束：调用者保证UpdateAlgParam和GCheck串行调用
    bool UpdateAlgParam();

    //系统退出，释放资源
    bool Free();

    //获取最后的状态信息
    const s_AlgErrorInfo &GetLastStatus();
    std::string m_strPageParamPath;
    std::vector<std::string> m_vecAlgOnResg;//成功注册和配置的算法组名称列表
    std::shared_ptr<CAlgPageParam> m_AlgPageParam;
private:

   std::vector<s_AlgCheckOutputParam> m_vecAlgParamResult;//缓存每个检测算法组的结果

   std::map<std::string,std::shared_ptr<CAlgInspectorBase>> m_VecpAlgInspector;

};

#endif // ALGINSPECTOR_H
