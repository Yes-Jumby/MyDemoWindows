#ifndef DLLPROJECTHEAD_H
#define DLLPROJECTHEAD_H
class DllProjectHead
{
public:
    DllProjectHead()
    {}
    ~DllProjectHead()
    {}
public:
    virtual int MyCheck(int value) = 0;
//    virtual void MyDestroy(void) = 0;
};

#endif // DLLPROJECTHEAD_H
