#ifndef ROUTEMANAGE_H
#define ROUTEMANAGE_H

#include <QMainWindow>
#include "RouteManager.h"

namespace Ui {
class RouteManage;
}

class RouteManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RouteManage(QWidget *parent = 0);
    ~RouteManage();

private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_Check_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Init_clicked();

    void on_pushButton_ParamDlg_clicked();

    void on_pushButton_LightParamDlg_clicked();

    void on_pushButton_VelAccDlg_clicked();

    void on_pushButton_DebugDlg_clicked();

    void on_pushButton_ModelDlg_clicked();

private:
    Ui::RouteManage *ui;
    CRouteManager m_RouteManager;
};

#endif // ROUTEMANAGE_H
