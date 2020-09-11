#ifndef DLGLIGHTPARAM_H
#define DLGLIGHTPARAM_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include "RouteManager.h"
namespace Ui {
class CDlgLightParam;
}

class CDlgLightParam : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgLightParam(QWidget *parent = 0,CRouteManager *pRouteManager=nullptr);
    ~CDlgLightParam();

private slots:
    void on_pushButton_Save_clicked();
    void ParamComboBoxChange(int index);
    void ModelComboBoxChange(int index);
    void FrameUpCheckChanged();
    void FrameDownCheckChanged();
    void FocusCheckChanged();
    void FrameUpCheckChanged1();
    void FrameDownCheckChanged1();
    void FocusCheckChanged1();
    void FrontExpoChanged();
    void FrontGainChanged();
    void NewExpoChanged();
    void NewGainChanged();
    void FlashExpoChanged();
    void FlashGainChanged();
private:
    void SetEditVisible(bool flag);
    Ui::CDlgLightParam *ui;
    CRouteManager* m_pRouteManager;
    short m_sCurrentParamIndex;
    short m_sCurrentSchmaModelIndex;
    QString m_qStr;
    QLineEdit *m_pLineEdit[13];
	QLabel *m_pQLabel[5];
    void UpdateChannelLineEdits(short ParamNum);
};

#endif // DLGLIGHTPARAM_H
