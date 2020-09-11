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

    void onNewConnection();//QTcpServer��newConnection()�ź�
    void onSocketReadyRead();
    void continue_transfer(qint64 sentSize);
    void on_listenBtn_clicked();
    void on_BTN_Config_clicked();

    void on_pushButton_clicked();

    void on_BTN_Quit_clicked();

    void on_selectBtn_clicked();

    void on_Test_clicked();

private:
    Ui::Dialog *ui;
    QTcpServer *tcpServer; //TCP������

    QTcpSocket *tcpSocket;//TCPͨѶ��Socket

    QString getLocalIP();//��ȡ����IP��ַ
    QString IP;
    qint64 PORT;
    QString fileName;
    QFile *file;
    qint16 fileMessage;
    /* �ѽ������ݣ������ݣ��ļ������� */
    qint64 gotBytes, nameSize;
    /* �����ݴ�С���ѷ������ݴ�С��ʣ�����ݴ�С��ÿ�η������ݿ���С */
    qint64 fileBytes, sentBytes, restBytes, loadBytes;

};

#endif // DIALOG_H
