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
    setAttribute(Qt::WA_DeleteOnClose);
    //模板级别
    m_sCurrentSchmaModelIndex = m_pRouteManager->m_iSchmaModelIndex;
    for(int i = 0;i < m_pRouteManager->m_listSchemaModelName.size();i++)
    {
        ui->comboBox_ModelIndex->addItem(m_pRouteManager->m_listSchemaModelName.at(i));
    }
    ui->comboBox_ModelIndex->setCurrentIndex(m_sCurrentSchmaModelIndex);
    UpdateLineEdits(m_sCurrentSchmaModelIndex);
    connect(ui->comboBox_ModelIndex, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ this->ModelComboBoxChange(index);});

    connect(ui->checkBox_EnableCheckDoor,SIGNAL(stateChanged(int)),this, SLOT(EnableCheckDoorOnCheckChanged()));
    connect(ui->checkBox_EnableFloodLight,SIGNAL(stateChanged(int)),this, SLOT(EnableFloodLightOnCheckChanged()));
}

CDlgRouteManage::~CDlgRouteManage()
{
    delete ui;
}

void CDlgRouteManage::ModelComboBoxChange(int index)
{
    m_sCurrentSchmaModelIndex = index;
    UpdateLineEdits(m_sCurrentSchmaModelIndex);
    m_qStr = tr("模板切换到%1！").arg(ui->comboBox_ModelIndex->currentText());
    ui->plainTextEdit_Show->appendPlainText(m_qStr);
}
void CDlgRouteManage::UpdateLineEdits(short ParamNum)
{
    //path1
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iFrontVel);
    ui->lineEdit_FrontVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iFrontAcc);
    ui->lineEdit_FrontAcc->setText(m_qStr);
    //path2
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iFrameVel);
    ui->lineEdit_FrameVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iFrameAcc);
    ui->lineEdit_FrameAcc->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iFrameCornerVel);
    ui->lineEdit_FrameCornerVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iFrameCornerAcc);
    ui->lineEdit_FrameCornerAcc->setText(m_qStr);
    //path3
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iUpDownCameraVel);
    ui->lineEdit_UpDownCameraVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iUpDownCameraAcc);
    ui->lineEdit_UpDownCameraAcc->setText(m_qStr);
    //path4
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iBackVel);
    ui->lineEdit_BackVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iBackAcc);
    ui->lineEdit_BackAcc->setText(m_qStr);
    //path5
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iLineVel);
    ui->lineEdit_LineVel->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(ParamNum).iLineAcc);
    ui->lineEdit_LineAcc->setText(m_qStr);
    //复选框
    ui->checkBox_EnableCheckDoor->setChecked(m_pRouteManager->m_isEnableCheckDoor);
    ui->checkBox_EnableFloodLight->setChecked(m_pRouteManager->m_bFloodlightOn);
}
int CDlgRouteManage::EnableCheckDoorOnCheckChanged()
{
    if (ui->checkBox_EnableCheckDoor->isChecked())
    {
        m_pRouteManager->m_isEnableCheckDoor = true;
    }
    else
    {
        m_pRouteManager->m_isEnableCheckDoor = false;
    }
    return 0;

}
int CDlgRouteManage::EnableFloodLightOnCheckChanged()
{
    if (ui->checkBox_EnableFloodLight->isChecked())
    {
        m_pRouteManager->FloodlightOn(true);
    }
    else
    {
        m_pRouteManager->FloodlightOn(false);
    }
    return 0;
}
//path1
void CDlgRouteManage::on_pushButton_FrontVel_clicked()
{
    if(ui->lineEdit_FrontVel->text().toInt() > 90)
    {
        ui->plainTextEdit_Show->appendPlainText("正面检测最大检测速度为90！");
        return;
    }
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iFrontVel = ui->lineEdit_FrontVel->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_FrontAcc_clicked()
{

    if(ui->lineEdit_FrontAcc->text().toInt() > 20)
    {
        ui->plainTextEdit_Show->appendPlainText("正面检测最大检测加速度为20！");
        return;
    }
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iFrontAcc = ui->lineEdit_FrontAcc->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path2
void CDlgRouteManage::on_pushButton_FrameVel_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iFrameVel = ui->lineEdit_FrameVel->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_FrameAcc_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iFrameAcc = ui->lineEdit_FrameAcc->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_FrameCornerVel_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iFrameCornerVel = ui->lineEdit_FrameCornerVel->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_FrameCornerAcc_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iFrameCornerAcc = ui->lineEdit_FrameCornerAcc->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}
//path3
void CDlgRouteManage::on_pushButton_UpDownCameraVel_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iUpDownCameraVel = ui->lineEdit_UpDownCameraVel->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_UpDownCameraAcc_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iUpDownCameraAcc = ui->lineEdit_UpDownCameraAcc->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path4
void CDlgRouteManage::on_pushButton_BackVel_clicked()
{
    if(ui->lineEdit_BackVel->text().toInt() > 90)
    {
        ui->plainTextEdit_Show->appendPlainText("背面检测最大检测速度为90！");
    }
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iBackVel = ui->lineEdit_BackVel->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_BackAcc_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iBackAcc = ui->lineEdit_BackAcc->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//path5
void CDlgRouteManage::on_pushButton_LineVel_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iLineVel = ui->lineEdit_LineVel->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteManage::on_pushButton_LineAcc_clicked()
{
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).iLineAcc = ui->lineEdit_LineAcc->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}
