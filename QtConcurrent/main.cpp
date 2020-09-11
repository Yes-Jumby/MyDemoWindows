#include <QCoreApplication>
#include <QtConcurrent>
#include <iostream>
#include <fstream>
#include "SpendTime.h"
using namespace std;
void writebin(const std::string & path,int size){
    float* pbuffer = new float[size];
    std::ofstream mDataStream;
    mDataStream.open(path,std::ios::binary| std::ios::ate);
    if (!mDataStream.is_open()){
        std::cout << "write bin failed" << std::endl;
    }
    mDataStream.write(reinterpret_cast<const char*>(pbuffer), size*sizeof(float));
    mDataStream.close();
    delete []pbuffer;
}
bool func(QString name)
 {

     for(int i =0;i<1000;i++)
     {
         for(int j =0;j<1;j++)
         {
//            Sleep(1);
             qDebug() << j*1000+i;
         }
     }
     qDebug() << "Hello" << name << "from" << QThread::currentThread();
     return true;
}

int main()
{
    //QCoreApplication a(argc, argv);

    int size = 1024;
    CSpendTime SpendTime;
    SpendTime.Start();
    for(int i=0;i<100;i++)
    {
        writebin("E:\\temp\\dat\\"+std::to_string(i)+".dat",size);
    }
    cout << SpendTime.GetTimeInterval() << endl;

    SpendTime.Start();
    for(int i=0;i<100;i++)
    {
        //writebin("E:\temp\dat"+std::to_string(i),1024,pbuffer);
        QtConcurrent::run(writebin, "E:\\temp\\datc\\"+std::to_string(i)+".dat",size);
    }
    cout << SpendTime.GetTimeInterval() << endl;


    return 0;
    QFuture<bool> fut1 = QtConcurrent::run(func, QString("Thread 1"));
    QFuture<bool> fut2 = QtConcurrent::run(func, QString("Thread 2"));

    fut1.waitForFinished();
    fut2.waitForFinished();

    bool flag = fut1.result();
    flag = fut2.result();
    qDebug() << "return" ;
    return 0;
}
