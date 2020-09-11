#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("应用");
    ui->comboBox->addItem("禁用");
    ui->comboBox->setCurrentIndex(1);
    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){ this->ComboBoxChange(index);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ComboBoxChange(int index)
{
    QString str = QObject::tr("%1").arg(index);
    ui->textEdit->setText(str);
}
