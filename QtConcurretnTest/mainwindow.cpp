#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>
#include <iostream>
#include <fstream>
#include "SpendTime.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("1024");
}

MainWindow::~MainWindow()
{
    delete ui;
}
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
void MainWindow::on_pushButton_clicked()
{
    int size = ui->lineEdit->text().toInt();
    CSpendTime SpendTime;
    SpendTime.Start();
    for(int i=0;i<3;i++)
    {
        writebin("E:\\temp\\dat\\"+std::to_string(i)+".dat",size);
    }
    cout << "for "<<SpendTime.GetTimeInterval() << endl;
    QFuture<void> fut1[3];
    SpendTime.Start();
    for(int i=0;i<3;i++)
    {
        //writebin("E:\temp\dat"+std::to_string(i),1024,pbuffer);
        fut1[i] = QtConcurrent::run(writebin, "E:\\temp\\datc\\"+std::to_string(i)+".dat",size);
    }
    fut1[0].waitForFinished();
    fut1[1].waitForFinished();
    fut1[2].waitForFinished();
    cout << "con "<<SpendTime.GetTimeInterval() << endl;
}
