#ifndef ROUTEMANAGE_H
#define ROUTEMANAGE_H

#include <QMainWindow>
#include "RouteManager.h"
#include <QTimer>
#include <QLineEdit>
namespace Ui {
class RouteManage;
}
enum e_RouteManageParam
{
    eRMP_Path_PutPhoneOnAxis,
    eRMP_Path_Lisener,
    eRMP_Path_Frame_1,                         //[24 7296]且必须为4的倍数
    eRMP_Path_Frame_2,
    eRMP_Path_Frame_3,
    eRMP_Path_Frame_4,
    eRMP_Path_FrameCorner_1,
    eRMP_Path_FrameCorner_2,
    eRMP_Path_FrameCorner_3,
    eRMP_Path_FrameCorner_4,
    eRMP_Path_CylinderCamera,
    eRMP_Path_Cylinder,
    eRMP_Path_FocusCamera,
    eRMP_Path_Flash,
    eRMP_Path_Back,
    eRMP_Path_PutPhoneOut,
    eRMP_Path_NULL,
};
class RouteManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RouteManage(QWidget *parent = 0);
    ~RouteManage();

private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_ParamDlg_clicked();

    void on_pushButton_VelAccDlg_clicked();

    void on_pushButton_DebugDlg_clicked();

    void on_pushButton_PutPhoneOnAxis_clicked();

    void on_pushButton_Path_Frame_1_clicked();

    void on_pushButton_Path_Frame_2_clicked();

    void on_pushButton_Path_Frame_3_clicked();

    void on_pushButton_Path_Frame_4_clicked();

    void on_pushButton_Path_FrameCorner_1_clicked();

    void on_pushButton_Path_FrameCorner_2_clicked();

    void on_pushButton_Path_FrameCorner_3_clicked();

    void on_pushButton_Path_FrameCorner_4_clicked();

    void on_pushButton_CameraFocus_clicked();

    void on_pushButton_PutPhoneOut_clicked();

    //定时器
    void TimeOut();
    void on_pushButton_FrameCameraOn_clicked();

    void on_pushButton_FocusCameraOn_clicked();

    void on_pushButton_P2P_clicked();
    void AxisNumComboBoxChange(int index);
    void on_pushButton_Save_clicked();

    void on_pushButton_Cylinder_clicked();

    void on_pushButton_Lisener_clicked();

    void on_pushButton_CylinderCamera_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_CyliderCameraOn_clicked();

    void on_pushButton_Flash_clicked();

private:
    Ui::RouteManage *ui;
    CRouteManager m_RouteManager;
    QTimer *m_pTime;
    QString m_qStr;
    double m_fAxisPos[3];
    QLineEdit *m_pAxisPos[3];
    bool m_bFrameCameraTrigerOn;
    bool m_bFocusCameraTrigerOn;
    bool m_bCyliderCameraTrigerOn;
    bool m_bFlag[3];
    e_RouteManageParam m_eRouteManageParam;
    int m_iAxisIndex;
    bool SaveRouteParam();
    int m_iVel;
    int m_iAcc;
};

#endif // ROUTEMANAGE_H
