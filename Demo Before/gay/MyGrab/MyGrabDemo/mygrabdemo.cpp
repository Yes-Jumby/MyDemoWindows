#include "mygrabdemo.h"
#include <QTimer>
#include <QDebug>
#include <string>
#include <QImage>
#include <QPixmap>
#include <QLabel>
MyGrabDemo::MyGrabDemo()
{
    m_Acq = NULL;
    m_Buffers = NULL;
    m_Xfer = NULL;
    m_isGrabbing = false;

    m_isCameraDetected = false;

//    char *acqServerName = new char[CORSERVER_MAX_STRLEN];
//    std::string fileName = "../Build/C_3DPixA_Line_Default.ccf";
//    char *acqConfigFileName = new char[MAX_CONFIG_PATH];
//    strcpy(acqConfigFileName, fileName.c_str());//string 赋值给char *

//    FindServerNmae(acqServerName);


//    SapLocation loc(acqServerName, 1);
//    m_Acq = new SapAcquisition(loc, acqConfigFileName);
//    m_Buffers = new SapBuffer(1, m_Acq);
//    m_Xfer = new SapAcqToBuf(m_Acq, m_Buffers,XferCallback,this);
//    m_Acq->Create();
//    m_Buffers->Create();
//    m_Xfer->Create();
}


MyGrabDemo::~MyGrabDemo()
{
    m_Acq->Destroy();
    m_Buffers->Destroy();
    m_Xfer->Destroy();

    delete m_Acq;
    delete m_Buffers;
    delete m_Xfer;
}
bool MyGrabDemo::InitServerParam(ServerInitParam param)
{

    SapLocation loc(param.acqServerName, 1);
    m_Acq = new SapAcquisition(loc, param.configFileName);
    m_Buffers = new SapBuffer(1, m_Acq);
    m_Xfer = new SapAcqToBuf(m_Acq, m_Buffers, XferCallback, this);
    if(!CreatObject())
    {
        return false;
    }
    return true;
}

bool MyGrabDemo::CreatObject()
{
    //creat acquisition object
    if(m_Acq && !(m_Acq->Create()))
    {
        //destory object
        DestoryObject();
        return false;
    }
    //creat buffer object
    if(m_Buffers && !(m_Buffers->Create()))
    {
        //destory object
        DestoryObject();
        return false;
    }
    //creat transfer object
    if(m_Xfer && !(m_Xfer->Create()))
    {
        //destory object
        DestoryObject();
        return false;
    }
}

bool MyGrabDemo::DestoryObject()
{
    // Destroy transfer object
    if (m_Xfer && *m_Xfer) m_Xfer->Destroy();

    // Destroy buffer object
    if (m_Buffers && *m_Buffers) m_Buffers->Destroy();

    // Destroy acquisition object
    if (m_Acq && *m_Acq) m_Acq->Destroy();

    return true;
}
bool MyGrabDemo::FindServerNmae(char *acqServerName)
{
    int serverCount = SapManager::GetServerCount();
    for (int index = 0; index < serverCount; index++)
    {
        if(SapManager::GetResourceCount(index, SapManager::ResourceAcq) != 0)
        {
            char serverName[CORSERVER_MAX_STRLEN];
            SapManager::GetServerName(index, acqServerName, sizeof(serverName));
        }
    }

    return true;
}
bool MyGrabDemo::StartGrab()
{
    if(!(m_isGrabbing))
    {
        m_Xfer->Grab();
        m_isGrabbing = true;
    }
    return true;
}


bool MyGrabDemo::StopGrab()
{
    if(m_isGrabbing)
    {
        if(m_Xfer->Freeze())
        {
            m_isGrabbing = false;
        }
        else
        {
            m_Xfer->Abort();
            m_isGrabbing = false;
        }
    }
    return true;
}
bool MyGrabDemo::SnapShot()
{
    if(!(m_isGrabbing))
    {
       m_Xfer->Snap(1);
       StopGrab();
    }
    return true;
}

void MyGrabDemo::RegFun(std::function<void(void *)>  f)
{
    m_pFun = f;
}

bool MyGrabDemo::SetTriggerMode(TriggerMode mode)
{
    switch (mode) {
    case SOFTWARE:
        m_Acq->SetParameter(CORACQ_PRM_EXT_FRAME_TRIGGER_ENABLE,false);
        break;
    case EXTERNAL:
        m_Acq->SetParameter(CORACQ_PRM_EXT_FRAME_TRIGGER_ENABLE,true);
        break;
    default:
        break;
    }

    return true;
}
int MyGrabDemo::GetImageHeight()
{
   return m_imageHeight;
}

int MyGrabDemo::GetImageWidth()
{
    return m_imageWidth;
}
//回调函数
void MyGrabDemo::XferCallback(SapXferCallbackInfo *pInfo)
{
    MyGrabDemo *pImg = (MyGrabDemo *)pInfo->GetContext();

    pImg->m_imageHeight = pImg->m_Buffers->GetHeight();
    pImg->m_imageWidth = pImg->m_Buffers->GetWidth();

    void * address = NULL;

    pImg->m_Buffers->GetAddress(&address);
    pImg->m_pFun(address);
}
