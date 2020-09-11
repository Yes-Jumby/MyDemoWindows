#include "DlgRouteManage.h"
#include "ui_DlgRouteManage.h"

CDlgRouteManage::CDlgRouteManage(QWidget *parent,CRouteManager *pRouteManager) :
    QDialog(parent),
    m_pRouteManager(pRouteManager),
    ui(new Ui::CDlgRouteManage)
{
    ui->setupUi(this);
    //设置窗口格式
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    //path1
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontVel);
    ui->lineEdit_FrontVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontAcc);
    ui->lineEdit_FrontAcc->setText(m_qStr);
    //path2
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameVel);
    ui->lineEdit_FrameVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameAcc);
    ui->lineEdit_FrameAcc->setText(m_qStr);
    //path3
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iUpDownCameraVel);
    ui->lineEdit_UpDownCameraVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iUpDownCameraAcc);
    ui->lineEdit_UpDownCameraAcc->setText(m_qStr);
    //path4
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackVel);
    ui->lineEdit_BackVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackAcc);
    ui->lineEdit_BackAcc->setText(m_qStr);
    //path5
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iLineVel);
    ui->lineEdit_LineVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iLineAcc);
    ui->lineEdit_LineAcc->setText(m_qStr);
}

CDlgRouteManage::~CDlgRouteManage()
{
    delete ui;
}

//path1
void CDlgRouteManage::on_pushButton_FrontVel_clicked()
{
    m_pRouteManager->m_iFrontVel = ui->lineEdit_FrontVel->text().toInt();
    if(m_pRouteManager->m_iFrontVel > 240)
    {
        m_pRouteManager->m_iFrontVel = 240;
        ui->plainTextEdit_Show->appendPlainText("正面检测最大检测速度为200！");
    }
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_FrontAcc_clicked()
{
    m_pRouteManager->m_iFrontAcc = ui->lineEdit_FrontAcc->text().toInt();
    if(m_pRouteManager->m_iFrontAcc > 20)
    {
        m_pRouteManager->m_iFrontAcc = 20;
    }
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path2
void CDlgRouteManage::on_pushButton_FrameVel_clicked()
{
    m_pRouteManager->m_iFrameVel = ui->lineEdit_FrameVel->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_FrameAcc_clicked()
{
    m_pRouteManager->m_iFrameAcc = ui->lineEdit_FrameAcc->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path3
void CDlgRouteManage::on_pushButton_UpDownCameraVel_clicked()
{
    m_pRouteManager->m_iUpDownCameraVel = ui->lineEdit_UpDownCameraVel->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_UpDownCameraAcc_clicked()
{
    m_pRouteManager->m_iUpDownCameraAcc = ui->lineEdit_UpDownCameraAcc->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path4
void CDlgRouteManage::on_pushButton_BackVel_clicked()
{
    m_pRouteManager->m_iBackVel = ui->lineEdit_BackVel->text().toInt();
    if(m_pRouteManager->m_iBackVel > 240)
    {
        m_pRouteManager->m_iBackVel = 240;
        ui->plainTextEdit_Show->appendPlainText("背面检测最大检测速度为200！");
    }
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_BackAcc_clicked()
{
    m_pRouteManager->m_iBackAcc = ui->lineEdit_BackAcc->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path5
void CDlgRouteManage::on_pushButton_LineVel_clicked()
{
    m_pRouteManager->m_iLineVel = ui->lineEdit_LineVel->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_LineAcc_clicked()
{
    m_pRouteManager->m_iLineAcc = ui->lineEdit_LineAcc->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}
