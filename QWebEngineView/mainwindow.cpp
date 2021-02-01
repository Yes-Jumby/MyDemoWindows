#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),m_webView(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_webView = new QWebEngineView(this);
//    std::thread *pthread = new std::thread(&MainWindow::displayTest,this);
//    pthread->detach();
//    delete pthread;
    m_webView->load(QUrl("https://www.baidu.com/"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    m_webView->resize(this->size());
}

void MainWindow::displayTest()
{
    m_webView->load(QUrl("https://www.baidu.com/"));
}
