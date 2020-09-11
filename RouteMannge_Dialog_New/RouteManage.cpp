#include "RouteManage.h"
#include "ui_RouteManage.h"

#pragma execution_character_set("utf-8")

RouteManage::RouteManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RouteManage)
{
    ui->setupUi(this);


}

RouteManage::~RouteManage()
{
    m_RouteManager.ReleaseRoute();
    delete ui;
}

void RouteManage::on_pushButton_Init_clicked()
{
    if(m_RouteManager.InitRoutePath("D:/BZVisualInspect/UserData/Mission","D:/BZVisualInspect/Bin/SysConfig",false))
    {
        ui->plainTextEdit_Show->appendPlainText("初始化成功！");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("初始化失败！");
    }
}
void RouteManage::on_pushButton_Start_clicked()
{
    if(m_RouteManager.RouteStart())
    {
        ui->plainTextEdit_Show->appendPlainText("开始成功！");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("开始失败！");
    }

}

void RouteManage::on_pushButton_Reset_clicked()
{

    if(m_RouteManager.RouteReset())
    {
        ui->plainTextEdit_Show->appendPlainText("复位成功!");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("复位失败!");
    }
}

void RouteManage::on_pushButton_Stop_clicked()
{
    if(m_RouteManager.RouteStop())
    {
        ui->plainTextEdit_Show->appendPlainText("停止成功!");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("停止失败!");
    }
}
void RouteManage::on_pushButton_Check_clicked()
{
    if(m_RouteManager.RouteRunFront())
    {
        ui->plainTextEdit_Show->appendPlainText("开始检测成功！");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("开始检测失败！");
    }
}

void RouteManage::on_pushButton_ParamDlg_clicked()
{
    m_RouteManager.CallRouteParamDlg();
}

void RouteManage::on_pushButton_LightParamDlg_clicked()
{
    m_RouteManager.CallLightParamDlg();
}

void RouteManage::on_pushButton_VelAccDlg_clicked()
{
    m_RouteManager.CallRouteManageDlg();
}

void RouteManage::on_pushButton_DebugDlg_clicked()
{
    m_RouteManager.CallMotionDebugDlg();
}

void RouteManage::on_pushButton_ModelDlg_clicked()
{
    m_RouteManager.CallMotionModelDlg();
}
