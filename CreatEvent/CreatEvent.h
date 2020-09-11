#ifndef CREATEVENT_H
#define CREATEVENT_H

#include <QDialog>
#include <Windows.h>
#include <QtConcurrent>
namespace Ui {
class CreatEvent;
}

class CreatEvent : public QDialog
{
    Q_OBJECT

public:
    explicit CreatEvent(QWidget *parent = 0);
    ~CreatEvent();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton__SetEvent_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_PulseEvent_clicked();

    void on_pushButton_Wait_clicked();

    void on_pushButton_Close_clicked();
    void DisplaySignalforSingleObjectReturn(DWORD value,int index);
signals:
    void SignalforSingleObjectReturn(DWORD value,int index);
private:
    void FunWaitForCornelObject();
    Ui::CreatEvent *ui;
    HANDLE m_Handle;
    int m_iThreadNum;
    int m_iEvent;
    int m_iIndex;
};

#endif // CREATEVENT_H
