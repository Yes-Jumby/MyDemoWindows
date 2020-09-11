#ifndef GARDASOFTLIGHT_H
#define GARDASOFTLIGHT_H
#include <memory>
#if defined(CGARDASOFTLIGHT_LIBRARY)
#  define CGARDASOFTLIGHTSHARED_EXPORT __declspec(dllexport)
#else
#  define CGARDASOFTLIGHTSHARED_EXPORT __declspec(dllimport)
#endif
class CGardasoftLightImpl;
class CGARDASOFTLIGHTSHARED_EXPORT CGardasoftLight
{

public:
    CGardasoftLight();
    ~CGardasoftLight();
public:
    bool Init(void* pThis);
    bool Open(short sControllerID);//0 1
    bool SendCommand(short sChannel,double iPluseWidth,double iPluseDelay,double iCurrent,double iRetriggerDelay);//A US US US
    bool Close();
    bool Save();//SaveChanges
private:
    std::shared_ptr<CGardasoftLightImpl> m_pGardasoftLightImpl;
};

#endif // GARDASOFTLIGHT_H
