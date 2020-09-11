#include "RouteManage.h"
#include "ui_RouteManage.h"

#pragma execution_character_set("utf-8")

RouteManage::RouteManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RouteManage)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(tr(":/Res/imac.ico")));//设置应用程序图标
    //初始化成员变量
    m_iVel = 100;
    m_iAcc = 10;
    QString str = QString("%1").arg(m_iVel);
    ui->lineEdit_Vel->setText(QString("%1").arg(m_iVel));
    ui->lineEdit_Acc->setText(QString("%1").arg(m_iAcc));
    m_iAxisIndex = 0;
    m_bFrameCameraTrigerOn = false;
    m_bFocusCameraTrigerOn = false;
    m_bCyliderCameraTrigerOn = false;
    memset(m_fAxisPos,0,3*sizeof(double));
    memset(m_bFlag,0,3*sizeof(bool));
    m_pAxisPos[0] = ui->lineEdit_Pos_Axis_1;
    m_pAxisPos[1] = ui->lineEdit_Pos_Axis_2;
    m_pAxisPos[2] = ui->lineEdit_Pos_Axis_3;
    //定时器
    m_pTime = new QTimer(this);
    connect(m_pTime,&QTimer::timeout,this,&RouteManage::TimeOut);
    //复选框
    ui->comboBox_AxisNum->addItem("机台X轴");
    ui->comboBox_AxisNum->addItem("机台Y轴");
    ui->comboBox_AxisNum->addItem("机台Z轴");
    ui->comboBox_AxisNum->setCurrentIndex(m_iAxisIndex);
    connect(ui->comboBox_AxisNum, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ this->AxisNumComboBoxChange(index);});
    //初始化按钮名字
    ui->pushButton_FocusCameraOn->setText("开始触发");
    ui->pushButton_FrameCameraOn->setText("开始触发");
    ui->pushButton_CyliderCameraOn->setText("开始触发");
    ui->lineEdit_P2p_Length->setText("1000");
    //初始化
    if(m_RouteManager.InitRoutePath("D:/BZVisualInspect/UserData/Mission","D:/BZVisualInspect/Bin/SysConfig",false))
    {
        ui->plainTextEdit_Show->appendPlainText("初始化成功！");
        m_pTime->start(800);
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("初始化失败，请关闭软件！");
    }
}

RouteManage::~RouteManage()
{
    m_RouteManager.ReleaseRoute();
    delete ui;
}
void RouteManage::AxisNumComboBoxChange(int index)
{
    m_iAxisIndex = index;
    m_qStr = tr("切换到%1！").arg(ui->comboBox_AxisNum->currentText());
    ui->plainTextEdit_Show->appendPlainText(m_qStr);
}
//定时器
void RouteManage::TimeOut()
{
    /*更新所有轴的状态*/
    for(int i = 0;i < 3;i++)
    {
            m_RouteManager.m_MotionCard.AxisEncPos(m_fAxisPos[i],i+1);
            m_qStr = QString("%1").arg(m_fAxisPos[i]);
            m_pAxisPos[i]->setText(m_qStr);
    }
    //中框相机
    if(m_bFrameCameraTrigerOn)
    {
        if(m_bFlag[0])
        {
            m_RouteManager.m_MotionCard.SetDoOutput(12,0,12);
            m_bFlag[0] = false;
        }
        else
        {
            m_RouteManager.m_MotionCard.SetDoOutput(12,1,12);
            m_bFlag[0] = true;
        }
    }
    //摄像头相机
    if(m_bFocusCameraTrigerOn)
    {
        if(m_bFlag[1])
        {
            m_RouteManager.m_MotionCard.SetDoOutput(15,1,12);
            m_bFlag[1] = false;
        }
        else
        {
            m_RouteManager.m_MotionCard.SetDoOutput(15,0,12);
            m_bFlag[1] = true;
        }
    }
    //听筒相机
    if(m_bCyliderCameraTrigerOn)
    {
        if(m_bFlag[2])
        {
            m_RouteManager.m_MotionCard.SetDoOutput(14,1,12);//
            m_bFlag[2] = false;
        }
        else
        {
            m_RouteManager.m_MotionCard.SetDoOutput(14,0,12);//
            m_bFlag[2] = true;
        }
    }
}
void RouteManage::on_pushButton_Start_clicked()
{
    if(m_RouteManager.RouteStart())
    {
		m_eRouteManageParam = eRMP_Path_NULL;
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
		m_eRouteManageParam = eRMP_Path_NULL;
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
		m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("停止成功!");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("停止失败!");
    }
}

void RouteManage::on_pushButton_ParamDlg_clicked()
{
    m_RouteManager.CallRouteParamDlg();
}

void RouteManage::on_pushButton_VelAccDlg_clicked()
{
    m_RouteManager.CallRouteManageDlg();
}

void RouteManage::on_pushButton_DebugDlg_clicked()
{
    m_RouteManager.CallMotionDebugDlg();
}

void RouteManage::on_pushButton_PutPhoneOnAxis_clicked()
{
    if(m_RouteManager.PutPhoneOnAxis())
    {
        m_eRouteManageParam = eRMP_Path_PutPhoneOnAxis;
        ui->plainTextEdit_Show->appendPlainText("开始检测成功！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("开始检测失败！");
    }
}
void RouteManage::on_pushButton_Lisener_clicked()
{
    if(m_RouteManager.Path_Lisener())
    {
        m_eRouteManageParam = eRMP_Path_Lisener;
        ui->plainTextEdit_Show->appendPlainText("走到前部听筒！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到前部听筒失败！");
    }

}
void RouteManage::on_pushButton_Path_Frame_1_clicked()
{
    if(m_RouteManager.Path_Frame_1())
    {
        m_eRouteManageParam = eRMP_Path_Frame_1;
        ui->plainTextEdit_Show->appendPlainText("走到中框1！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到中框1失败！");
    }
}

void RouteManage::on_pushButton_Path_Frame_2_clicked()
{
    if(m_RouteManager.Path_Frame_2())
    {
        m_eRouteManageParam = eRMP_Path_Frame_2;
        ui->plainTextEdit_Show->appendPlainText("走到中框2！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到中框2失败！");
    }
}

void RouteManage::on_pushButton_Path_Frame_3_clicked()
{
    if(m_RouteManager.Path_Frame_3())
    {
        m_eRouteManageParam = eRMP_Path_Frame_3;
        ui->plainTextEdit_Show->appendPlainText("走到中框3！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到中框3失败！");
    }
}

void RouteManage::on_pushButton_Path_Frame_4_clicked()
{
    if(m_RouteManager.Path_Frame_4())
    {
        m_eRouteManageParam = eRMP_Path_Frame_4;
        ui->plainTextEdit_Show->appendPlainText("走到中框4！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到中框4失败！");
    }
}

void RouteManage::on_pushButton_Path_FrameCorner_1_clicked()
{
    if(m_RouteManager.Path_FrameCorner_1())
    {
        m_eRouteManageParam = eRMP_Path_FrameCorner_1;
        ui->plainTextEdit_Show->appendPlainText("走到R角1！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到R角1失败！");
    }
}

void RouteManage::on_pushButton_Path_FrameCorner_2_clicked()
{
    if(m_RouteManager.Path_FrameCorner_2())
    {
        m_eRouteManageParam = eRMP_Path_FrameCorner_2;
        ui->plainTextEdit_Show->appendPlainText("走到R角2！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到R角2失败！");
    }
}

void RouteManage::on_pushButton_Path_FrameCorner_3_clicked()
{
    if(m_RouteManager.Path_FrameCorner_3())
    {
        m_eRouteManageParam = eRMP_Path_FrameCorner_3;
        ui->plainTextEdit_Show->appendPlainText("走到R角3！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到R角3失败！");
    }
}

void RouteManage::on_pushButton_Path_FrameCorner_4_clicked()
{
    if(m_RouteManager.Path_FrameCorner_4())
    {
        m_eRouteManageParam = eRMP_Path_FrameCorner_4;
        ui->plainTextEdit_Show->appendPlainText("走到R角4！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到R角4失败！");
    }
}

void RouteManage::on_pushButton_CylinderCamera_clicked()
{
    if(m_RouteManager.Path_CylinderCamera())
    {
        m_eRouteManageParam = eRMP_Path_CylinderCamera;
        ui->plainTextEdit_Show->appendPlainText("走到前置听筒！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到前置听筒失败！");
    }
}
void RouteManage::on_pushButton_Cylinder_clicked()
{
    if(m_RouteManager.Path_Cylinder())
    {
        m_eRouteManageParam = eRMP_Path_FocusCamera;
        ui->plainTextEdit_Show->appendPlainText("走到翻转机构！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到翻转机构失败！");
    }
}
void RouteManage::on_pushButton_CameraFocus_clicked()
{
    if(m_RouteManager.Path_CameraFocus())
    {
        m_eRouteManageParam = eRMP_Path_FocusCamera;
        ui->plainTextEdit_Show->appendPlainText("走到摄像头！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到摄像头失败！");
    }
}

void RouteManage::on_pushButton_Flash_clicked()
{
    if(m_RouteManager.Path_Flash())
    {
        m_eRouteManageParam = eRMP_Path_Flash;
        ui->plainTextEdit_Show->appendPlainText("走到闪光灯！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到闪光灯失败！");
    }
}
void RouteManage::on_pushButton_Back_clicked()
{
    if(m_RouteManager.Path_Back())
    {
        m_eRouteManageParam = eRMP_Path_Back;
        ui->plainTextEdit_Show->appendPlainText("走到背面！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到背面失败！");
    }
}
void RouteManage::on_pushButton_PutPhoneOut_clicked()
{
    if(m_RouteManager.PutPhoneOut())
    {
        m_eRouteManageParam = eRMP_Path_PutPhoneOut;
        ui->plainTextEdit_Show->appendPlainText("走到出口！");
    }
    else
    {
        m_eRouteManageParam = eRMP_Path_NULL;
        ui->plainTextEdit_Show->appendPlainText("走到出口失败！");
    }
}

void RouteManage::on_pushButton_FrameCameraOn_clicked()
{
    if(!m_bFrameCameraTrigerOn)
    {
        m_bFrameCameraTrigerOn = true;
        m_bFlag[0] = true;
        m_RouteManager.m_MotionCard.SetDoOutput(12,1,12);
        ui->pushButton_FrameCameraOn->setText("停止触发");
    }
    else
    {
        m_bFrameCameraTrigerOn = false;
        m_bFlag[0] = false;
        m_RouteManager.m_MotionCard.SetDoOutput(12,0,12);
        ui->pushButton_FrameCameraOn->setText("开始触发");
    }
}

void RouteManage::on_pushButton_FocusCameraOn_clicked()
{
    if(!m_bFocusCameraTrigerOn)
    {
        m_bFocusCameraTrigerOn = true;
        m_bFlag[1] = true;
        m_RouteManager.m_MotionCard.SetDoOutput(15,0,12);
        ui->pushButton_FocusCameraOn->setText("停止触发");
    }
    else
    {
        m_bFocusCameraTrigerOn = false;
        m_bFlag[1] = false;
        m_RouteManager.m_MotionCard.SetDoOutput(15,1,12);
        ui->pushButton_FocusCameraOn->setText("开始触发");
    }
}

void RouteManage::on_pushButton_CyliderCameraOn_clicked()
{
    if(!m_bCyliderCameraTrigerOn)
    {
        m_bCyliderCameraTrigerOn = true;
        m_bFlag[2] = true;
        m_RouteManager.m_MotionCard.SetDoOutput(14,0,12);//
        ui->pushButton_CyliderCameraOn->setText("停止触发");
    }
    else
    {
        m_bCyliderCameraTrigerOn = false;
        m_bFlag[2] = false;
        m_RouteManager.m_MotionCard.SetDoOutput(14,1,12);//
        ui->pushButton_CyliderCameraOn->setText("开始触发");
    }
}

void RouteManage::on_pushButton_P2P_clicked()
{
    double x = m_fAxisPos[0];
    double y = m_fAxisPos[1];
    double z = m_fAxisPos[2];
    switch (m_iAxisIndex)
    {
    case 0:
        x = m_fAxisPos[0] + ui->lineEdit_P2p_Length->text().toDouble();
        break;
    case 1:
        y = m_fAxisPos[1] + ui->lineEdit_P2p_Length->text().toDouble();
        break;
    case 2:
        z = m_fAxisPos[2] + ui->lineEdit_P2p_Length->text().toDouble();
        break;
    default:
        break;
    }
    m_iVel = ui->lineEdit_Vel->text().toInt();
    m_iAcc = ui->lineEdit_Acc->text().toInt();
    m_RouteManager.Path_Move(x,y,z,m_iVel,m_iAcc);
}

void RouteManage::on_pushButton_Save_clicked()
{
    if(SaveRouteParam())
    {
        ui->plainTextEdit_Show->appendPlainText("保存参数成功！");
    }
    else
    {
        ui->plainTextEdit_Show->appendPlainText("保存参数失败！");
    }
}

bool RouteManage::SaveRouteParam()
{
    switch (m_eRouteManageParam)
    {
    case eRMP_Path_PutPhoneOnAxis:
        m_RouteManager.m_iFrontOffSetY = m_fAxisPos[1] + 4016;
        break;
    case eRMP_Path_Lisener:
        m_RouteManager.m_iLisenerX = m_fAxisPos[0];
        m_RouteManager.m_iLisenerY = m_fAxisPos[1];
        //m_RouteManager.m_iLisenerZ = m_fAxisPos[2];
        break;
    case eRMP_Path_Frame_1:
        m_RouteManager.m_iFrameOffSetY1 = m_fAxisPos[1] - (m_RouteManager.m_MyLength - m_RouteManager.m_iWidth / 2);
        m_RouteManager.m_iFrameOffSetZ1 = m_fAxisPos[2];
        break;
    case eRMP_Path_Frame_2:
        m_RouteManager.m_iFrameOffSetY2 = m_fAxisPos[1] - (m_RouteManager.m_MyLength - m_RouteManager.m_iLong / 2);
        m_RouteManager.m_iFrameOffSetZ2 = m_fAxisPos[2] + m_RouteManager.m_iCircle14;
        break;
    case eRMP_Path_Frame_3:
        m_RouteManager.m_iFrameOffSetY3 = m_fAxisPos[1] - (m_RouteManager.m_MyLength - m_RouteManager.m_iWidth / 2);
        m_RouteManager.m_iFrameOffSetZ3 = m_fAxisPos[2] + 2*m_RouteManager.m_iCircle14;
        break;
    case eRMP_Path_Frame_4:
        m_RouteManager.m_iFrameOffSetY4 = m_fAxisPos[1] - (m_RouteManager.m_MyLength - m_RouteManager.m_iLong / 2);
        m_RouteManager.m_iFrameOffSetZ4 = m_fAxisPos[2] + 3*m_RouteManager.m_iCircle14;
        break;
    case eRMP_Path_FrameCorner_1:
        m_RouteManager.m_iFrameCornerOffSetX1 = m_fAxisPos[0];
        m_RouteManager.m_iFrameCornerOffSetY1 = m_fAxisPos[1];
        m_RouteManager.m_iFrameCornerOffSetZ1 = m_fAxisPos[2] + m_RouteManager.m_iCircle14/2;
        break;
    case eRMP_Path_FrameCorner_2:
        m_RouteManager.m_iFrameCornerOffSetX2 = m_fAxisPos[0];
        m_RouteManager.m_iFrameCornerOffSetY2 = m_fAxisPos[1];
        m_RouteManager.m_iFrameCornerOffSetZ2 = m_fAxisPos[2] + m_RouteManager.m_iCircle14 + m_RouteManager.m_iCircle14/2;
        break;
    case eRMP_Path_FrameCorner_3:
        m_RouteManager.m_iFrameCornerOffSetX3 = m_fAxisPos[0];
        m_RouteManager.m_iFrameCornerOffSetY3 = m_fAxisPos[1];
        m_RouteManager.m_iFrameCornerOffSetZ3 = m_fAxisPos[2] + 2*m_RouteManager.m_iCircle14 + m_RouteManager.m_iCircle14/2;
        break;
    case eRMP_Path_FrameCorner_4:
        m_RouteManager.m_iFrameCornerOffSetX4 = m_fAxisPos[0];
        m_RouteManager.m_iFrameCornerOffSetY4 = m_fAxisPos[1];
        m_RouteManager.m_iFrameCornerOffSetZ4 = m_fAxisPos[2] + 3*m_RouteManager.m_iCircle14 + m_RouteManager.m_iCircle14/2;
        break;
    case eRMP_Path_CylinderCamera:
        m_RouteManager.m_iCylinderCameraX = m_fAxisPos[0];
        m_RouteManager.m_iCylinderCameraY = m_fAxisPos[1];
        //m_RouteManager.m_iLisenerZ = m_fAxisPos[2];
        break;
    case eRMP_Path_Cylinder:
        m_RouteManager.m_iCylinderOffSetX = m_fAxisPos[0] - m_RouteManager.m_iP4;
        m_RouteManager.m_iCylinderOffSetY = m_fAxisPos[1];
        m_RouteManager.m_iCylinderOffSetZ = m_fAxisPos[2] + 3*m_RouteManager.m_iCircle14;
        break;
    case eRMP_Path_FocusCamera:
        m_RouteManager.m_iCameraOffSetX = m_fAxisPos[0] - (m_RouteManager.m_iP2 - m_RouteManager.m_iLong/2 + m_RouteManager.m_iLightOpen+7484);
        m_RouteManager.m_iCameraOffSetY = m_fAxisPos[1];
        m_RouteManager.m_iCameraOffSetZ = m_fAxisPos[2] + 4*m_RouteManager.m_iCircle14;
        break;
    case eRMP_Path_Flash:
        m_RouteManager.m_iFlashOffSetX = m_fAxisPos[0];
        m_RouteManager.m_iFlashOffSetY = m_fAxisPos[1];
        m_RouteManager.m_iCameraOffSetZ = m_fAxisPos[2] + 4*m_RouteManager.m_iCircle14;
        break;
    case eRMP_Path_Back:
        m_RouteManager.m_iBackOffSetY = m_fAxisPos[1] + 3696;
        break;
    default:
        return false;
        break;
    }
    return m_RouteManager.SaveSchmaRouteConfig();
}


