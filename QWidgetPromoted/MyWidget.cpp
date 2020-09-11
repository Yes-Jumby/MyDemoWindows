#include "MyWidget.h"
#include "ui_MyWidget.h"
#pragma execution_character_set("utf-8")
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    pTimer = new QTimer(this);
    this->connect(pTimer, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    //每隔一秒，计数器触发一次
    pTimer->start(1000);
}

MyWidget::~MyWidget()
{
//    pTimer->stop();
//    delete pTimer;
    delete ui;
}

void MyWidget::SetDisplay(QString strDisplay)
{
    ui->lineEdit_Display->setText(strDisplay);
}
void MyWidget::UpdateTime()
{
    ui->lineEdit_Time->setText(dateTime.currentDateTime().toString("hh:mm:ss"));
}
