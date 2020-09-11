#ifndef DLGROUTEPARAM_H
#define DLGROUTEPARAM_H

#include <QDialog>
#include "RouteManager.h"
#include <QLineEdit>
namespace Ui {
class DlgRouteParam;
}

class CDlgRouteParam : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgRouteParam(QWidget *parent = 0,CRouteManager *pRouteManager=nullptr);
    ~CDlgRouteParam();

private slots:
    void on_pushButton_P1_clicked();

    void on_pushButton_P2_clicked();

    void on_pushButton_P3_clicked();

    void on_pushButton_P4_clicked();

    void on_pushButton_P5_clicked();

    void on_pushButton_FrontGrat_clicked();

    void on_pushButton_BackGrat_clicked();

    void on_pushButton_LightOpen_clicked();

    void on_pushButton_Circle14_clicked();

    void on_pushButton_RunBackOffSetY_clicked();

    void on_pushButton_PageIndex0_clicked();

    void on_pushButton_PageIndex1_clicked();

    void on_pushButton_Long_clicked();

    void on_pushButton_Width_clicked();

    void on_pushButton_FrontBackImageHeight_clicked();

    void on_pushButton_ResetPointX_clicked();

    void on_pushButton_ResetPointY_clicked();

    void on_pushButton_ResetPointZ_clicked();

    void on_pushButton_GetPointX_clicked();

    void on_pushButton_GetPointY_clicked();

    void on_pushButton_GetPointZ_clicked();

    void on_pushButton_PageIndex2_clicked();

    void on_pushButton_FrontOffSetX_clicked();

    void on_pushButton_FrontOffSetY_clicked();

    void on_pushButton_FrontOffSetZ_clicked();

    void on_pushButton_PageIndex3_clicked();

    void on_pushButton_FrameOffSetX1_clicked();

    void on_pushButton_FrameOffSetY1_clicked();

    void on_pushButton_FrameOffSetZ1_clicked();

    void on_pushButton_FrameOffSetX2_clicked();

    void on_pushButton_FrameOffSetY2_clicked();

    void on_pushButton_FrameOffSetZ2_clicked();

    void on_pushButton_FrameOffSetX3_clicked();

    void on_pushButton_FrameOffSetY3_clicked();

    void on_pushButton_FrameOffSetZ3_clicked();

    void on_pushButton_FrameOffSetX4_clicked();

    void on_pushButton_FrameOffSetY4_clicked();

    void on_pushButton_FrameOffSetZ4_clicked();

    void on_pushButton_FrameCornerOffSetX1_clicked();

    void on_pushButton_FrameCornerOffSetY1_clicked();

    void on_pushButton_FrameCornerOffSetZ1_clicked();

    void on_pushButton_FrameCornerOffSetX2_clicked();

    void on_pushButton_FrameCornerOffSetY2_clicked();

    void on_pushButton_FrameCornerOffSetZ2_clicked();

    void on_pushButton_FrameCornerOffSetX3_clicked();

    void on_pushButton_FrameCornerOffSetY3_clicked();

    void on_pushButton_FrameCornerOffSetZ3_clicked();

    void on_pushButton_FrameCornerOffSetX4_clicked();

    void on_pushButton_FrameCornerOffSetY4_clicked();

    void on_pushButton_FrameCornerOffSetZ4_clicked();

    void on_pushButton_FrameStep_clicked();

    void on_pushButton_CylinderOffSetX_clicked();

    void on_pushButton_CylinderOffSetY_clicked();

    void on_pushButton_CylinderOffSetZ_clicked();

    void on_pushButton_CameraOffSetX_clicked();

    void on_pushButton_CameraOffSetY_clicked();

    void on_pushButton_CameraOffSetZ_clicked();

    void on_pushButton_PageIndex4_clicked();

    void on_pushButton_PageIndex5_clicked();

    void on_pushButton_BackOffSetX_clicked();

    void on_pushButton_BackOffSetY_clicked();

    void on_pushButton_BackOffSetZ_clicked();

    void on_pushButton_PageIndex6_clicked();

    void on_pushButton_PageIndex7_clicked();

    void ComboBoxChange(int index);
    void on_pushButton_StepCount_clicked();

    void on_pushButton_FrameStepSave_clicked();

    void on_pushButton_BackOffSetX1_clicked();

    void on_pushButton_BackOffSetY1_clicked();

    void on_pushButton_BackOffSetZ1_clicked();

private:
    Ui::DlgRouteParam *ui;
    CRouteManager *m_pRouteManager;
    QString m_qStr;
    QLineEdit *m_pLineEdit[21];
    short m_sCurrentParamIndex;
    void UpdateFrameStepLineEdits(short ParamNum);//显示电流
    int GetSum(short ParamNum);
};

#endif // DLGROUTEPARAM_H
