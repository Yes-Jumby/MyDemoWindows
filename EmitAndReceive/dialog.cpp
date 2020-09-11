#include "dialog.h"
#include "ui_dialog.h"
#include "dialog1.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qRegisterMetaType<point>("point");
    Dialog1* dialog= new Dialog1(this);//要找到信号的来源的界面
    dialog->setModal(false);    //此处ture为模态，false为非模态
    dialog->show();
    //接收数据
    connect(dialog,SIGNAL(sendData(const point &)),this,SLOT(recvdata(const point &)));
    connect(dialog,SIGNAL(sendData(const point &)),this,SLOT(recvdata1()));
    //发送数据
    connect(this,SIGNAL(HsendData(point &)),dialog,SLOT(Crecvdata(point &)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::recvdata(const point &data)
{
    //ui->SHOW->setText(data);
    QString str;
    str=QString("x:%1 y:%2 ").arg(data.xPos).arg(data.yPos);
    ui->SHOW->append(str);
}

void Dialog::recvdata1()
{
    QString str;
    str=QString("数据接收次数:%1").arg(num);
    num++;
    ui->SHOWNum->setText(str);
}

void Dialog::on_pushButton_clicked()
{
    point point(1,1);
    emit  HsendData(point);
    cout<<"point(1,1) sender"<<endl;
}
