#include "DllProjectDialog.h"
#include "ui_DllProjectDialog.h"

DllProjectDialog::DllProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DllProjectDialog)
{
    ui->setupUi(this);

    ui->lineEdit_Type->setText("0");
    ui->lineEdit_Value->setText("1");
}

DllProjectDialog::~DllProjectDialog()
{
    delete ui;
}

void DllProjectDialog::on_pushButton_Test_clicked()
{

    m_qStr = QObject::tr("%1").arg(m_DllProject.MyCheck(ui->lineEdit_Type->text().toInt(),ui->lineEdit_Value->text().toInt()));
    ui->textEdit->setText(m_qStr);
}
