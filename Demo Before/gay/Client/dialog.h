#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
//自定义槽函数
    void onSocketReadyRead();
    void on_pushButton_clicked();
    void on_listenBtn_clicked();
    void on_BTN_Config_clicked();
    void continue_transfer(qint64);
    void on_BTN_Quit_clicked();

    void on_selectBtn_clicked();

private:
    Ui::Dialog *ui;
    QTcpSocket  *tcpClient;  //socket

    QString getLocalIP();//获取本机IP地址
    QString IP;
    qint64 PORT;
    QFile *file;
    QString fileName;
    qint16 fileMessage;
    /* 总数据大小，已发送数据大小，剩余数据大小，每次发送数据块大小 */
    qint64 fileBytes, sentBytes, restBytes, loadBytes;
    /* 已接受数据，总数据，文件名长度 */
    qint64 gotBytes, nameSize;

};

#endif // DIALOG_H
