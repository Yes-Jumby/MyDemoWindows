#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygrabdemo.h"
#include <iostream>
#include <functional>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_test = NULL;
    m_aa = new MyGrabDemo;

    std::function<void(void *)> f = bind(&MainWindow::process,this,std::placeholders::_1);
    m_aa->RegFun(f);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_aa->StartGrab();
}


void MainWindow::process(void *buffer)
{
    m_test = buffer;
}

void MainWindow::on_pushButton_2_clicked()
{
    QImage image((uchar *)m_test,7296,3000,QImage::Format_RGB32);
    QGraphicsScene *aa = new QGraphicsScene;

    image.setPixelColor(1500,1500,QColor(Qt::red));
    image.setPixelColor(1501,1501,QColor(Qt::red));
    image.setPixelColor(1502,1502,QColor(Qt::red));
    image.setPixelColor(1503,1503,QColor(Qt::red));
    image.setPixelColor(1504,1504,QColor(Qt::red));
    image.setPixelColor(1505,1505,QColor(Qt::red));
    image.setPixelColor(1506,1506,QColor(Qt::red));
    image.setPixelColor(1507,1507,QColor(Qt::red));
    image.setPixelColor(1508,1508,QColor(Qt::red));
    aa->addPixmap(QPixmap::fromImage(image));



    ui->graphicsView->setScene(aa);
    ui->label->setText(QString::number(m_aa->GetImageHeight()));
    static int i =10;
    image.save(QString::number(i++) +".bmp");

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->graphicsView->scene()->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    QImage image((uchar *)m_test,7296,3000,QImage::Format_RGB32);
    QGraphicsScene *aa = new QGraphicsScene;

    aa->addPixmap(QPixmap::fromImage(image));

    ui->graphicsView->setScene(aa);
    ui->label->setText(QString::number(m_aa->GetImageHeight()));
    static int j =20;
    image.save(QString::number(j++) +".bmp");

}

void MainWindow::on_pushButton_5_clicked()
{
    m_aa->StopGrab();
}
