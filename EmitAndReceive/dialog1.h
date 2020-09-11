#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include "dialog.h"
#include "piont.h"
#include <iostream>
using namespace std;
namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

private slots:
    void on_pushButton_clicked();
    void Crecvdata(point &data);//来接收Dialog界面传过来的数据
signals:
    void sendData(const point &senddata);//作为信号来发送senddata这个数据；
private:
    Ui::Dialog1 *ui;
};

#endif // DIALOG1_H
