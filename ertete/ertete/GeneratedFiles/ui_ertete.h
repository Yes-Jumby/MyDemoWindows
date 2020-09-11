/********************************************************************************
** Form generated from reading UI file 'ertete.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERTETE_H
#define UI_ERTETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_erteteClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *erteteClass)
    {
        if (erteteClass->objectName().isEmpty())
            erteteClass->setObjectName(QStringLiteral("erteteClass"));
        erteteClass->resize(600, 400);
        menuBar = new QMenuBar(erteteClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        erteteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(erteteClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        erteteClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(erteteClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        erteteClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(erteteClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        erteteClass->setStatusBar(statusBar);

        retranslateUi(erteteClass);

        QMetaObject::connectSlotsByName(erteteClass);
    } // setupUi

    void retranslateUi(QMainWindow *erteteClass)
    {
        erteteClass->setWindowTitle(QApplication::translate("erteteClass", "ertete", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class erteteClass: public Ui_erteteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERTETE_H
