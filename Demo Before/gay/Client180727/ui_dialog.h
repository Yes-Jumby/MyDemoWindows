/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label_2;
    QLineEdit *linePORT;
    QTextEdit *textEdit;
    QPushButton *BTN_Quit;
    QGroupBox *groupBox;
    QLineEdit *lineIP;
    QLabel *label;
    QPushButton *BTN_Config;
    QPushButton *listenBtn;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QProgressBar *Prog;
    QLabel *label_4;
    QPushButton *selectBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(697, 510);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 100, 71, 16));
        linePORT = new QLineEdit(Dialog);
        linePORT->setObjectName(QStringLiteral("linePORT"));
        linePORT->setGeometry(QRect(150, 100, 113, 20));
        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(370, 30, 291, 101));
        BTN_Quit = new QPushButton(Dialog);
        BTN_Quit->setObjectName(QStringLiteral("BTN_Quit"));
        BTN_Quit->setGeometry(QRect(600, 430, 75, 23));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 271, 171));
        lineIP = new QLineEdit(groupBox);
        lineIP->setObjectName(QStringLiteral("lineIP"));
        lineIP->setGeometry(QRect(130, 40, 113, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 40, 81, 16));
        BTN_Config = new QPushButton(groupBox);
        BTN_Config->setObjectName(QStringLiteral("BTN_Config"));
        BTN_Config->setGeometry(QRect(30, 120, 75, 23));
        listenBtn = new QPushButton(groupBox);
        listenBtn->setObjectName(QStringLiteral("listenBtn"));
        listenBtn->setGeometry(QRect(160, 120, 75, 23));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 300, 75, 23));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 260, 113, 20));
        Prog = new QProgressBar(Dialog);
        Prog->setObjectName(QStringLiteral("Prog"));
        Prog->setGeometry(QRect(380, 150, 301, 23));
        Prog->setValue(24);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 260, 81, 16));
        selectBtn = new QPushButton(Dialog);
        selectBtn->setObjectName(QStringLiteral("selectBtn"));
        selectBtn->setGeometry(QRect(30, 300, 75, 23));
        groupBox->raise();
        label_2->raise();
        linePORT->raise();
        textEdit->raise();
        BTN_Quit->raise();
        pushButton->raise();
        lineEdit->raise();
        Prog->raise();
        label_4->raise();
        selectBtn->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\345\217\267", Q_NULLPTR));
        BTN_Quit->setText(QApplication::translate("Dialog", "\351\200\200\345\207\272", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "\347\253\257\345\217\243\345\217\267\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200", Q_NULLPTR));
        BTN_Config->setText(QApplication::translate("Dialog", "\350\256\276\347\275\256", Q_NULLPTR));
        listenBtn->setText(QApplication::translate("Dialog", "\350\277\236\346\216\245", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Dialog", "\345\217\221\351\200\201", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog", "\350\257\267\350\276\223\345\205\245\345\221\275\344\273\244", Q_NULLPTR));
        selectBtn->setText(QApplication::translate("Dialog", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
