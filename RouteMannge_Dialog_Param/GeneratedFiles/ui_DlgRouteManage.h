/********************************************************************************
** Form generated from reading UI file 'DlgRouteManage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGROUTEMANAGE_H
#define UI_DLGROUTEMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CDlgRouteManage
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEdit_FrontAcc;
    QPushButton *pushButton_FrontAcc;
    QPushButton *pushButton_FrontVel;
    QLineEdit *lineEdit_FrontVel;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_FrameAcc;
    QLineEdit *lineEdit_FrameVel;
    QPushButton *pushButton_FrameAcc;
    QPushButton *pushButton_FrameVel;
    QPushButton *pushButton_FrameCornerAcc;
    QPushButton *pushButton_FrameCornerVel;
    QLineEdit *lineEdit_FrameCornerVel;
    QLineEdit *lineEdit_FrameCornerAcc;
    QGroupBox *groupBox_3;
    QLineEdit *lineEdit_UpDownCameraAcc;
    QLineEdit *lineEdit_UpDownCameraVel;
    QPushButton *pushButton_UpDownCameraAcc;
    QPushButton *pushButton_UpDownCameraVel;
    QGroupBox *groupBox_4;
    QLineEdit *lineEdit_BackAcc;
    QLineEdit *lineEdit_BackVel;
    QPushButton *pushButton_BackAcc;
    QPushButton *pushButton_BackVel;
    QGroupBox *groupBox_5;
    QLineEdit *lineEdit_LineAcc;
    QLineEdit *lineEdit_LineVel;
    QPushButton *pushButton_LineAcc;
    QPushButton *pushButton_LineVel;
    QPlainTextEdit *plainTextEdit_Show;
    QCheckBox *checkBox_EnableCheckDoor;
    QGroupBox *groupBox_6;
    QCheckBox *checkBox_EnableFloodLight;
    QComboBox *comboBox_ModelIndex;
    QGroupBox *groupBox_7;

    void setupUi(QDialog *CDlgRouteManage)
    {
        if (CDlgRouteManage->objectName().isEmpty())
            CDlgRouteManage->setObjectName(QStringLiteral("CDlgRouteManage"));
        CDlgRouteManage->resize(882, 671);
        groupBox = new QGroupBox(CDlgRouteManage);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 90, 241, 141));
        groupBox->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_FrontAcc = new QLineEdit(groupBox);
        lineEdit_FrontAcc->setObjectName(QStringLiteral("lineEdit_FrontAcc"));
        lineEdit_FrontAcc->setGeometry(QRect(10, 80, 121, 31));
        lineEdit_FrontAcc->setAlignment(Qt::AlignCenter);
        pushButton_FrontAcc = new QPushButton(groupBox);
        pushButton_FrontAcc->setObjectName(QStringLiteral("pushButton_FrontAcc"));
        pushButton_FrontAcc->setGeometry(QRect(150, 80, 81, 31));
        pushButton_FrontVel = new QPushButton(groupBox);
        pushButton_FrontVel->setObjectName(QStringLiteral("pushButton_FrontVel"));
        pushButton_FrontVel->setGeometry(QRect(150, 30, 81, 31));
        lineEdit_FrontVel = new QLineEdit(groupBox);
        lineEdit_FrontVel->setObjectName(QStringLiteral("lineEdit_FrontVel"));
        lineEdit_FrontVel->setGeometry(QRect(10, 30, 121, 31));
        lineEdit_FrontVel->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(CDlgRouteManage);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 430, 531, 141));
        groupBox_2->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_FrameAcc = new QLineEdit(groupBox_2);
        lineEdit_FrameAcc->setObjectName(QStringLiteral("lineEdit_FrameAcc"));
        lineEdit_FrameAcc->setGeometry(QRect(10, 80, 121, 31));
        lineEdit_FrameAcc->setAlignment(Qt::AlignCenter);
        lineEdit_FrameVel = new QLineEdit(groupBox_2);
        lineEdit_FrameVel->setObjectName(QStringLiteral("lineEdit_FrameVel"));
        lineEdit_FrameVel->setGeometry(QRect(10, 30, 121, 31));
        lineEdit_FrameVel->setAlignment(Qt::AlignCenter);
        pushButton_FrameAcc = new QPushButton(groupBox_2);
        pushButton_FrameAcc->setObjectName(QStringLiteral("pushButton_FrameAcc"));
        pushButton_FrameAcc->setGeometry(QRect(150, 80, 91, 31));
        pushButton_FrameVel = new QPushButton(groupBox_2);
        pushButton_FrameVel->setObjectName(QStringLiteral("pushButton_FrameVel"));
        pushButton_FrameVel->setGeometry(QRect(150, 30, 91, 31));
        pushButton_FrameCornerAcc = new QPushButton(groupBox_2);
        pushButton_FrameCornerAcc->setObjectName(QStringLiteral("pushButton_FrameCornerAcc"));
        pushButton_FrameCornerAcc->setGeometry(QRect(430, 80, 91, 31));
        pushButton_FrameCornerVel = new QPushButton(groupBox_2);
        pushButton_FrameCornerVel->setObjectName(QStringLiteral("pushButton_FrameCornerVel"));
        pushButton_FrameCornerVel->setGeometry(QRect(430, 30, 91, 31));
        lineEdit_FrameCornerVel = new QLineEdit(groupBox_2);
        lineEdit_FrameCornerVel->setObjectName(QStringLiteral("lineEdit_FrameCornerVel"));
        lineEdit_FrameCornerVel->setGeometry(QRect(290, 30, 121, 31));
        lineEdit_FrameCornerVel->setAlignment(Qt::AlignCenter);
        lineEdit_FrameCornerAcc = new QLineEdit(groupBox_2);
        lineEdit_FrameCornerAcc->setObjectName(QStringLiteral("lineEdit_FrameCornerAcc"));
        lineEdit_FrameCornerAcc->setGeometry(QRect(290, 80, 121, 31));
        lineEdit_FrameCornerAcc->setAlignment(Qt::AlignCenter);
        groupBox_3 = new QGroupBox(CDlgRouteManage);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 260, 241, 141));
        groupBox_3->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_UpDownCameraAcc = new QLineEdit(groupBox_3);
        lineEdit_UpDownCameraAcc->setObjectName(QStringLiteral("lineEdit_UpDownCameraAcc"));
        lineEdit_UpDownCameraAcc->setGeometry(QRect(10, 80, 121, 31));
        lineEdit_UpDownCameraAcc->setAlignment(Qt::AlignCenter);
        lineEdit_UpDownCameraVel = new QLineEdit(groupBox_3);
        lineEdit_UpDownCameraVel->setObjectName(QStringLiteral("lineEdit_UpDownCameraVel"));
        lineEdit_UpDownCameraVel->setGeometry(QRect(10, 30, 121, 31));
        lineEdit_UpDownCameraVel->setAlignment(Qt::AlignCenter);
        pushButton_UpDownCameraAcc = new QPushButton(groupBox_3);
        pushButton_UpDownCameraAcc->setObjectName(QStringLiteral("pushButton_UpDownCameraAcc"));
        pushButton_UpDownCameraAcc->setGeometry(QRect(150, 80, 81, 31));
        pushButton_UpDownCameraVel = new QPushButton(groupBox_3);
        pushButton_UpDownCameraVel->setObjectName(QStringLiteral("pushButton_UpDownCameraVel"));
        pushButton_UpDownCameraVel->setGeometry(QRect(150, 30, 81, 31));
        groupBox_4 = new QGroupBox(CDlgRouteManage);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(320, 260, 241, 141));
        groupBox_4->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_BackAcc = new QLineEdit(groupBox_4);
        lineEdit_BackAcc->setObjectName(QStringLiteral("lineEdit_BackAcc"));
        lineEdit_BackAcc->setGeometry(QRect(10, 80, 121, 31));
        lineEdit_BackAcc->setAlignment(Qt::AlignCenter);
        lineEdit_BackVel = new QLineEdit(groupBox_4);
        lineEdit_BackVel->setObjectName(QStringLiteral("lineEdit_BackVel"));
        lineEdit_BackVel->setGeometry(QRect(10, 30, 121, 31));
        lineEdit_BackVel->setAlignment(Qt::AlignCenter);
        pushButton_BackAcc = new QPushButton(groupBox_4);
        pushButton_BackAcc->setObjectName(QStringLiteral("pushButton_BackAcc"));
        pushButton_BackAcc->setGeometry(QRect(150, 80, 81, 31));
        pushButton_BackVel = new QPushButton(groupBox_4);
        pushButton_BackVel->setObjectName(QStringLiteral("pushButton_BackVel"));
        pushButton_BackVel->setGeometry(QRect(150, 30, 81, 31));
        groupBox_5 = new QGroupBox(CDlgRouteManage);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(320, 90, 251, 141));
        groupBox_5->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_LineAcc = new QLineEdit(groupBox_5);
        lineEdit_LineAcc->setObjectName(QStringLiteral("lineEdit_LineAcc"));
        lineEdit_LineAcc->setGeometry(QRect(10, 80, 121, 31));
        lineEdit_LineAcc->setAlignment(Qt::AlignCenter);
        lineEdit_LineVel = new QLineEdit(groupBox_5);
        lineEdit_LineVel->setObjectName(QStringLiteral("lineEdit_LineVel"));
        lineEdit_LineVel->setGeometry(QRect(10, 30, 121, 31));
        lineEdit_LineVel->setAlignment(Qt::AlignCenter);
        pushButton_LineAcc = new QPushButton(groupBox_5);
        pushButton_LineAcc->setObjectName(QStringLiteral("pushButton_LineAcc"));
        pushButton_LineAcc->setGeometry(QRect(150, 80, 81, 31));
        pushButton_LineVel = new QPushButton(groupBox_5);
        pushButton_LineVel->setObjectName(QStringLiteral("pushButton_LineVel"));
        pushButton_LineVel->setGeometry(QRect(150, 30, 81, 31));
        plainTextEdit_Show = new QPlainTextEdit(CDlgRouteManage);
        plainTextEdit_Show->setObjectName(QStringLiteral("plainTextEdit_Show"));
        plainTextEdit_Show->setGeometry(QRect(590, 20, 261, 631));
        plainTextEdit_Show->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\215\216\346\226\207\344\273\277\345\256\213\";"));
        checkBox_EnableCheckDoor = new QCheckBox(CDlgRouteManage);
        checkBox_EnableCheckDoor->setObjectName(QStringLiteral("checkBox_EnableCheckDoor"));
        checkBox_EnableCheckDoor->setGeometry(QRect(80, 610, 171, 31));
        checkBox_EnableCheckDoor->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox_6 = new QGroupBox(CDlgRouteManage);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(30, 590, 531, 61));
        groupBox_6->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        checkBox_EnableFloodLight = new QCheckBox(groupBox_6);
        checkBox_EnableFloodLight->setObjectName(QStringLiteral("checkBox_EnableFloodLight"));
        checkBox_EnableFloodLight->setGeometry(QRect(300, 20, 171, 31));
        checkBox_EnableFloodLight->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        comboBox_ModelIndex = new QComboBox(CDlgRouteManage);
        comboBox_ModelIndex->setObjectName(QStringLiteral("comboBox_ModelIndex"));
        comboBox_ModelIndex->setGeometry(QRect(50, 40, 501, 31));
        comboBox_ModelIndex->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox_7 = new QGroupBox(CDlgRouteManage);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(30, 10, 541, 71));
        groupBox_7->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox_7->raise();
        groupBox_6->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        groupBox_4->raise();
        groupBox_5->raise();
        plainTextEdit_Show->raise();
        checkBox_EnableCheckDoor->raise();
        comboBox_ModelIndex->raise();

        retranslateUi(CDlgRouteManage);

        QMetaObject::connectSlotsByName(CDlgRouteManage);
    } // setupUi

    void retranslateUi(QDialog *CDlgRouteManage)
    {
        CDlgRouteManage->setWindowTitle(QApplication::translate("CDlgRouteManage", "\346\211\213\346\234\272\345\244\226\350\247\202\346\243\200\346\265\213\351\200\237\345\272\246\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("CDlgRouteManage", "\346\255\243\351\235\242\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_FrontAcc->setText(QApplication::translate("CDlgRouteManage", "\345\212\240\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_FrontVel->setText(QApplication::translate("CDlgRouteManage", "\351\200\237\345\272\246", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("CDlgRouteManage", "\344\270\255\346\241\206\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_FrameAcc->setText(QApplication::translate("CDlgRouteManage", "\347\233\264\347\272\277\345\212\240\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_FrameVel->setText(QApplication::translate("CDlgRouteManage", "\347\233\264\347\272\277\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_FrameCornerAcc->setText(QApplication::translate("CDlgRouteManage", "R\350\247\222\345\212\240\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_FrameCornerVel->setText(QApplication::translate("CDlgRouteManage", "R\350\247\222\351\200\237\345\272\246", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("CDlgRouteManage", "\347\277\273\350\275\254\345\217\212\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        pushButton_UpDownCameraAcc->setText(QApplication::translate("CDlgRouteManage", "\345\212\240\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_UpDownCameraVel->setText(QApplication::translate("CDlgRouteManage", "\351\200\237\345\272\246", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("CDlgRouteManage", "\350\203\214\351\235\242\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_BackAcc->setText(QApplication::translate("CDlgRouteManage", "\345\212\240\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_BackVel->setText(QApplication::translate("CDlgRouteManage", "\351\200\237\345\272\246", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("CDlgRouteManage", "\345\205\250\345\261\200\350\275\254\347\247\273\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_LineAcc->setText(QApplication::translate("CDlgRouteManage", "\345\212\240\351\200\237\345\272\246", Q_NULLPTR));
        pushButton_LineVel->setText(QApplication::translate("CDlgRouteManage", "\351\200\237\345\272\246", Q_NULLPTR));
        checkBox_EnableCheckDoor->setText(QApplication::translate("CDlgRouteManage", "\344\275\277\350\203\275\345\256\211\345\205\250\351\227\250\346\243\200\346\265\213", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("CDlgRouteManage", "\345\256\211\345\205\250\351\227\250\345\222\214\347\205\247\346\230\216\347\201\257", Q_NULLPTR));
        checkBox_EnableFloodLight->setText(QApplication::translate("CDlgRouteManage", "\345\274\200\345\220\257\347\205\247\346\230\216\347\201\257", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("CDlgRouteManage", "\346\250\241\346\235\277\345\220\215\347\247\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CDlgRouteManage: public Ui_CDlgRouteManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGROUTEMANAGE_H
