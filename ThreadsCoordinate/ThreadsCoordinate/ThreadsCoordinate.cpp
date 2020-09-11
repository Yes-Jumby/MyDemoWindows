// ThreadsCoordinate.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//--------------------------------------------------------------
//开发工具：Visual Studio 2015
//---------------------------------------------------------------
//C++
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
std::mutex m_muCout;
using namespace std;

//windows
#include <windows.h>


/************************************************
[示例]实现一个多线程方式下的协同工作程序

当一个线程（相对的主线程）在完成一个任务的时
候，有时候为了提高效率，可以充分利用多核CPU的
优势可以将手中的任务分成多个部分，分发给比较
空闲的辅助线程来帮助处理，并且主线程要等待所
有的辅助线程都处理完成后，对所有任务进行一次
汇总，才能进行下一步操作，此时就需要一个同步的
多线程协同工作类。
*************************************************/


//定义一个求累积和的任务类
class CSumTask
{
public:
    CSumTask(double dStart, double dEnd);
    ~CSumTask();
    double DoTask();
    double GetResult();
private:
    double m_dMin;
    double m_dMax;
    double m_dResult;
};

CSumTask::CSumTask(double dStart, double dEnd) :m_dMin(dStart), m_dMax(dEnd), m_dResult(0.0)
{

}
CSumTask::~CSumTask()
{

}
double CSumTask::DoTask()
{

    for (double dNum = m_dMin; dNum <= m_dMax; ++dNum)
    {
        m_dResult += dNum;
    }
    return m_dResult;
}

double CSumTask::GetResult()
{
    return m_dResult;
}


//定义一个任务管理者
class CTaskManager
{
public:
    CTaskManager();
    ~CTaskManager();
    size_t Size();
    void AddTask(const std::shared_ptr<CSumTask> TaskPtr);
    std::shared_ptr<CSumTask> PopTask();
protected:
    std::queue<std::shared_ptr<CSumTask>> m_queTask;
};

CTaskManager::CTaskManager()
{

}

CTaskManager::~CTaskManager()
{

}

size_t CTaskManager::Size()
{
    return m_queTask.size();
}

void CTaskManager::AddTask(const std::shared_ptr<CSumTask> TaskPtr)
{
    m_queTask.push(std::move(TaskPtr));
}

std::shared_ptr<CSumTask> CTaskManager::PopTask()
{
    std::shared_ptr<CSumTask> tmPtr = m_queTask.front();//得到队列前面
    m_queTask.pop();//删除前面
    return tmPtr;
}


//协同工作线程管理类，负责创建协同工作线程并接受来自主线程委托的任务进行处理
class CWorkThreadManager
{
public:
    CWorkThreadManager(unsigned int uiThreadSum);
    ~CWorkThreadManager();
    bool AcceptTask(std::shared_ptr<CSumTask> TaskPtr);
    bool StopAll(bool bStop);
    unsigned int ThreadNum();
protected:
    std::queue<std::shared_ptr<CSumTask>> m_queTask;
    std::mutex m_muTask;
    int m_iWorkingThread;
    int m_iWorkThreadSum;
    std::vector<std::shared_ptr<std::thread>> m_vecWorkers;

    void WorkThread(int iWorkerID);
    bool m_bStop;
    std::condition_variable_any m_condPop;
    std::condition_variable_any m_stopVar;

};

CWorkThreadManager::~CWorkThreadManager()
{

}
unsigned int CWorkThreadManager::ThreadNum()
{
    return m_iWorkThreadSum;
}

CWorkThreadManager::CWorkThreadManager(unsigned int uiThreadSum) :m_bStop(false), m_iWorkingThread(0), m_iWorkThreadSum(uiThreadSum)
{
    //创建工作线程
    for (int i = 0; i < m_iWorkThreadSum; ++i)
    {
        std::shared_ptr<std::thread> WorkPtr(new std::thread(&CWorkThreadManager::WorkThread, this, i + 1));
        m_vecWorkers.push_back(WorkPtr);
    }

}

bool CWorkThreadManager::AcceptTask(std::shared_ptr<CSumTask> TaskPtr)
{
    std::unique_lock<std::mutex>    muLock(m_muTask);
    if (m_iWorkingThread >= m_iWorkThreadSum)
    {
        return false;            //当前已没有多余的空闲的线程处理任务
    }
    m_queTask.push(TaskPtr);
    m_condPop.notify_all();
    return true;
}

void CWorkThreadManager::WorkThread(int iWorkerID)
{
    while (!m_bStop)
    {
        std::shared_ptr<CSumTask> TaskPtr;
        //添加任务
        bool bDoTask = false;
        {
            std::unique_lock<std::mutex>    muLock(m_muTask);
            while (m_queTask.empty() && !m_bStop)
            {
                m_condPop.wait(m_muTask);//线程阻塞，等待
            }
            if (!m_queTask.empty())
            {
                TaskPtr = m_queTask.front();
                m_queTask.pop();
                m_iWorkingThread++;
                bDoTask = true;
            }

        }
        //处理任务
        if (bDoTask)
        {
            TaskPtr->DoTask();
            {
                std::unique_lock<std::mutex>    muLock(m_muTask);
                m_iWorkingThread--;
                m_muCout.lock();
                cout << ">>>DoTask in thread [" << iWorkerID << "]\n";
                m_muCout.unlock();
            }
        }
        m_stopVar.notify_all();//唤醒所有
    }
}

bool CWorkThreadManager::StopAll(bool bStop)
{
    {
        std::unique_lock<std::mutex>    muLock(m_muTask);
        while (m_queTask.size()>0 || m_iWorkingThread>0)
        {
            m_stopVar.wait(m_muTask);
            cout << ">>>Waiting finish....\n";
        }
        cout << ">>>All task finished!\n";

    }

    m_bStop = true;
    m_condPop.notify_all();//唤醒所有
    //等待所有线程关闭
    for (std::vector<std::shared_ptr<std::thread>>::iterator itTask = m_vecWorkers.begin(); itTask != m_vecWorkers.end(); ++itTask)
    {
        (*itTask)->join();//join(): 阻塞当前线程，直至 *this 所标识的线程完成其执行
    }
    return true;
}


/**************************************
[示例程序说明]

每个任务对象表示求1+2+....+1000的累
积和,现在有2000个这样的任务，需要将每个
任务进行计算，然后将所有的结果汇总求和。
利用多线程协同工作类对象辅助完成每
个任务结果计算，主线程等待所有结果完成
后将所有结果汇总求和。
****************************************/


int main(int arg, char *arv[])
{
    int iTaskSum = 2000;
    double iSumStart = 1.0;
    double iSumEnd = 10000.0;

    std::cout.sync_with_stdio(true);
    CTaskManager TaskMgr;
    CWorkThreadManager WorkerMgr(5);
    std::vector<std::shared_ptr<CSumTask>> vecResultTask;
    
    for (int i = 0; i < iTaskSum; ++i)
    {
        std::shared_ptr<CSumTask> TaskPtr(new CSumTask(iSumStart, iSumEnd));
        TaskMgr.AddTask(TaskPtr);
        vecResultTask.push_back(TaskPtr);
    }

    //
    DWORD dStartTime = ::GetTickCount();//精度为16ms
    while (TaskMgr.Size()>0)
    {
        std::shared_ptr<CSumTask> WorkPtr = TaskMgr.PopTask();
        if (!WorkerMgr.AcceptTask(WorkPtr))//添加任务
        {
            //辅助线程此刻处于忙碌状态（没有空闲帮忙）,自己处理该任务
            WorkPtr->DoTask();
            m_muCout.lock();
            cout << ">>>DoTask in thread [0]*******************************\n";
            m_muCout.unlock();
        }
    }
    WorkerMgr.StopAll(true);                    //等待所有的任务完成

                                                //对所有结果求和
    double dSumResult = 0.0;
    for (std::vector<std::shared_ptr<CSumTask>>::iterator itTask = vecResultTask.begin(); itTask != vecResultTask.end(); ++itTask)
    {
        dSumResult += (*itTask)->GetResult();
    }

    DWORD dEndTime = ::GetTickCount();
    cout << "\n[Status]" << endl;
    cout << "\tEvery task result:" << vecResultTask[0]->GetResult() << endl;
    cout << "\tTask num:" << vecResultTask.size() << endl;
    cout << "\tAll result sum:" << dSumResult;
    cout << "\tCast to int,result:" << static_cast<long long>(dSumResult) << endl;
    cout << "\tWorkthread num:" << WorkerMgr.ThreadNum() << endl;
    cout << "\tTime of used:" << dEndTime - dStartTime << " ms" << endl;
    getchar();
    return 0;
}

