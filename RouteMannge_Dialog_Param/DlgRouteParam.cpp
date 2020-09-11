#include "DlgRouteParam.h"
#include "ui_DlgRouteParam.h"

CDlgRouteParam::CDlgRouteParam(QWidget *parent,CRouteManager *pRouteManager) :
    QDialog(parent),
    m_pRouteManager(pRouteManager),
    ui(new Ui::DlgRouteParam)
{
    ui->setupUi(this);
    //设置窗口格式
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setAttribute(Qt::WA_DeleteOnClose);
    //设置默认界面
    ui->stackedWidget->setCurrentIndex(0);
    //Fixed Point
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iP1);
    ui->lineEdit_P1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iP2);
    ui->lineEdit_P2->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iP3);
    ui->lineEdit_P3->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iP4);
    ui->lineEdit_P4->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iP5);
    ui->lineEdit_P5->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontGrat);
    ui->lineEdit_FrontGrat->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackGrat);
    ui->lineEdit_BackGrat->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iLightOpen);
    ui->lineEdit_LightOpen->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCircle14);
    ui->lineEdit_Circle14->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iRunBackOffSetY);
    ui->lineEdit_RunBackOffSetY->setText(m_qStr);
    //产品尺寸
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iLong);
    ui->lineEdit_Long->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iWidth);
    ui->lineEdit_Width->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontBackImageHeight);
    ui->lineEdit_FrontBackImageHeight->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iResetPointOffSetX);
    ui->lineEdit_ResetPointX->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iResetPointOffSetY);
    ui->lineEdit_ResetPointY->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iResetPointOffSetZ);
    ui->lineEdit_ResetPointZ->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iGetPointOffSetX);
    ui->lineEdit_GetPointX->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iGetPointOffSetY);
    ui->lineEdit_GetPointY->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iGetPointOffSetZ);
    ui->lineEdit_GetPointZ->setText(m_qStr);
    //正面
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontOffSetX);
    ui->lineEdit_FrontOffSetX->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontOffSetY);
    ui->lineEdit_FrontOffSetY->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrontOffSetZ);
    ui->lineEdit_FrontOffSetZ->setText(m_qStr);
    //中框
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetX1);
    ui->lineEdit_FrameOffSetX1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetY1);
    ui->lineEdit_FrameOffSetY1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetZ1);
    ui->lineEdit_FrameOffSetZ1->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetX2);
    ui->lineEdit_FrameOffSetX2->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetY2);
    ui->lineEdit_FrameOffSetY2->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetZ2);
    ui->lineEdit_FrameOffSetZ2->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetX3);
    ui->lineEdit_FrameOffSetX3->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetY3);
    ui->lineEdit_FrameOffSetY3->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetZ3);
    ui->lineEdit_FrameOffSetZ3->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetX4);
    ui->lineEdit_FrameOffSetX4->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetY4);
    ui->lineEdit_FrameOffSetY4->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameOffSetZ4);
    ui->lineEdit_FrameOffSetZ4->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameStep);
    ui->lineEdit_FrameStep->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetX1);
    ui->lineEdit_FrameCornerOffSetX1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetY1);
    ui->lineEdit_FrameCornerOffSetY1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetZ1);
    ui->lineEdit_FrameCornerOffSetZ1->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetX2);
    ui->lineEdit_FrameCornerOffSetX2->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetY2);
    ui->lineEdit_FrameCornerOffSetY2->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetZ2);
    ui->lineEdit_FrameCornerOffSetZ2->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetX3);
    ui->lineEdit_FrameCornerOffSetX3->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetY3);
    ui->lineEdit_FrameCornerOffSetY3->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetZ3);
    ui->lineEdit_FrameCornerOffSetZ3->setText(m_qStr);

    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetX4);
    ui->lineEdit_FrameCornerOffSetX4->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetY4);
    ui->lineEdit_FrameCornerOffSetY4->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iFrameCornerOffSetZ4);
    ui->lineEdit_FrameCornerOffSetZ4->setText(m_qStr);

    //翻转及摄像头
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCylinderOffSetX);
    ui->lineEdit_CylinderOffSetX->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCylinderOffSetY);
    ui->lineEdit_CylinderOffSetY->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCylinderOffSetZ);
    ui->lineEdit_CylinderOffSetZ->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCameraOffSetX);
    ui->lineEdit_CameraOffSetX->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCameraOffSetY);
    ui->lineEdit_CameraOffSetY->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iCameraOffSetZ);
    ui->lineEdit_CameraOffSetZ->setText(m_qStr);
    //背面
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackOffSetX);
    ui->lineEdit_BackOffSetX->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackOffSetY);
    ui->lineEdit_BackOffSetY->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackOffSetZ);
    ui->lineEdit_BackOffSetZ->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackOffSetX1);
    ui->lineEdit_BackOffSetX1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackOffSetY1);
    ui->lineEdit_BackOffSetY1->setText(m_qStr);
    m_qStr = QObject::tr("%1").arg(m_pRouteManager->m_iBackOffSetZ1);
    ui->lineEdit_BackOffSetZ1->setText(m_qStr);
    //中框轨迹
    m_pLineEdit[0] = ui->lineEdit_FrameStep1;
    m_pLineEdit[1] = ui->lineEdit_FrameStep2;
    m_pLineEdit[2] = ui->lineEdit_FrameStep3;
    m_pLineEdit[3] = ui->lineEdit_FrameStep4;
    m_pLineEdit[4] = ui->lineEdit_FrameStep5;
    m_pLineEdit[5] = ui->lineEdit_FrameStep6;
    m_pLineEdit[6] = ui->lineEdit_FrameStep7;
    m_pLineEdit[7] = ui->lineEdit_FrameStep8;
    m_pLineEdit[8] = ui->lineEdit_FrameStep9;
    m_pLineEdit[9] = ui->lineEdit_FrameStep10;
    m_pLineEdit[10] = ui->lineEdit_FrameStep11;
    m_pLineEdit[11] = ui->lineEdit_FrameStep12;
    m_pLineEdit[12] = ui->lineEdit_FrameStep13;
    m_pLineEdit[13] = ui->lineEdit_FrameStep14;
    m_pLineEdit[14] = ui->lineEdit_FrameStep15;
    m_pLineEdit[15] = ui->lineEdit_FrameStep16;
    m_pLineEdit[16] = ui->lineEdit_FrameStep17;
    m_pLineEdit[17] = ui->lineEdit_FrameStep18;
    m_pLineEdit[18] = ui->lineEdit_FrameStep19;
    m_pLineEdit[19] = ui->lineEdit_FrameStep20;
    m_pLineEdit[20] = ui->lineEdit_FrameStepCount;
    //更新参数
    m_sCurrentParamIndex = 0;
    UpdateFrameStepLineEdits(m_sCurrentParamIndex);
    ui->comboBox_ParamIndex->addItem("第一边");
    ui->comboBox_ParamIndex->addItem("第二边");
    ui->comboBox_ParamIndex->addItem("第三边");
    ui->comboBox_ParamIndex->addItem("第四边");
    ui->comboBox_ParamIndex->setCurrentIndex(m_sCurrentParamIndex);
    connect(ui->comboBox_ParamIndex, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ this->ComboBoxChange(index);});
}

CDlgRouteParam::~CDlgRouteParam()
{
    delete ui;
}
int CDlgRouteParam::GetSum(short ParamNum)
{
    int iSum =0;
    switch (ParamNum)
    {
    case 0:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            iSum = iSum + m_pRouteManager->m_iStep1[i];
        }
        break;
    case 1:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            iSum = iSum + m_pRouteManager->m_iStep2[i];
        }
        break;
    case 2:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            iSum = iSum + m_pRouteManager->m_iStep3[i];
        }
        break;
    case 3:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            iSum = iSum + m_pRouteManager->m_iStep4[i];
        }
        break;
    default:
        break;
    }
    return iSum;

}
void CDlgRouteParam::UpdateFrameStepLineEdits(short ParamNum)//显示电流
{
    switch (ParamNum)
    {
    case 0:
        m_qStr = tr("%1").arg(m_pRouteManager->m_iStepCount[ParamNum]);
        m_pLineEdit[20]->setText(m_qStr);
        m_qStr = tr("计划长度%1/目标长度%2").arg(GetSum(ParamNum)).arg(m_pRouteManager->m_iStepLength[ParamNum]);
        ui->label_Show->setText(m_qStr);
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_iStep1[i]);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    case 1:
        m_qStr = tr("%1").arg(m_pRouteManager->m_iStepCount[ParamNum]);
        m_pLineEdit[20]->setText(m_qStr);
        m_qStr = tr("计划长度%1/目标长度%2").arg(GetSum(ParamNum)).arg(m_pRouteManager->m_iStepLength[ParamNum]);
        ui->label_Show->setText(m_qStr);
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_iStep2[i]);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    case 2:
        m_qStr = tr("%1").arg(m_pRouteManager->m_iStepCount[ParamNum]);
        m_pLineEdit[20]->setText(m_qStr);
        m_qStr = tr("计划长度%1/目标长度%2").arg(GetSum(ParamNum)).arg(m_pRouteManager->m_iStepLength[ParamNum]);
        ui->label_Show->setText(m_qStr);
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_iStep3[i]);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    case 3:
        m_qStr = tr("%1").arg(m_pRouteManager->m_iStepCount[ParamNum]);
        m_pLineEdit[20]->setText(m_qStr);
        m_qStr = tr("计划长度%1/目标长度%2").arg(GetSum(ParamNum)).arg(m_pRouteManager->m_iStepLength[ParamNum]);
        ui->label_Show->setText(m_qStr);
        for(int i = 0;i < m_pRouteManager->m_iStepCount[ParamNum] ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_iStep4[i]);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    default:
        break;
    }
    for(int i=0;i<m_pRouteManager->m_iStepCount[m_sCurrentParamIndex];i++)
    {
        m_pLineEdit[i]->setEnabled(true);
    }
    for(int i = m_pRouteManager->m_iStepCount[m_sCurrentParamIndex];i < 20 ;i++)
    {
        m_qStr = tr("%1").arg(0);
        m_pLineEdit[i]->setText(m_qStr);
        m_pLineEdit[i]->setEnabled(false);
    }
}
void CDlgRouteParam::ComboBoxChange(int index)
{
    m_sCurrentParamIndex = index;
    UpdateFrameStepLineEdits(m_sCurrentParamIndex);
    m_qStr = tr("切换到%1！").arg(ui->comboBox_ParamIndex->currentText());
    ui->plainTextEdit_Show->appendPlainText(m_qStr);
}
//Fixed Point
void CDlgRouteParam::on_pushButton_PageIndex0_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CDlgRouteParam::on_pushButton_P1_clicked()
{
    m_pRouteManager->m_iP1 = ui->lineEdit_P1->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_P2_clicked()
{
    m_pRouteManager->m_iP2 = ui->lineEdit_P2->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_P3_clicked()
{
    m_pRouteManager->m_iP3 = ui->lineEdit_P3->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_P4_clicked()
{
    m_pRouteManager->m_iP4 = ui->lineEdit_P4->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_P5_clicked()
{
    m_pRouteManager->m_iP5 = ui->lineEdit_P5->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrontGrat_clicked()
{
    m_pRouteManager->m_iFrontGrat = ui->lineEdit_FrontGrat->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_BackGrat_clicked()
{
    m_pRouteManager->m_iBackGrat = ui->lineEdit_BackGrat->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_LightOpen_clicked()
{
    m_pRouteManager->m_iLightOpen = ui->lineEdit_LightOpen->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_Circle14_clicked()
{
    m_pRouteManager->m_iCircle14 = ui->lineEdit_Circle14->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_RunBackOffSetY_clicked()
{
    m_pRouteManager->m_iRunBackOffSetY = ui->lineEdit_RunBackOffSetY->text().toInt();
    m_pRouteManager->SaveConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//产品尺寸
void CDlgRouteParam::on_pushButton_PageIndex1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CDlgRouteParam::on_pushButton_Long_clicked()
{
    m_pRouteManager->m_iLong = ui->lineEdit_Long->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_Width_clicked()
{
    m_pRouteManager->m_iWidth = ui->lineEdit_Width->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrontBackImageHeight_clicked()
{
    m_pRouteManager->m_iFrontBackImageHeight = ui->lineEdit_FrontBackImageHeight->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_ResetPointX_clicked()
{
    m_pRouteManager->m_iResetPointOffSetX = ui->lineEdit_ResetPointX->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_ResetPointY_clicked()
{
    m_pRouteManager->m_iResetPointOffSetY = ui->lineEdit_ResetPointY->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_ResetPointZ_clicked()
{
    m_pRouteManager->m_iResetPointOffSetZ = ui->lineEdit_ResetPointZ->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_GetPointX_clicked()
{
    m_pRouteManager->m_iGetPointOffSetX = ui->lineEdit_GetPointX->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_GetPointY_clicked()
{
    m_pRouteManager->m_iGetPointOffSetY = ui->lineEdit_GetPointY->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_GetPointZ_clicked()
{
    m_pRouteManager->m_iGetPointOffSetZ = ui->lineEdit_GetPointZ->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//正面
void CDlgRouteParam::on_pushButton_PageIndex2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void CDlgRouteParam::on_pushButton_FrontOffSetX_clicked()
{
    m_pRouteManager->m_iFrontOffSetX = ui->lineEdit_FrontOffSetX->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrontOffSetY_clicked()
{
    m_pRouteManager->m_iFrontOffSetY = ui->lineEdit_FrontOffSetY->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrontOffSetZ_clicked()
{
    m_pRouteManager->m_iFrontOffSetZ = ui->lineEdit_FrontOffSetZ->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}
//中框
void CDlgRouteParam::on_pushButton_PageIndex3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void CDlgRouteParam::on_pushButton_FrameOffSetX1_clicked()
{
    m_pRouteManager->m_iFrameOffSetX1 = ui->lineEdit_FrameOffSetX1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetY1_clicked()
{
    m_pRouteManager->m_iFrameOffSetY1 = ui->lineEdit_FrameOffSetY1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetZ1_clicked()
{
    m_pRouteManager->m_iFrameOffSetZ1 = ui->lineEdit_FrameOffSetZ1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetX2_clicked()
{
    m_pRouteManager->m_iFrameOffSetX2 = ui->lineEdit_FrameOffSetX2->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetY2_clicked()
{
    m_pRouteManager->m_iFrameOffSetY2 = ui->lineEdit_FrameOffSetY2->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetZ2_clicked()
{
    m_pRouteManager->m_iFrameOffSetZ2 = ui->lineEdit_FrameOffSetZ2->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetX3_clicked()
{
    m_pRouteManager->m_iFrameOffSetX3 = ui->lineEdit_FrameOffSetX3->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetY3_clicked()
{
    m_pRouteManager->m_iFrameOffSetY3 = ui->lineEdit_FrameOffSetY3->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetZ3_clicked()
{
    m_pRouteManager->m_iFrameOffSetZ3 = ui->lineEdit_FrameOffSetZ3->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetX4_clicked()
{
    m_pRouteManager->m_iFrameOffSetX4 = ui->lineEdit_FrameOffSetX4->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetY4_clicked()
{
    m_pRouteManager->m_iFrameOffSetY4 = ui->lineEdit_FrameOffSetY4->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameOffSetZ4_clicked()
{
    m_pRouteManager->m_iFrameOffSetZ4 = ui->lineEdit_FrameOffSetZ4->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameStep_clicked()
{
    if(ui->lineEdit_FrameStep->text().toInt() == 9000)
    {
        m_pRouteManager->m_iFrameStep = ui->lineEdit_FrameStep->text().toInt();
        m_pRouteManager->SaveSchmaRouteConfig();
        ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("此参数禁止修改，请联系管理员！");
    }

}

//翻转及摄像头
void CDlgRouteParam::on_pushButton_PageIndex4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void CDlgRouteParam::on_pushButton_CylinderOffSetX_clicked()
{
    m_pRouteManager->m_iCylinderOffSetX = ui->lineEdit_CylinderOffSetX->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_CylinderOffSetY_clicked()
{
    m_pRouteManager->m_iCylinderOffSetY = ui->lineEdit_CylinderOffSetY->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_CylinderOffSetZ_clicked()
{
    m_pRouteManager->m_iCylinderOffSetZ = ui->lineEdit_CylinderOffSetZ->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_CameraOffSetX_clicked()
{
    m_pRouteManager->m_iCameraOffSetX = ui->lineEdit_CameraOffSetX->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_CameraOffSetY_clicked()
{
    m_pRouteManager->m_iCameraOffSetY = ui->lineEdit_CameraOffSetY->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_CameraOffSetZ_clicked()
{
    m_pRouteManager->m_iCameraOffSetZ = ui->lineEdit_CameraOffSetZ->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//背面
void CDlgRouteParam::on_pushButton_PageIndex5_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void CDlgRouteParam::on_pushButton_BackOffSetX_clicked()
{
    m_pRouteManager->m_iBackOffSetX = ui->lineEdit_BackOffSetX->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_BackOffSetY_clicked()
{
    m_pRouteManager->m_iBackOffSetY = ui->lineEdit_BackOffSetY->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_BackOffSetZ_clicked()
{
    m_pRouteManager->m_iBackOffSetZ = ui->lineEdit_BackOffSetZ->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}
void CDlgRouteParam::on_pushButton_BackOffSetX1_clicked()
{
    m_pRouteManager->m_iBackOffSetX1 = ui->lineEdit_BackOffSetX1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_BackOffSetY1_clicked()
{
    m_pRouteManager->m_iBackOffSetY1 = ui->lineEdit_BackOffSetY1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_BackOffSetZ1_clicked()
{
    m_pRouteManager->m_iBackOffSetZ1 = ui->lineEdit_BackOffSetZ1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

//中框R角
void CDlgRouteParam::on_pushButton_PageIndex6_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetX1_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetX1 = ui->lineEdit_FrameCornerOffSetX1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetY1_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetY1 = ui->lineEdit_FrameCornerOffSetY1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetZ1_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetZ1 = ui->lineEdit_FrameCornerOffSetZ1->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetX2_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetX2 = ui->lineEdit_FrameCornerOffSetX2->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetY2_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetY2 = ui->lineEdit_FrameCornerOffSetY2->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetZ2_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetZ2 = ui->lineEdit_FrameCornerOffSetZ2->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetX3_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetX3 = ui->lineEdit_FrameCornerOffSetX3->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetY3_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetY3 = ui->lineEdit_FrameCornerOffSetY3->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetZ3_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetZ3 = ui->lineEdit_FrameCornerOffSetZ3->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetX4_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetX4 = ui->lineEdit_FrameCornerOffSetX4->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetY4_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetY4 = ui->lineEdit_FrameCornerOffSetY4->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_FrameCornerOffSetZ4_clicked()
{
    m_pRouteManager->m_iFrameCornerOffSetZ4 = ui->lineEdit_FrameCornerOffSetZ4->text().toInt();
    m_pRouteManager->SaveSchmaRouteConfig();
    ui->plainTextEdit_Show->appendPlainText("设置保存成功！");
}

void CDlgRouteParam::on_pushButton_PageIndex7_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void CDlgRouteParam::on_pushButton_StepCount_clicked()
{
    m_pRouteManager->m_iStepCount[m_sCurrentParamIndex] = ui->lineEdit_FrameStepCount->text().toInt();
    for(int i=0;i<m_pRouteManager->m_iStepCount[m_sCurrentParamIndex];i++)
    {
        m_pLineEdit[i]->setEnabled(true);
    }
    for(int i = m_pRouteManager->m_iStepCount[m_sCurrentParamIndex];i < 20 ;i++)
    {
        m_qStr = tr("%1").arg(0);
        m_pLineEdit[i]->setText(m_qStr);
        m_pLineEdit[i]->setEnabled(false);
    }
}

void CDlgRouteParam::on_pushButton_FrameStepSave_clicked()
{
    switch (m_sCurrentParamIndex)
    {
    case 0:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[m_sCurrentParamIndex] ;i++)
        {
            m_pRouteManager->m_iStep1[i] = m_pLineEdit[i]->text().toDouble();
        }

        break;
    case 1:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[m_sCurrentParamIndex] ;i++)
        {
            m_pRouteManager->m_iStep2[i] = m_pLineEdit[i]->text().toDouble();
        }
        break;
    case 2:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[m_sCurrentParamIndex] ;i++)
        {
            m_pRouteManager->m_iStep3[i] = m_pLineEdit[i]->text().toDouble();
        }
        break;
    case 3:
        for(int i = 0;i < m_pRouteManager->m_iStepCount[m_sCurrentParamIndex] ;i++)
        {
            m_pRouteManager->m_iStep4[i] = m_pLineEdit[i]->text().toDouble();
        }
        break;
    default:
        break;
    }
    UpdateFrameStepLineEdits(m_sCurrentParamIndex);
    if(GetSum(m_sCurrentParamIndex) == m_pRouteManager->m_iStepLength[m_sCurrentParamIndex])
    {
        m_pRouteManager->SaveSchmaRouteConfig();
        ui->plainTextEdit_Show->appendPlainText("参数保存成功！");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("参数保存失败，计划长度必须等于目标长度！");
    }

}

