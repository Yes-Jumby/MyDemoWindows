#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    //qRegisterMetaType<point>("point");

}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_pushButton_clicked()
{
    point point(2,2);
    emit  sendData(point);
}
void Dialog1::Crecvdata(point &data)
{
    cout<<"point(1,1) received"<<endl;
    QString str;
    str=QString("x:%1 y:%2 ").arg(data.xPos).arg(data.yPos);
    ui->EDIT->setText("");
    ui->EDIT->setText(str);
    cout<<"point(1,1) displayed"<<endl;
}
