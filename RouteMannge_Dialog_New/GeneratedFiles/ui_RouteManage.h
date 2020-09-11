/********************************************************************************
** Form generated from reading UI file 'RouteManage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTEMANAGE_H
#define UI_ROUTEMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RouteManage
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Reset;
    QPushButton *pushButton_Check;
    QPushButton *pushButton_Stop;
    QPlainTextEdit *plainTextEdit_Show;
    QPushButton *pushButton_Init;
    QPushButton *pushButton_ParamDlg;
    QPushButton *pushButton_LightParamDlg;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RouteManage)
    {
        if (RouteManage->objectName().isEmpty())
            RouteManage->setObjectName(QStringLiteral("RouteManage"));
        RouteManage->resize(688, 434);
        centralWidget = new QWidget(RouteManage);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(190, 190, 101, 41));
        pushButton_Reset = new QPushButton(centralWidget);
        pushButton_Reset->setObjectName(QStringLiteral("pushButton_Reset"));
        pushButton_Reset->setGeometry(QRect(190, 260, 101, 41));
        pushButton_Check = new QPushButton(centralWidget);
        pushButton_Check->setObjectName(QStringLiteral("pushButton_Check"));
        pushButton_Check->setGeometry(QRect(380, 190, 101, 41));
        pushButton_Stop = new QPushButton(centralWidget);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setGeometry(QRect(50, 260, 101, 41));
        plainTextEdit_Show = new QPlainTextEdit(centralWidget);
        plainTextEdit_Show->setObjectName(QStringLiteral("plainTextEdit_Show"));
        plainTextEdit_Show->setGeometry(QRect(60, 20, 561, 131));
        pushButton_Init = new QPushButton(centralWidget);
        pushButton_Init->setObjectName(QStringLiteral("pushButton_Init"));
        pushButton_Init->setGeometry(QRect(50, 190, 101, 41));
        pushButton_ParamDlg = new QPushButton(centralWidget);
        pushButton_ParamDlg->setObjectName(QStringLiteral("pushButton_ParamDlg"));
        pushButton_ParamDlg->setGeometry(QRect(380, 260, 101, 41));
        pushButton_LightParamDlg = new QPushButton(centralWidget);
        pushButton_LightParamDlg->setObjectName(QStringLiteral("pushButton_LightParamDlg"));
        pushButton_LightParamDlg->setGeometry(QRect(520, 260, 101, 41));
        RouteManage->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RouteManage);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 688, 23));
        RouteManage->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RouteManage);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RouteManage->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RouteManage);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RouteManage->setStatusBar(statusBar);

        retranslateUi(RouteManage);

        QMetaObject::connectSlotsByName(RouteManage);
    } // setupUi

    void retranslateUi(QMainWindow *RouteManage)
    {
        RouteManage->setWindowTitle(QApplication::translate("RouteManage", "RouteManage", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("RouteManage", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_Reset->setText(QApplication::translate("RouteManage", "\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_Check->setText(QApplication::translate("RouteManage", "\345\274\200\345\247\213\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_Stop->setText(QApplication::translate("RouteManage", "\345\201\234\346\255\242", Q_NULLPTR));
        pushButton_Init->setText(QApplication::translate("RouteManage", "\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        pushButton_ParamDlg->setText(QApplication::translate("RouteManage", "\345\217\202\346\225\260\350\256\276\347\275\256\347\225\214\351\235\242", Q_NULLPTR));
        pushButton_LightParamDlg->setText(QApplication::translate("RouteManage", "\345\205\211\346\272\220\350\256\276\347\275\256\347\225\214\351\235\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RouteManage: public Ui_RouteManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTEMANAGE_H
