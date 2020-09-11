#include "QwidgetPromoted.h"
#include "ui_QwidgetPromoted.h"
#include <QDebug>
#pragma execution_character_set("utf-8")
QwidgetPromoted::QwidgetPromoted(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QwidgetPromoted)
{
    ui->setupUi(this);

//    m_pWidgetForModelImagePromoted = ui->widget_PromotedShow;
//    qDebug()<< "234";
//    QString strModelImage = "D:/BZVisualInspect/Bin/SysConfig/PhoneModel.png";
//    m_pWidgetForModelImagePromoted->InitModelImageFile(strModelImage);

//    for(int i =0;i<80;i++)
//    {
//        m_pWidgetForModelImagePromoted->PushDefect((DEFECT_LOCATION_CODE)i);
//    }
//    ui->horizontalLayout_3->setContentsMargins(0,0,0,0);
    //strModelImage = "D:/WOrks/Demo/QWidgetPromoted/Model.png";
//    QHBoxLayout *HLayout_Image = new QHBoxLayout(ui->widget_DirectShow);
//    HLayout_Image->setContentsMargins(0,0,0,0);
//    HLayout_Image->setSpacing(0);
//    m_pWidgetForModelImageDirectred1= std::make_shared<CQWidgetForModel>(ui->widget_DirectShow);
//    m_pWidgetForModelImageDirectred1->InitModelImageFile(strModelImage);
//    HLayout_Image->addWidget(m_pWidgetForModelImageDirectred1.get());
//    m_pWidgetForModelImageDirectred2= std::make_shared<CQWidgetForModel>(ui->widget_DirectShow);
//    m_pWidgetForModelImageDirectred2->InitModelImageFile(strModelImage);
//    HLayout_Image->addWidget(m_pWidgetForModelImageDirectred2.get());

//    HLayout_Image->setStretch(0,1);
//    HLayout_Image->setStretch(1,1);
//    ui->widget_5->SetDisplay("NG计数:103");
//    ui->widget_6->SetDisplay("上个产品：F0190213243");
//    ui->widget_7->SetDisplay("当前产品：F0190213244");
//    ui->widget_8->SetDisplay("下个产品：F0190213245");
}

QwidgetPromoted::~QwidgetPromoted()
{
    delete ui;
}
