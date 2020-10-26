/********************************************************************************
** Form generated from reading UI file 'dialog1.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG1_H
#define UI_DIALOG1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog1
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *EDIT;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;

    void setupUi(QDialog *Dialog1)
    {
        if (Dialog1->objectName().isEmpty())
            Dialog1->setObjectName(QStringLiteral("Dialog1"));
        Dialog1->resize(400, 300);
        pushButton = new QPushButton(Dialog1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(240, 110, 75, 23));
        lineEdit = new QLineEdit(Dialog1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 50, 121, 41));
        EDIT = new QLineEdit(Dialog1);
        EDIT->setObjectName(QStringLiteral("EDIT"));
        EDIT->setGeometry(QRect(40, 80, 113, 51));
        groupBox = new QGroupBox(Dialog1);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(210, 30, 151, 131));
        groupBox_2 = new QGroupBox(Dialog1);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 30, 161, 131));
        groupBox->raise();
        pushButton->raise();
        lineEdit->raise();
        EDIT->raise();
        groupBox_2->raise();

        retranslateUi(Dialog1);

        QMetaObject::connectSlotsByName(Dialog1);
    } // setupUi

    void retranslateUi(QDialog *Dialog1)
    {
        Dialog1->setWindowTitle(QApplication::translate("Dialog1", "\344\273\216\347\252\227\345\217\243", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Dialog1", "\345\217\221\351\200\201", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog1", "\345\217\221\351\200\201\346\225\260\346\215\256", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog1", "\346\216\245\346\224\266\346\225\260\346\215\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog1: public Ui_Dialog1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG1_H
