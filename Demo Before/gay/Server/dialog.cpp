#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include <QDataStream>
#include <QFile>
#include <QHostAddress>
#include <QFileDialog>

const qint64 LOADBYTES = 4 * 1024; // 4 kilo-byte
const int DATA_STREAM_VERSION = QDataStream::Qt_5_8;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineIP->setText("127.0.0.1");
    ui->linePORT->setText("8001");
    PORT = 8001;
    IP = "127.0.0.1";
    fileBytes = sentBytes = restBytes = 0;
    gotBytes = 0;
    nameSize = 0;
    loadBytes = LOADBYTES;
    fileMessage = 4;
    file = Q_NULLPTR;
    ui->Prog->setValue(0); // ����������
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(onNewConnection()));

}

Dialog::~Dialog()
{
    delete ui;
    tcpServer->close();
    delete tcpServer;
}

void Dialog::on_BTN_Config_clicked()
{
    IP = ui->lineIP->text();
    PORT = ui->linePORT->text().toInt();
    ui->textEdit->append(QString("Host:[%1:%2] Confirmed").arg(IP).arg(PORT));
    ui->BTN_Config->setEnabled(false);
}

/*--- ����������ť ---*/
void Dialog::on_listenBtn_clicked()
{
    tcpServer->listen(QHostAddress::LocalHost,PORT);//
    ui->listenBtn->setEnabled(false);
    ui->textEdit->append("Server:127.0.0.1:8001");
}

void Dialog::onNewConnection()
{
//    ui->plainTextEdit->appendPlainText("��������");
    tcpSocket = tcpServer->nextPendingConnection(); //����socket
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
    connect(tcpSocket, SIGNAL(bytesWritten(qint64)),
                this, SLOT(continue_transfer(qint64)));

}

void Dialog::onSocketReadyRead()
{//��ȡ���������ı�
    QDataStream in(tcpSocket);
    in.setVersion(DATA_STREAM_VERSION);
    if(fileMessage == 4)
    {
        in >> fileMessage;
        gotBytes = gotBytes + sizeof(qint16);
        if(fileMessage)
        {
            QByteArray data;
            in >> data;
            QString str = data;
            ui->textEdit->append(QString("Server Reveived CMD: %1").arg(str));
            //tcpSocket->close(); // ��socket
            fileMessage = 4;
            gotBytes = 0;
            //receive = Q_NULLPTR;
            if(str == "@openRemoteCamera")
            {
                //openCamera();
            }
            if(str == "@closeRemoteCamera")
            {
                //closeCamera();
            }
            return;
        }
    }

    /* �ײ�δ����/δ������ */
    if(gotBytes <= 2 * sizeof(qint64) + sizeof(qint16))
    {
        if(!nameSize) // �ײ��������������ֶ�δ����
        {
            if(tcpSocket->bytesAvailable() >= 2 * sizeof(qint64))//�ļ����� �ܴ�С ���ִ�С
            {
                in >> fileBytes >> nameSize;//112616  94
                gotBytes = gotBytes + 2 * sizeof(qint64);//16
                ui->Prog->setMaximum(fileBytes);
                ui->Prog->setValue(gotBytes);
            }
            else // ���ݲ��㣬���´�
                return;
        }
        else if(tcpSocket->bytesAvailable() >= nameSize)
        {
            in >> fileName;//�ļ���
            gotBytes += nameSize;//110
            ui->Prog->setValue(gotBytes);
        }
        else // ���ݲ����ļ������ȣ����´�
            return;
    }

    /* �Ѷ��ļ������ļ�δ���� -> ���Դ����ļ� */
    if(!fileName.isEmpty() && file == Q_NULLPTR)
    {
        file = new QFile(fileName);
        if(!file->open(QFile::WriteOnly)) // ����ʧ��
        {
            ui->textEdit->append(QString("*** File Open Failed ***").arg(fileName));
            delete file;
            file = Q_NULLPTR;
            return;
        }
        ui->textEdit->append(QString("Open %1 Successfully!").arg(fileName));
    }
    if(file == Q_NULLPTR) // �ļ�δ�򿪣����ܽ��к�������
        return;

    if(gotBytes < fileBytes) // �ļ�δ������
    {
        gotBytes += tcpSocket->bytesAvailable();
        ui->Prog->setValue(gotBytes);
        file->write(tcpSocket->readAll());
    }
    if(gotBytes == fileBytes) // �ļ�������
    {
        //tcpSocket->close(); // ��socket
        //receive = Q_NULLPTR;
        fileMessage = 4;//�����ļ�����
        file->close(); // ���ļ�
        delete file;
        file = Q_NULLPTR;
        ui->textEdit->append(QString("Finish receiving %1").arg(fileName));
        //ui->listenBtn->setEnabled(true);
        ui->Prog->reset(); // ����������
        fileName.clear(); // �����ļ���
        fileBytes = gotBytes = nameSize = 0;
    }
}

void Dialog::on_pushButton_clicked()
{
    if(fileName.isEmpty())
    {
        QByteArray str = "Server Sent CMD: ";
        QByteArray data = ui->lineEdit->text().toLatin1();
        QByteArray buf;
        QDataStream out(&buf, QIODevice::WriteOnly);
        out.setVersion(DATA_STREAM_VERSION);
        fileMessage = 1;
        out << fileMessage << data;
        if(data == "OpenLocalCamera")
        {
            //openCamera();
            ui->textEdit->append(str.append(data));
            return;
        }
        if(data == "CloseLocalCamera")
        {
            //closeCamera();
            ui->textEdit->append(str.append(data));
            return;
        }

        tcpSocket->write(buf);

        ui->textEdit->append(str.append(data));
        //tcpClient->close(); // ��socket
        return;
    }
    file = new QFile(fileName);
    if(!file->open(QFile::ReadOnly))
    {
        ui->textEdit->append(QString("*** start_transfer(): File-Open-Error"));
        return;
    }

    fileBytes = file->size();
    ui->Prog->setValue(0);
    ui->textEdit->append(QString("Connection Established!"));

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out.setVersion(DATA_STREAM_VERSION);

    /* ��·���ļ��� */
    QString sfName = fileName.right(fileName.size() -
                                    fileName.lastIndexOf('/') - 1);
    fileMessage = 0;
    /* �ײ� = �ܴ�С + �ļ������� + �ļ��� */
    /* �ײ� = �ļ����� + �ܴ�С + �ļ������� + �ļ��� */
    out << qint16(0) <<qint64(0) << qint64(0) << sfName;
    /* �ܴ�С�����ײ��Ĵ�С */
    fileBytes += buf.size();//70052886
    ui->Prog->setMaximum(fileBytes);
    /* ��д�ײ���ǰ���������ֶ� */
    out.device()->seek(0);
    //int a = sizeof(int);//110 - 16= 94
    out << fileMessage <<fileBytes << (qint64(buf.size()) - 2 * sizeof(qint64) - sizeof(qint16));//�ļ����� �ļ���С �ļ�����С
    /* �����ײ�������ʣ����С */
    restBytes = fileBytes - tcpSocket->write(buf);
}

/*--- �������� ---*/
void Dialog::continue_transfer(qint64 sentSize)
{
    if(fileMessage == 1)
    {
        return;
    }
    sentBytes += sentSize;
    ui->Prog->setValue(sentBytes);
    /* ��������Ҫ�� */
    if(restBytes > 0)
    {
        /* ���ļ������� */
        QByteArray buf = file->read(qMin(loadBytes, restBytes));
        /* ���� */
        restBytes -= tcpSocket->write(buf);
    }
    else
        file->close();
    /* ȫ�������� */
    if(sentBytes == fileBytes)
    {
        //tcpClient->close(); // ��socket
        fileBytes = 0;
        sentBytes = 0;
        restBytes = 0;
        fileMessage = 4;
        fileName.clear(); // �����ļ���
        ui->textEdit->append(QString("Finish sending!"));
        //ui->sendBtn->setEnabled(false);
        ui->Prog->reset(); // ����������
    }
}

void Dialog::on_BTN_Quit_clicked()
{
    this->close();
}

void Dialog::on_selectBtn_clicked()
{
    /* ���ļ�ѡ����ѡ�ļ������ش�·���ļ��� */
        fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
        {
            ui->textEdit->append(QString("File %1 Opened!").arg(fileName));
            //ui->sendBtn->setEnabled(true);
            //ui->selectBtn->setEnabled(false);
        }
        else
            ui->textEdit->append(QString("*** FAIL OPENING FILE"));
}

void Dialog::on_Test_clicked()
{
    QList<int>list;
    list<<5;
    qDebug()<<list[0]<<list.size()<<endl;
}
