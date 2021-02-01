#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *);
private:
    QWebEngineView* m_webView;
    Ui::MainWindow *ui;
    void displayTest();
};

#endif // MAINWINDOW_H
