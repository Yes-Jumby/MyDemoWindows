#ifndef DLLPROJECTDIALOG_H
#define DLLPROJECTDIALOG_H

#include <QDialog>

#include "DllProject.h"
namespace Ui {
class DllProjectDialog;
}

class DllProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DllProjectDialog(QWidget *parent = 0);
    ~DllProjectDialog();

private slots:
    void on_pushButton_Test_clicked();

private:
    Ui::DllProjectDialog *ui;
    DllProject m_DllProject;
    QString m_qStr;
};

#endif // DLLPROJECTDIALOG_H
