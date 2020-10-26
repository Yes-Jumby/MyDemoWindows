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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTextEdit *SHOW;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QTextEdit *SHOWNum;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        SHOW = new QTextEdit(Dialog);
        SHOW->setObjectName(QStringLiteral("SHOW"));
        SHOW->setGeometry(QRect(20, 40, 104, 71));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 90, 113, 20));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 130, 75, 23));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(180, 50, 191, 141));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 131, 221));
        SHOWNum = new QTextEdit(groupBox_2);
        SHOWNum->setObjectName(QStringLiteral("SHOWNum"));
        SHOWNum->setGeometry(QRect(10, 130, 104, 41));
        groupBox->raise();
        groupBox_2->raise();
        SHOW->raise();
        lineEdit->raise();
        pushButton->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\344\270\273\347\252\227\345\217\243", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Dialog", "\345\217\221\351\200\201", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "\345\217\221\351\200\201\346\225\260\346\215\256", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\346\216\245\346\224\266\346\225\260\346\215\256/\346\254\241\346\225\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
