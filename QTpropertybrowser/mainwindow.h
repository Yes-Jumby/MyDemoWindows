#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_valueChanged(QtProperty *property, const QVariant &value);

private:
    Ui::MainWindow *ui;
    int m_count;
    QMap<QtProperty*,QString>m_property_dic;
};

#endif // MAINWINDOW_H
