#ifndef DLGROUTEMANAGE_H
#define DLGROUTEMANAGE_H

#include <QDialog>
#include "RouteManager.h"
namespace Ui {
class CDlgRouteManage;
}

class CDlgRouteManage : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgRouteManage(QWidget *parent = 0,CRouteManager *pRouteManager=nullptr);
    ~CDlgRouteManage();

private slots:
    void on_pushButton_FrontVel_clicked();

    void on_pushButton_FrontAcc_clicked();

    void on_pushButton_FrameVel_clicked();

    void on_pushButton_FrameAcc_clicked();

    void on_pushButton_UpDownCameraVel_clicked();

    void on_pushButton_UpDownCameraAcc_clicked();

    void on_pushButton_BackVel_clicked();

    void on_pushButton_BackAcc_clicked();

    void on_pushButton_LineVel_clicked();

    void on_pushButton_LineAcc_clicked();

private:
    Ui::CDlgRouteManage *ui;
    CRouteManager *m_pRouteManager;
    QString m_qStr;
};

#endif // DLGROUTEMANAGE_H
