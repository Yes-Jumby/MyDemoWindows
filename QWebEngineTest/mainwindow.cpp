#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_web1->setDisplayWeb(QUrl("https://www.baidu.com/"));
    ui->widget_web2->setDisplayWeb(QUrl("https://fanyi.baidu.com/"));
    ui->lineEdit_url->setText("https://www.csdn.net/");
    connect(this,SIGNAL(signalTest()),this,SLOT(on_signalTest()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_changeweb1_clicked()
{
    ui->widget_web1->setDisplayWeb(QUrl(ui->lineEdit_url->text()));
}

void MainWindow::on_pushButton_changeweb2_clicked()
{
    ui->widget_web2->setDisplayWeb(QUrl(ui->lineEdit_url->text()));
}

void MainWindow::on_pushButton_thread_clicked()
{
    std::thread *pthread = new std::thread(&MainWindow::threadTest,this);
    pthread->detach();
    delete pthread;

}
void MainWindow::threadTest()
{
    emit signalTest();
}
void MainWindow::on_signalTest()
{
    ui->widget_web2->setDisplayWeb(QUrl(ui->lineEdit_url->text()));
}
