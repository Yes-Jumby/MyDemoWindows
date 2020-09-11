#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void SetDisplay(QString strDisplay);
public slots:
    void UpdateTime();
private:
    QTimer *pTimer;
    QDateTime dateTime;
    Ui::MyWidget *ui;

};

#endif // MYWIDGET_H
