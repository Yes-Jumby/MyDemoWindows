#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <stdio.h>
#include <qdebug.h>
#include <qmutex.h>

bool flag = true;
QList<int>List_Init;
QList<int>List_Show;
QList<int>List_Save;
//要定义两个信号量，一个用于表示自由空间，一个用于表示已用空间
int a =100;
QMutex Mutex;
class Init : public QThread
 {
 public:
     void run();
 };

 void Init::run()
 {
     while(flag)
     {
        Mutex.lock();
        a=a+2;
        qDebug()<<"Init"<<a;
        Mutex.unlock();
     }
 }


class Show : public QThread
 {
 public:
     void run();
 };

 void Show::run()
 {
     while(flag)
     {
         Mutex.lock();
         a=a-3;
         qDebug()<<"Show"<<a;
         Mutex.unlock();
         if(a==0)
             flag = false;
     }
 }

 class Save : public QThread
 {
 public:
     void run();
 };

 void Save::run()
 {
     while(flag)
     {

     }
 }
int main(int argc, char *argv[])
 {
     QCoreApplication app(argc, argv);
     Init aaa;
     Show bbb;
     aaa.start();
     bbb.start();
     aaa.wait();
     bbb.wait();
     return 0;
 }
