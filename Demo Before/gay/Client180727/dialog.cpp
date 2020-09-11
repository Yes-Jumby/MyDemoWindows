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
    loadBytes = LOADBYTES;
    gotBytes = 0;
    nameSize = 0;
    file = Q_NULLPTR;
    fileMessage = 4;
    ui->Prog->setValue(0); // 进度条置零
    tcpClient=new QTcpSocket(this); //创建socket变量
    connect(tcpClient, SIGNAL(bytesWritten(qint64)),
                this, SLOT(continue_transfer(qint64)));
    //connect(tcpClient,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(tcpClient,SIGNAL(readyRead()),
            this,SLOT(onSocketReadyRead()));
}

Dialog::~Dialog()
{
    delete ui;
    tcpClient->close();
    delete tcpClient;
}

void Dialog::on_BTN_Config_clicked()
{
    IP = ui->lineIP->text();
    PORT = ui->linePORT->text().toInt();
    ui->textEdit->append(QString("Host:[%1:%2] Confirmed").arg(IP).arg(PORT));
    ui->BTN_Config->setEnabled(false);
}

/*--- 点击监听按钮 ---*/
void Dialog::on_listenBtn_clicked()
{
    tcpClient->connectToHost(QHostAddress(IP),PORT);//
    ui->textEdit->append("Client join Server[127.0.0.1:8001]");
}

void Dialog::onSocketReadyRead()
{//readyRead()信号槽函数
    QDataStream in(tcpClient);
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
            ui->textEdit->append(QString("Client Reveived CMD: %1").arg(str));
            //tcpSocket->close(); // 关socket
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

    /* 首部未接收/未接收完 */
    if(gotBytes <= 2 * sizeof(qint64) + sizeof(qint16))
    {
        if(!nameSize) // 首部后部两个长度字段未接收
        {
            if(tcpClient->bytesAvailable() >= 2 * sizeof(qint64))//文件类型 总大小 名字大小
            {
                in >> fileBytes >> nameSize;//112616  94
                gotBytes = gotBytes + 2 * sizeof(qint64);//16
                ui->Prog->setMaximum(fileBytes);
                ui->Prog->setValue(gotBytes);
            }
            else // 数据不足，等下次
                return;
        }
        else if(tcpClient->bytesAvailable() >= nameSize)
        {
            in >> fileName;//文件名
            gotBytes += nameSize;//110
            ui->Prog->setValue(gotBytes);
        }
        else // 数据不足文件名长度，等下次
            return;
    }

    /* 已读文件名、文件未打开 -> 尝试打开文件 */
    if(!fileName.isEmpty() && file == Q_NULLPTR)
    {
        file = new QFile(fileName);
        if(!file->open(QFile::WriteOnly)) // 打开失败
        {
            ui->textEdit->append(QString("*** File Open Failed ***").arg(fileName));
            delete file;
            file = Q_NULLPTR;
            return;
        }
        ui->textEdit->append(QString("Open %1 Successfully!").arg(fileName));
    }
    if(file == Q_NULLPTR) // 文件未打开，不能进行后续操作
        return;

    if(gotBytes < fileBytes) // 文件未接收完
    {
        gotBytes += tcpClient->bytesAvailable();
        ui->Prog->setValue(gotBytes);
        file->write(tcpClient->readAll());
    }
    if(gotBytes == fileBytes) // 文件接收完
    {
        //tcpSocket->close(); // 关socket
        //receive = Q_NULLPTR;
        fileMessage = 4;//重置文件类型
        file->close(); // 关文件
        delete file;
        file = Q_NULLPTR;
        ui->textEdit->append(QString("Finish receiving %1").arg(fileName));
        //ui->listenBtn->setEnabled(true);
        ui->Prog->reset(); // 进度条归零
        fileName.clear(); // 清空文件名
        fileBytes = gotBytes = nameSize = 0;
    }
}

void Dialog::on_pushButton_clicked()
{  
    if(fileName.isEmpty())
        {
            QByteArray str = "Client Sent CMD: ";
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

            tcpClient->write(buf);

            ui->textEdit->append(str.append(data));
            //tcpClient->close(); // 关socket
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

        /* 无路径文件名 */
        QString sfName = fileName.right(fileName.size() -
                fileName.lastIndexOf('/') - 1);
        fileMessage = 0;
        /* 首部 = 总大小 + 文件名长度 + 文件名 */
        /* 首部 = 文件类型 + 总大小 + 文件名长度 + 文件名 */
        out << qint16(0) <<qint64(0) << qint64(0) << sfName;
        /* 总大小加上首部的大小 */
        fileBytes += buf.size();//70052886
        ui->Prog->setMaximum(fileBytes);
        /* 重写首部的前两个长度字段 */
        out.device()->seek(0);
        //int a = sizeof(int);//110 - 16= 94
        out << fileMessage <<fileBytes << (qint64(buf.size()) - 2 * sizeof(qint64) - sizeof(qint16));//文件类型 文件大小 文件名大小
        /* 发送首部，计算剩余大小 */
        restBytes = fileBytes - tcpClient->write(buf);
}

/*--- 继续传输 ---*/
void Dialog::continue_transfer(qint64 sentSize)
{
    if(fileMessage == 1)
    {
        return;
    }
    sentBytes += sentSize;
    ui->Prog->setValue(sentBytes);
    /* 还有数据要发 */
    if(restBytes > 0)
    {
        /* 从文件读数据 */
        QByteArray buf = file->read(qMin(loadBytes, restBytes));
        /* 发送 */
        restBytes -= tcpClient->write(buf);
    }
    else
        file->close();
    /* 全部发送完 */
    if(sentBytes == fileBytes)
    {
        //tcpClient->close(); // 关socket
        fileBytes = 0;
        sentBytes = 0;
        restBytes = 0;
        fileMessage = 4;
        fileName.clear(); // 清空文件名
        ui->textEdit->append(QString("Finish sending!"));
        //ui->sendBtn->setEnabled(false);
        ui->Prog->reset(); // 进度条归零
    }
}

void Dialog::on_BTN_Quit_clicked()
{
    this->close();
}

void Dialog::on_selectBtn_clicked()
{
    /* 开文件选择窗选文件，返回带路径文件名 */
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
