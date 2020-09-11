#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <stdio.h>
#include <qdebug.h>
#include <qmutex.h>
#include <set>
QSemaphore Page1;
QSemaphore Page2;
QSemaphore Page3;

//检测输出
struct s_AlgCheckOutputParam
{
   int iIndex;
   int iGay;
   int iShort;
};
//要定义两个信号量，一个用于表示自由空间，一个用于表示已用空间

class MyThread : public QThread
 {
public:
    MyThread(const QString &myName);
    void run();
    void SetStart();
    void SetStop();
    void Attach(MyThread* pObs);   //注册观察者
    void Notify(); //若状态变化，则遍历观察者，逐个通知更新
    const QSemaphore &getSemaphore();
    void SetWait();
    void SetResult(const s_AlgCheckOutputParam &myResult);
 private:
     void AlgTest();
     void AlgPre();
     bool isStart = false;
     bool flag = true;
     int temp = 0;
     QString m_strName;
     std::set<MyThread*> m_setObs;
     QSemaphore MySemaphore;
     s_AlgCheckOutputParam myResult;
     bool IsNeedWait = false;
 };
const QSemaphore &MyThread::getSemaphore()
{
    return MySemaphore;
}

void MyThread::SetWait()
{
    IsNeedWait = true;
}

void MyThread::SetResult(const s_AlgCheckOutputParam &myResult)
{
    MyThread::myResult = myResult;
}
MyThread::MyThread(const QString &myName)
{
    m_strName = myName;
}
void MyThread::Attach(MyThread* pObs)
{
    if (pObs==nullptr)
        return;
    pObs->SetWait();
    m_setObs.insert(pObs);
}
void MyThread::Notify()
 {
    if(m_setObs.size()==0)
        return ;
    std::set<MyThread*>::iterator itr = m_setObs.begin();
    for (; itr != m_setObs.end(); itr++)
    {
        (*itr)->SetResult(myResult);
        (*itr)->SetStart();
    }
}

 void MyThread::run()
 {  
     while(flag)
     {
         while(isStart)
         {
             MySemaphore.acquire();
             if(!IsNeedWait)
             {
                 myResult.iGay = 1;
                 myResult.iIndex =1;
                 myResult.iShort = 1;
                 AlgPre();
                 Notify();
             }
             AlgTest();
             SetStop();
         }
     }
 }
 void MyThread::SetStart()
 {
     qDebug("%s-----Start",qPrintable(m_strName));
     isStart = true;
     MySemaphore.release();
 }
 void MyThread::SetStop()
 {
     isStart = false;
     flag = false;
     qDebug("AlgPre:%s-----%s-----%d-----%d-----%d",qPrintable(m_strName),"Quit",myResult.iGay,myResult.iIndex,myResult.iShort);
 }
 void MyThread::AlgTest()
 {
     for(int i =0;i<10000;i++)
     {
         for(int j =0;j<10000;j++)
             temp = i * j ;
     }
     qDebug("%s-----%s",qPrintable(m_strName),"Test Finished");
 }
 void MyThread::AlgPre()
 {
     for(int i =0;i<1000;i++)
     {
         for(int j =0;j<1000;j++)
             temp = i * j ;
     }
     qDebug("%s-----%s",qPrintable(m_strName),"Pre Finished");
 }
int main(int argc, char *argv[])
 {
     QCoreApplication app(argc, argv);
     //指针形式
     qDebug("-----%s","Thread Stack");
     MyThread* pThread1 = new MyThread("Page1");
     MyThread* pThread2 = new MyThread("Page2");
     MyThread* pThread3 = new MyThread("Page3");
     pThread1->start();
     pThread2->start();
     pThread3->start();
     pThread1->Attach(pThread2);
     pThread1->Attach(pThread3);
     pThread1->SetStart();


     pThread1->wait();
     pThread2->wait();
     pThread3->wait();
     //对象形式
     qDebug("-----%s","Thread Heap");
     MyThread Thread1("Page1");
     MyThread Thread2("Page2");
     MyThread Thread3("Page3");
     Thread1.start();
     Thread2.start();
     Thread3.start();
     Thread1.Attach(&Thread2);
     Thread1.Attach(&Thread3);
     Thread1.SetStart();


     Thread1.wait();
     Thread2.wait();
     Thread3.wait();
     return 0;
 }
