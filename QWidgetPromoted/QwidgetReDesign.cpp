#include "QwidgetReDesign.h"
#include "ui_QwidgetReDesign.h"

CQwidgetReDesign::CQwidgetReDesign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CQwidgetReDesign)
{
    ui->setupUi(this);

    m_pWidgetForModelImagePromoted = ui->widget_Modelshow;
    QString strModelImage = "D:/BZVisualInspect/Bin/SysConfig/PhoneModel.png";
    m_pWidgetForModelImagePromoted->InitModelImageFile(strModelImage);

    for(int i =0;i<80;i++)
    {
        m_pWidgetForModelImagePromoted->PushDefect((DEFECT_LOCATION_CODE)i);
    }
}

CQwidgetReDesign::~CQwidgetReDesign()
{
    delete ui;
}
