#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "piont.h"
#include <iostream>
using namespace std;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    int num=1;
private:
    Ui::Dialog *ui;
private slots:
void recvdata(const point &data);//来接收Dialog界面传过来的数据
void recvdata1();//来接收Dialog界面传过来的数据
void on_pushButton_clicked();
signals:
    void HsendData(point &senddata);//作为信号来发送senddata这个数据；
};

#endif // DIALOG_H
