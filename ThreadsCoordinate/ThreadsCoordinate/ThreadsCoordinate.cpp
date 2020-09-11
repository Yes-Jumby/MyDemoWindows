// ThreadsCoordinate.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//--------------------------------------------------------------
//�������ߣ�Visual Studio 2015
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
[ʾ��]ʵ��һ�����̷߳�ʽ�µ�Эͬ��������

��һ���̣߳���Ե����̣߳������һ�������ʱ
����ʱ��Ϊ�����Ч�ʣ����Գ�����ö��CPU��
���ƿ��Խ����е�����ֳɶ�����֣��ַ����Ƚ�
���еĸ����߳������������������߳�Ҫ�ȴ���
�еĸ����̶߳�������ɺ󣬶������������һ��
���ܣ����ܽ�����һ����������ʱ����Ҫһ��ͬ����
���߳�Эͬ�����ࡣ
*************************************************/


//����һ�����ۻ��͵�������
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


//����һ�����������
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
    std::shared_ptr<CSumTask> tmPtr = m_queTask.front();//�õ�����ǰ��
    m_queTask.pop();//ɾ��ǰ��
    return tmPtr;
}


//Эͬ�����̹߳����࣬���𴴽�Эͬ�����̲߳������������߳�ί�е�������д���
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
    //���������߳�
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
        return false;            //��ǰ��û�ж���Ŀ��е��̴߳�������
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
        //�������
        bool bDoTask = false;
        {
            std::unique_lock<std::mutex>    muLock(m_muTask);
            while (m_queTask.empty() && !m_bStop)
            {
                m_condPop.wait(m_muTask);//�߳��������ȴ�
            }
            if (!m_queTask.empty())
            {
                TaskPtr = m_queTask.front();
                m_queTask.pop();
                m_iWorkingThread++;
                bDoTask = true;
            }

        }
        //��������
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
        m_stopVar.notify_all();//��������
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
    m_condPop.notify_all();//��������
    //�ȴ������̹߳ر�
    for (std::vector<std::shared_ptr<std::thread>>::iterator itTask = m_vecWorkers.begin(); itTask != m_vecWorkers.end(); ++itTask)
    {
        (*itTask)->join();//join(): ������ǰ�̣߳�ֱ�� *this ����ʶ���߳������ִ��
    }
    return true;
}


/**************************************
[ʾ������˵��]

ÿ����������ʾ��1+2+....+1000����
����,������2000��������������Ҫ��ÿ��
������м��㣬Ȼ�����еĽ��������͡�
���ö��߳�Эͬ��������������ÿ
�����������㣬���̵߳ȴ����н�����
�����н��������͡�
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
    DWORD dStartTime = ::GetTickCount();//����Ϊ16ms
    while (TaskMgr.Size()>0)
    {
        std::shared_ptr<CSumTask> WorkPtr = TaskMgr.PopTask();
        if (!WorkerMgr.AcceptTask(WorkPtr))//�������
        {
            //�����̴߳˿̴���æµ״̬��û�п��а�æ��,�Լ����������
            WorkPtr->DoTask();
            m_muCout.lock();
            cout << ">>>DoTask in thread [0]*******************************\n";
            m_muCout.unlock();
        }
    }
    WorkerMgr.StopAll(true);                    //�ȴ����е��������

                                                //�����н�����
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

