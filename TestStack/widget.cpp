#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget_Show->setCurrentIndex(0);
    //设置窗口有最小化按钮
      Qt::WindowFlags flags = Qt::Dialog;
      flags |= Qt::WindowMinMaxButtonsHint;
      flags |= Qt::WindowCloseButtonHint;
      setWindowFlags(flags);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Show1_clicked()
{
    ui->stackedWidget_Show->setCurrentIndex(0);
}

void Widget::on_pushButton_Show1_2_clicked()
{
    ui->stackedWidget_Show->setCurrentIndex(1);

}

void Widget::on_pushButton_Show1_3_clicked()
{
    ui->stackedWidget_Show->setCurrentIndex(2);
}

void Widget::on_pushButton_Show1_4_clicked()
{
    ui->stackedWidget_Show->setCurrentIndex(3);
}
