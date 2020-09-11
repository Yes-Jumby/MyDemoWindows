#include "CreatEvent.h"
#include "ui_CreatEvent.h"

CreatEvent::CreatEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatEvent)
{
    ui->setupUi(this);
    m_iThreadNum = 0;
    m_iEvent = 0;
    m_iIndex = 0;
    ui->lineEdit_EventNum->setText(QString("%1").arg(m_iEvent));
    ui->lineEdit_ThreadWaitNum->setText(QString("%1").arg(m_iThreadNum));
    qRegisterMetaType<DWORD>("DWORD");
    connect(this,&CreatEvent::SignalforSingleObjectReturn,this,&CreatEvent::DisplaySignalforSingleObjectReturn);
}

CreatEvent::~CreatEvent()
{
    delete ui;
}
void CreatEvent::DisplaySignalforSingleObjectReturn(DWORD value,int index)
{
    m_iThreadNum--;
    ui->lineEdit_ThreadWaitNum->setText(QString("%1").arg(m_iThreadNum));
    if(value == WAIT_OBJECT_0)
    {
        ui->plainTextEdit_Show->appendPlainText(QString("=========线程:[%1]等待成功=======").arg(index));
    }else if(value == STATUS_TIMEOUT)
    {
        ui->plainTextEdit_Show->appendPlainText("等待超时");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("等待失败");
    }
}
void CreatEvent::on_pushButton_clicked()
{
    m_Handle = CreateEvent(NULL,true,false,NULL);
    ui->plainTextEdit_Show->appendPlainText("产生一个人工量");//可以一带多，且设置为有信号，就一直有信号
    m_iEvent++;
    ui->lineEdit_EventNum->setText(QString("%1").arg(m_iEvent));
}

void CreatEvent::on_pushButton_2_clicked()
{
    m_Handle = CreateEvent(NULL,false,false,NULL);
    ui->plainTextEdit_Show->appendPlainText("产生一个自动量");//只能一带一
    m_iEvent++;
    ui->lineEdit_EventNum->setText(QString("%1").arg(m_iEvent));
}

void CreatEvent::on_pushButton__SetEvent_clicked()
{
    SetEvent(m_Handle);
}

void CreatEvent::on_pushButton_Reset_clicked()
{
    ResetEvent(m_Handle);
}

void CreatEvent::on_pushButton_PulseEvent_clicked()
{
    PulseEvent(m_Handle);//有线程等待才有用，否则会产生丢失
}

void CreatEvent::on_pushButton_Wait_clicked()
{
    QFuture<void> future = QtConcurrent::run(this, &CreatEvent::FunWaitForCornelObject);
    m_iThreadNum++;
    ui->lineEdit_ThreadWaitNum->setText(QString("%1").arg(m_iThreadNum));
    m_iIndex++;
}

void CreatEvent::on_pushButton_Close_clicked()
{
    CloseHandle(m_Handle);
    ui->plainTextEdit_Show->appendPlainText("关闭");
    m_iEvent--;
    ui->lineEdit_EventNum->setText(QString("%1").arg(m_iEvent));
}

void CreatEvent::FunWaitForCornelObject()
{
    int index = m_iIndex;
    DWORD ReturnValue = WaitForSingleObject(m_Handle,5000);
    emit SignalforSingleObjectReturn(ReturnValue,index);
}
