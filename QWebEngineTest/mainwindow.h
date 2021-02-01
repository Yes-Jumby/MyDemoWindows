#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_changeweb1_clicked();

    void on_pushButton_changeweb2_clicked();

    void on_pushButton_thread_clicked();
    void on_signalTest();
signals:
    void signalTest();
private:
    Ui::MainWindow *ui;
    void threadTest();

};

#endif // MAINWINDOW_H
