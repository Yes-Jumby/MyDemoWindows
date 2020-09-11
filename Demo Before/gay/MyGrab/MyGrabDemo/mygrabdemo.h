/*************用于相机和电脑通过采集卡相连的模式***************/

#ifndef MYGRABDEMO_H
#define MYGRABDEMO_H

#if defined(MYGRABDEMO_LIBRARY)
#  define MYGRABDEMOSHARED_EXPORT __declspec(dllexport)
#else
#  define MYGRABDEMOSHARED_EXPORT __declspec(dllimport)
#endif

#include "SapClassBasic.h"
#include <string>
#include "conio.h"
#include "functional"
#include "commonparam.h"
#define MAX_CONFIG_FILES 36 //最大可选配置文件数，共36个，依次用0-9和26个小写字母编号
#define STRING_LENGTH 256
#define MAX_CONFIG_PATH 260


static char conFigFileNames[MAX_CONFIG_FILES][MAX_CONFIG_PATH];
enum TriggerMode
{
    SOFTWARE = 0,
    EXTERNAL
};

class MYGRABDEMOSHARED_EXPORT MyGrabDemo
{

public:

    MyGrabDemo();
    ~MyGrabDemo();
    //连续采集
    bool StartGrab();
    bool InitServerParam(ServerInitParam param);

    //停止采集
    bool StopGrab();
    //单帧采集
    bool SnapShot();
    //设置触发模式
    bool SetTriggerMode(TriggerMode mode);
    //获取图像的宽
    int GetImageWidth();
    //获取图像的高
    int GetImageHeight();
    //注册回调函数
    void RegFun(std::function<void(void *)>  f);
    bool DestoryObject();
    //回调函数
    static void XferCallback(SapXferCallbackInfo *pInfo);


private:
    SapAcquisition  *m_Acq;        //此处指控制相机的采集卡；采集卡作为一个中间传输节点，实现了相机和Buffer之间的传输
    SapBuffer       *m_Buffers;    //动态资源，即buffer，作为缓冲区
    SapTransfer     *m_Xfer;       //传输类，控制着数据从源节点到目标节点的传输过程
    int             m_imageWidth;
    int             m_imageHeight;
    std::function<void(void *)>          m_pFun;
    bool             m_isCameraDetected;    //检测到即为true
    bool             m_isGrabbing;      //标识是否正在抓取图像，true为正在抓，false为没有抓取
    bool FindServerNmae(char *acqServerName);
    bool CreatObject();

};

#endif // MYGRABDEMO_H
