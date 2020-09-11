#ifndef ERTETE_H
#define ERTETE_H

#include <QtWidgets/QMainWindow>
#include "ui_ertete.h"

class ertete : public QMainWindow
{
    Q_OBJECT

public:
    ertete(QWidget *parent = 0);
    ~ertete();

private:
    Ui::erteteClass ui;
};

#endif // ERTETE_H
