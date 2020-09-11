#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <stdio.h>
#include <qdebug.h>
#include <qmutex.h>
const int DataSize=400;
const int BufferSize=10;
int buffer[BufferSize];
QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes(0);


QSemaphore SemaphoreDemo(1);
int threadnum=1;
QString str="  ";
QMutex mutex;
int index = 0;
bool flag=true;
bool stas[4]={true,false,false,false};
int threadsum = 100;

class Producer : public QThread
{
public:
    Producer();
    void run();
};

Producer::Producer()
{
}

void Producer::run()
{
   while(flag)
   {
       while(stas[0])
       {
           qDebug()<<str<<currentThreadId()<<str<<0<<"线程执行次数"<<threadnum<<endl;
           stas[0]=false;
           if(threadnum==threadsum)
           {
               flag=false;
               break;
           }
           ++threadnum;
           stas[1]=true;
       }
   }
}
class Consumer : public QThread
{
public:
    Consumer();
    void run();
};

Consumer::Consumer()
{
}

void Consumer::run()
{
    while(flag)
    {
        while(stas[1])
        {
            qDebug()<<str<<currentThreadId()<<str<<1<<"线程执行次数"<<threadnum<<endl;
            stas[1]=false;
            if(threadnum==threadsum)
            {
                flag=false;
                break;
            }
            ++threadnum;
            stas[2]=true;
        }
    }
}

class ProducerA : public QThread
{
public:
    ProducerA();
    void run();
};

ProducerA::ProducerA()
{
}

void ProducerA::run()
{
    while(flag)
    {
        while(stas[2])
        {
            qDebug()<<str<<currentThreadId()<<str<<2<<"线程执行次数"<<threadnum<<endl;
            stas[2]=false;
            if(threadnum==threadsum)
            {
                flag=false;
                break;
            }
            ++threadnum;
            stas[3]=true;
        }
    }
}
class ConsumerA : public QThread
{
public:
    ConsumerA();
    void run();
};

ConsumerA::ConsumerA()
{
}

void ConsumerA::run()
{
    while(flag)
    {
        while(stas[3])
        {
            qDebug()<<str<<currentThreadId()<<str<<3<<"线程执行次数"<<threadnum<<endl;
            stas[3]=false;
            if(threadnum==threadsum)
            {
                flag=false;
                break;
            }
            ++threadnum;
            stas[0]=true;
        }
    }
}

//互斥量的使用
class ConsumerB : public QThread
{
public:
    ConsumerB();
    void run();
};

ConsumerB::ConsumerB()
{
}

void ConsumerB::run()
{
    while(flag)
    {
        mutex.lock();
        if(threadnum>threadsum)
        {
            break;
        }
        qDebug()<<"线程ID:"<<currentThreadId()<<str<<"线程执行次数:"<<threadnum<<endl;
        if(threadnum==threadsum)
        {
            flag=false;
        }
        ++threadnum;
        mutex.unlock();
    }
}

//信号量的使用
class Semaphore : public QThread
{
public:
    Semaphore();
    void run();
};

Semaphore::Semaphore()
{
}

void Semaphore::run()
{
    while(flag)
    {
        SemaphoreDemo.acquire();//获取一个信号量
        if(threadnum>threadsum)
        {
            break;
        }
        qDebug()<<"线程ID:"<<currentThreadId()<<str<<"线程执行次数:"<<threadnum<<endl;
        if(threadnum==threadsum)
        {
            flag=false;
        }
        ++threadnum;
        SemaphoreDemo.release();//释放一个信号量
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//线程循环执行，A线程输出0，B线程输出1，C线程输出2,D线程输出3
    //bool型变量
//    Producer producer;
//    Consumer consumer;
//    ProducerA producerA;
//    ConsumerA consumerA;

//    producer.start();
//    producerA.start();
//    consumer.start();
//    consumerA.start();

//    producer.wait();
//    consumer.wait();
//    producerA.wait();
    consumerA.wait();
    //互斥量
    ConsumerB consumerA;
    ConsumerB consumerB;
    ConsumerB consumerC;
    ConsumerB consumerD;
    ConsumerB consumerE;

    consumerA.start();
    consumerB.start();
    consumerC.start();
    consumerD.start();
    consumerE.start();
//    //信号量
//    Semaphore SemaphoreA;
//    Semaphore SemaphoreB;
//    Semaphore SemaphoreC;
//    Semaphore SemaphoreD;
//    SemaphoreA.start();
//    SemaphoreB.start();
//    SemaphoreC.start();
//    SemaphoreD.start();
    return a.exec();
}
