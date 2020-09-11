#include "DlgLightParam.h"
#include "ui_DlgLightParam.h"

CDlgLightParam::CDlgLightParam(QWidget *parent,CRouteManager *pRouteManager) :
    QDialog(parent),
    m_pRouteManager(pRouteManager),
    ui(new Ui::CDlgLightParam)
{
    ui->setupUi(this);
    //设置窗口格式
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setAttribute(Qt::WA_DeleteOnClose);
    //初始化指针
    m_pLineEdit[0] = ui->lineEdit_Channel0;
    m_pLineEdit[1] = ui->lineEdit_Channel1;
    m_pLineEdit[2] = ui->lineEdit_Channel2;
    m_pLineEdit[3] = ui->lineEdit_Channel3;
    m_pLineEdit[4] = ui->lineEdit_Channel4;
    m_pLineEdit[5] = ui->lineEdit_Channel5;
    m_pLineEdit[6] = ui->lineEdit_Channel6;
    m_pLineEdit[7] = ui->lineEdit_Channel7;
    m_pLineEdit[8] = ui->lineEdit_Channel8;
    m_pLineEdit[9] = ui->lineEdit_Channel9;
    m_pLineEdit[10] = ui->lineEdit_Channel10;
    m_pLineEdit[11] = ui->lineEdit_Channel11;
    m_pLineEdit[12] = ui->lineEdit_Channel12;
	m_pQLabel[0] = ui->label;
	m_pQLabel[1] = ui->label_2;
	m_pQLabel[2] = ui->label_3;
	m_pQLabel[3] = ui->label_4;
	m_pQLabel[4] = ui->label_5;
    //模板级别
    m_sCurrentSchmaModelIndex = m_pRouteManager->m_iSchmaModelIndex;
    for(int i = 0;i < m_pRouteManager->m_listSchemaModelName.size();i++)
    {
        ui->comboBox_ModelIndex->addItem(m_pRouteManager->m_listSchemaModelName.at(i));
    }
    ui->comboBox_ModelIndex->setCurrentIndex(m_sCurrentSchmaModelIndex);
    connect(ui->comboBox_ModelIndex, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ this->ModelComboBoxChange(index);});
    //参数级别
    m_sCurrentParamIndex = 2;
    UpdateChannelLineEdits(m_sCurrentParamIndex);//显示电流
    ui->comboBox_ParamIndex->addItem("PulseWidth[us]");
    ui->comboBox_ParamIndex->addItem("PulseDelay[us]");
    ui->comboBox_ParamIndex->addItem("Current[A]");
    ui->comboBox_ParamIndex->addItem("RetriggerDelay[us]");
    ui->comboBox_ParamIndex->setCurrentIndex(m_sCurrentParamIndex);
    connect(ui->comboBox_ParamIndex, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ this->ParamComboBoxChange(index);});
    connect(ui->checkBox_EnableFrameUp,SIGNAL(stateChanged(int)),this, SLOT(FrameUpCheckChanged()));
    connect(ui->checkBox_EnableFrameDown,SIGNAL(stateChanged(int)),this, SLOT(FrameDownCheckChanged()));
    connect(ui->checkBox_EnableFocus,SIGNAL(stateChanged(int)),this, SLOT(FocusCheckChanged()));
    connect(ui->checkBox_EnableFrameUp1,SIGNAL(stateChanged(int)),this, SLOT(FrameUpCheckChanged1()));
    connect(ui->checkBox_EnableFrameDown1,SIGNAL(stateChanged(int)),this, SLOT(FrameDownCheckChanged1()));
    connect(ui->checkBox_EnableFocus1,SIGNAL(stateChanged(int)),this, SLOT(FocusCheckChanged1()));

    connect(ui->checkBox_EnableFrontExpo,SIGNAL(stateChanged(int)),this, SLOT(FrontExpoChanged()));
    connect(ui->checkBox_EnableFrontGain,SIGNAL(stateChanged(int)),this, SLOT(FrontGainChanged()));

    connect(ui->checkBox_EnableNewExpo,SIGNAL(stateChanged(int)),this, SLOT(NewExpoChanged()));
    connect(ui->checkBox_EnableNewGain,SIGNAL(stateChanged(int)),this, SLOT(NewGainChanged()));
    connect(ui->checkBox_EnableFlashExpo,SIGNAL(stateChanged(int)),this, SLOT(FlashExpoChanged()));
    connect(ui->checkBox_EnableFlashGain,SIGNAL(stateChanged(int)),this, SLOT(FlashGainChanged()));
	SetEditVisible(false);
}

CDlgLightParam::~CDlgLightParam()
{
    delete ui;
}
void CDlgLightParam::ParamComboBoxChange(int index)
{
    m_sCurrentParamIndex = index;
    UpdateChannelLineEdits(m_sCurrentParamIndex);
    m_qStr = tr("参数切换到%1！").arg(ui->comboBox_ParamIndex->currentText());
    ui->plainTextEdit_Show->appendPlainText(m_qStr);
}
void CDlgLightParam::ModelComboBoxChange(int index)
{
    if(index == 0)
    {
        SetEditVisible(true);
    }
    else
    {
        SetEditVisible(false);
    }
    m_sCurrentSchmaModelIndex = index;
    UpdateChannelLineEdits(m_sCurrentParamIndex);
    m_qStr = tr("模板切换到%1！").arg(ui->comboBox_ModelIndex->currentText());
    ui->plainTextEdit_Show->appendPlainText(m_qStr);
}
void CDlgLightParam::SetEditVisible(bool flag)
{
    if(flag)
    {
        for(int i = 0;i < 5;i++)
        {
            m_pLineEdit[i]->setVisible(true);
			m_pQLabel[i]->setVisible(true);
        }
    }
    else
    {
        for(int i = 0;i < 5;i++)
        {
            m_pLineEdit[i]->setVisible(false);
			m_pQLabel[i]->setVisible(false);
        }
    }
}
void CDlgLightParam::FrameUpCheckChanged()
{
    if (ui->checkBox_EnableFrameUp->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[1] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[1] = false;
    }
}
void CDlgLightParam::FrameDownCheckChanged()
{
    if (ui->checkBox_EnableFrameDown->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[2] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[2] = false;
    }
}
void CDlgLightParam::FocusCheckChanged()
{
    if (ui->checkBox_EnableFocus->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[0] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[0] = false;
    }
}

void CDlgLightParam::FrameUpCheckChanged1()
{
    if (ui->checkBox_EnableFrameUp1->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[1] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[1] = false;
    }
}
void CDlgLightParam::FrameDownCheckChanged1()
{
    if (ui->checkBox_EnableFrameDown1->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[2] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[2] = false;
    }
}
void CDlgLightParam::FocusCheckChanged1()
{
    if (ui->checkBox_EnableFocus1->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[0] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[0] = false;
    }
}
void CDlgLightParam::FrontExpoChanged()
{
    if (ui->checkBox_EnableFrontExpo->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[3] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[3] = false;
    }
}
void CDlgLightParam::FrontGainChanged()
{
    if (ui->checkBox_EnableFrontGain->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[3] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[3] = false;
    }
}
void CDlgLightParam::NewExpoChanged()
{
    if (ui->checkBox_EnableNewExpo->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[4] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[4] = false;
    }
}
void CDlgLightParam::NewGainChanged()
{
    if (ui->checkBox_EnableNewGain->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[4] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[4] = false;
    }
}
void CDlgLightParam::FlashExpoChanged()
{
    if (ui->checkBox_EnableFlashExpo->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[5] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[5] = false;
    }
}
void CDlgLightParam::FlashGainChanged()
{
    if (ui->checkBox_EnableFlashGain->isChecked())
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[5] = true;
    }
    else
    {
        m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[5] = false;
    }
}
void CDlgLightParam::UpdateChannelLineEdits(short ParamNum)
{
    switch (ParamNum)
    {
    case 0:
        for(int i = 0;i < 13 ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dPulseWidth);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    case 1:
        for(int i = 0;i < 13 ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dPulseDelay);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    case 2:
        for(int i = 0;i < 13 ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dCurrent);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    case 3:
        for(int i = 0;i < 13 ;i++)
        {
            m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dRetriggerDelay);
            m_pLineEdit[i]->setText(m_qStr);
        }
        break;
    default:
        break;
    }
    ui->checkBox_EnableFocus->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[0]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[0]);
	ui->lineEdit_FocusExposureTime->setText(m_qStr);
    ui->checkBox_EnableFocus1->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[0]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[0]);
    ui->lineEdit_FocusGain->setText(m_qStr);

    ui->checkBox_EnableFrameUp->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[1]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[1]);
    ui->lineEdit_FrameUpExposureTime->setText(m_qStr);
    ui->checkBox_EnableFrameUp1->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[1]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[1]);
    ui->lineEdit_FrameUpGain->setText(m_qStr);

    ui->checkBox_EnableFrameDown->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[2]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[2]);
    ui->lineEdit_FrameDownExposureTime->setText(m_qStr);
    ui->checkBox_EnableFrameDown1->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[2]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[2]);
    ui->lineEdit_FrameDownGain->setText(m_qStr);

    ui->checkBox_EnableFrontExpo->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[3]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[3]);
    ui->lineEdit_FrontExposureTime->setText(m_qStr);
    ui->checkBox_EnableFrontGain->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[3]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[3]);
    ui->lineEdit_FrontGain->setText(m_qStr);

    ui->checkBox_EnableNewExpo->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[4]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[4]);
    ui->lineEdit_NewExposureTime->setText(m_qStr);
    ui->checkBox_EnableNewGain->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[4]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[4]);
    ui->lineEdit_NewGain->setText(m_qStr);

    ui->checkBox_EnableFlashExpo->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bExposureValid[5]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[5]);
    ui->lineEdit_FlashExposureTime->setText(m_qStr);
    ui->checkBox_EnableFlashGain->setChecked(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).bGainValid[5]);
    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[5]);
    ui->lineEdit_FlashGain->setText(m_qStr);

    m_qStr = tr("%1").arg(m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecRSeeParam.at(0));
    ui->lineEdit_FocusLightIntensity->setText(m_qStr);

}
void CDlgLightParam::on_pushButton_Save_clicked()
{
    switch (m_sCurrentParamIndex)
    {
    case 0:
        for(int i = 0;i < 13 ;i++)
        {
            m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dPulseWidth = m_pLineEdit[i]->text().toDouble();
        }

        break;
    case 1:
        for(int i = 0;i < 13 ;i++)
        {
            m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dPulseDelay = m_pLineEdit[i]->text().toDouble();
        }
        break;
    case 2:
        for(int i = 0;i < 13 ;i++)
        {
            m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dCurrent = m_pLineEdit[i]->text().toDouble();
        }
        break;
    case 3:
        for(int i = 0;i < 13 ;i++)
        {
            m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecGardSoftParam.at(i).dRetriggerDelay = m_pLineEdit[i]->text().toDouble();
        }
        break;
    default:
        break;
    }
    for (int i = 0; i < 5;i++)
    {
        m_pRouteManager->m_dPulseWidth[i] = m_pRouteManager->m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dPulseWidth;
        m_pRouteManager->m_dPulseDelay[i] = m_pRouteManager->m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dPulseDelay;
        m_pRouteManager->m_dCurrent[i] = m_pRouteManager->m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dCurrent;
        m_pRouteManager->m_dRetriggerDelay[i] = m_pRouteManager->m_vecLightParamInfo.at(0).vecGardSoftParam.at(i).dRetriggerDelay;
        continue;
    }
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[1] = ui->lineEdit_FrameUpExposureTime->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[2] = ui->lineEdit_FrameDownExposureTime->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[0] = ui->lineEdit_FocusExposureTime->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[3] = ui->lineEdit_FrontExposureTime->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[4] = ui->lineEdit_NewExposureTime->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fExposureTime[5] = ui->lineEdit_FlashExposureTime->text().toFloat();

    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[1] = ui->lineEdit_FrameUpGain->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[2] = ui->lineEdit_FrameDownGain->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[0] = ui->lineEdit_FocusGain->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[3] = ui->lineEdit_FrontGain->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[4] = ui->lineEdit_NewGain->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).fGain[5] = ui->lineEdit_FlashGain->text().toFloat();
    m_pRouteManager->m_vecLightParamInfo.at(m_sCurrentSchmaModelIndex).vecRSeeParam.at(0) = ui->lineEdit_FocusLightIntensity->text().toInt();
    m_pRouteManager->SaveSchemaConfig(m_pRouteManager->m_listSchemaModelName.at(m_sCurrentSchmaModelIndex));
    ui->plainTextEdit_Show->appendPlainText("参数保存成功！");
}
