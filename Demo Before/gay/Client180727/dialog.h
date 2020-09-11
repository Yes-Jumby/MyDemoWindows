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
//�Զ���ۺ���
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

    QString getLocalIP();//��ȡ����IP��ַ
    QString IP;
    qint64 PORT;
    QFile *file;
    QString fileName;
    qint16 fileMessage;
    /* �����ݴ�С���ѷ������ݴ�С��ʣ�����ݴ�С��ÿ�η������ݿ��С */
    qint64 fileBytes, sentBytes, restBytes, loadBytes;
    /* �ѽ������ݣ������ݣ��ļ������� */
    qint64 gotBytes, nameSize;

};

#endif // DIALOG_H
