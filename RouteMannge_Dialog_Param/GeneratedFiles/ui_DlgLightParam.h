/********************************************************************************
** Form generated from reading UI file 'DlgLightParam.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLIGHTPARAM_H
#define UI_DLGLIGHTPARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CDlgLightParam
{
public:
    QComboBox *comboBox_ParamIndex;
    QLineEdit *lineEdit_Channel0;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_Channel1;
    QLineEdit *lineEdit_Channel2;
    QLabel *label_3;
    QLineEdit *lineEdit_Channel3;
    QLabel *label_4;
    QLineEdit *lineEdit_Channel4;
    QLabel *label_5;
    QLineEdit *lineEdit_Channel7;
    QLabel *label_6;
    QLineEdit *lineEdit_Channel5;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_Channel6;
    QLineEdit *lineEdit_Channel12;
    QLineEdit *lineEdit_Channel11;
    QLineEdit *lineEdit_Channel10;
    QLineEdit *lineEdit_Channel8;
    QLineEdit *lineEdit_Channel9;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QGroupBox *groupBox;
    QPlainTextEdit *plainTextEdit_Show;
    QComboBox *comboBox_ModelIndex;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_FrameUpExposureTime;
    QLabel *label_14;
    QLineEdit *lineEdit_FrameDownExposureTime;
    QLabel *label_15;
    QCheckBox *checkBox_EnableFrameUp;
    QCheckBox *checkBox_EnableFrameDown;
    QLineEdit *lineEdit_FocusLightIntensity;
    QLabel *label_17;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_Save;
    QLineEdit *lineEdit_FocusExposureTime;
    QCheckBox *checkBox_EnableFocus;
    QLabel *label_16;
    QLineEdit *lineEdit_FocusGain;
    QCheckBox *checkBox_EnableFrameDown1;
    QCheckBox *checkBox_EnableFocus1;
    QLabel *label_18;
    QLineEdit *lineEdit_FrameDownGain;
    QCheckBox *checkBox_EnableFrameUp1;
    QLineEdit *lineEdit_FrameUpGain;
    QLabel *label_19;
    QLabel *label_20;

    void setupUi(QDialog *CDlgLightParam)
    {
        if (CDlgLightParam->objectName().isEmpty())
            CDlgLightParam->setObjectName(QStringLiteral("CDlgLightParam"));
        CDlgLightParam->resize(953, 760);
        CDlgLightParam->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        comboBox_ParamIndex = new QComboBox(CDlgLightParam);
        comboBox_ParamIndex->setObjectName(QStringLiteral("comboBox_ParamIndex"));
        comboBox_ParamIndex->setGeometry(QRect(40, 110, 161, 31));
        lineEdit_Channel0 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel0->setObjectName(QStringLiteral("lineEdit_Channel0"));
        lineEdit_Channel0->setGeometry(QRect(160, 170, 121, 31));
        lineEdit_Channel0->setAlignment(Qt::AlignCenter);
        label = new QLabel(CDlgLightParam);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 175, 121, 21));
        label_2 = new QLabel(CDlgLightParam);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 230, 121, 21));
        lineEdit_Channel1 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel1->setObjectName(QStringLiteral("lineEdit_Channel1"));
        lineEdit_Channel1->setGeometry(QRect(160, 225, 121, 31));
        lineEdit_Channel1->setAlignment(Qt::AlignCenter);
        lineEdit_Channel2 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel2->setObjectName(QStringLiteral("lineEdit_Channel2"));
        lineEdit_Channel2->setGeometry(QRect(160, 280, 121, 31));
        lineEdit_Channel2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(CDlgLightParam);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 285, 121, 21));
        lineEdit_Channel3 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel3->setObjectName(QStringLiteral("lineEdit_Channel3"));
        lineEdit_Channel3->setGeometry(QRect(160, 330, 121, 31));
        lineEdit_Channel3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(CDlgLightParam);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 335, 121, 21));
        lineEdit_Channel4 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel4->setObjectName(QStringLiteral("lineEdit_Channel4"));
        lineEdit_Channel4->setGeometry(QRect(160, 380, 121, 31));
        lineEdit_Channel4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(CDlgLightParam);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 385, 121, 21));
        lineEdit_Channel7 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel7->setObjectName(QStringLiteral("lineEdit_Channel7"));
        lineEdit_Channel7->setGeometry(QRect(470, 325, 121, 31));
        lineEdit_Channel7->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(CDlgLightParam);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(330, 275, 131, 21));
        lineEdit_Channel5 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel5->setObjectName(QStringLiteral("lineEdit_Channel5"));
        lineEdit_Channel5->setGeometry(QRect(470, 215, 121, 31));
        lineEdit_Channel5->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(CDlgLightParam);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(330, 330, 131, 21));
        label_8 = new QLabel(CDlgLightParam);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(330, 220, 131, 21));
        lineEdit_Channel6 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel6->setObjectName(QStringLiteral("lineEdit_Channel6"));
        lineEdit_Channel6->setGeometry(QRect(470, 270, 121, 31));
        lineEdit_Channel6->setAlignment(Qt::AlignCenter);
        lineEdit_Channel12 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel12->setObjectName(QStringLiteral("lineEdit_Channel12"));
        lineEdit_Channel12->setGeometry(QRect(790, 380, 121, 31));
        lineEdit_Channel12->setAlignment(Qt::AlignCenter);
        lineEdit_Channel11 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel11->setObjectName(QStringLiteral("lineEdit_Channel11"));
        lineEdit_Channel11->setGeometry(QRect(790, 330, 121, 31));
        lineEdit_Channel11->setAlignment(Qt::AlignCenter);
        lineEdit_Channel10 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel10->setObjectName(QStringLiteral("lineEdit_Channel10"));
        lineEdit_Channel10->setGeometry(QRect(790, 280, 121, 31));
        lineEdit_Channel10->setAlignment(Qt::AlignCenter);
        lineEdit_Channel8 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel8->setObjectName(QStringLiteral("lineEdit_Channel8"));
        lineEdit_Channel8->setGeometry(QRect(790, 170, 121, 31));
        lineEdit_Channel8->setAlignment(Qt::AlignCenter);
        lineEdit_Channel9 = new QLineEdit(CDlgLightParam);
        lineEdit_Channel9->setObjectName(QStringLiteral("lineEdit_Channel9"));
        lineEdit_Channel9->setGeometry(QRect(790, 225, 121, 31));
        lineEdit_Channel9->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(CDlgLightParam);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(640, 380, 121, 21));
        label_10 = new QLabel(CDlgLightParam);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(640, 225, 121, 21));
        label_11 = new QLabel(CDlgLightParam);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(640, 280, 121, 21));
        label_12 = new QLabel(CDlgLightParam);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(640, 170, 121, 21));
        label_13 = new QLabel(CDlgLightParam);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(640, 330, 121, 21));
        groupBox = new QGroupBox(CDlgLightParam);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 80, 931, 361));
        plainTextEdit_Show = new QPlainTextEdit(CDlgLightParam);
        plainTextEdit_Show->setObjectName(QStringLiteral("plainTextEdit_Show"));
        plainTextEdit_Show->setGeometry(QRect(290, 10, 651, 61));
        comboBox_ModelIndex = new QComboBox(CDlgLightParam);
        comboBox_ModelIndex->setObjectName(QStringLiteral("comboBox_ModelIndex"));
        comboBox_ModelIndex->setGeometry(QRect(30, 30, 221, 31));
        groupBox_2 = new QGroupBox(CDlgLightParam);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 261, 71));
        lineEdit_FrameUpExposureTime = new QLineEdit(CDlgLightParam);
        lineEdit_FrameUpExposureTime->setObjectName(QStringLiteral("lineEdit_FrameUpExposureTime"));
        lineEdit_FrameUpExposureTime->setGeometry(QRect(160, 510, 121, 31));
        lineEdit_FrameUpExposureTime->setAlignment(Qt::AlignCenter);
        label_14 = new QLabel(CDlgLightParam);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 515, 121, 21));
        lineEdit_FrameDownExposureTime = new QLineEdit(CDlgLightParam);
        lineEdit_FrameDownExposureTime->setObjectName(QStringLiteral("lineEdit_FrameDownExposureTime"));
        lineEdit_FrameDownExposureTime->setGeometry(QRect(460, 510, 121, 31));
        lineEdit_FrameDownExposureTime->setAlignment(Qt::AlignCenter);
        label_15 = new QLabel(CDlgLightParam);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(330, 515, 121, 21));
        checkBox_EnableFrameUp = new QCheckBox(CDlgLightParam);
        checkBox_EnableFrameUp->setObjectName(QStringLiteral("checkBox_EnableFrameUp"));
        checkBox_EnableFrameUp->setGeometry(QRect(30, 470, 171, 31));
        checkBox_EnableFrameUp->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        checkBox_EnableFrameDown = new QCheckBox(CDlgLightParam);
        checkBox_EnableFrameDown->setObjectName(QStringLiteral("checkBox_EnableFrameDown"));
        checkBox_EnableFrameDown->setGeometry(QRect(330, 470, 171, 31));
        checkBox_EnableFrameDown->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_FocusLightIntensity = new QLineEdit(CDlgLightParam);
        lineEdit_FocusLightIntensity->setObjectName(QStringLiteral("lineEdit_FocusLightIntensity"));
        lineEdit_FocusLightIntensity->setGeometry(QRect(460, 670, 121, 31));
        lineEdit_FocusLightIntensity->setAlignment(Qt::AlignCenter);
        label_17 = new QLabel(CDlgLightParam);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(330, 675, 121, 21));
        groupBox_3 = new QGroupBox(CDlgLightParam);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 450, 931, 281));
        pushButton_Save = new QPushButton(groupBox_3);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(740, 220, 121, 41));
        lineEdit_FocusExposureTime = new QLineEdit(groupBox_3);
        lineEdit_FocusExposureTime->setObjectName(QStringLiteral("lineEdit_FocusExposureTime"));
        lineEdit_FocusExposureTime->setGeometry(QRect(760, 65, 121, 31));
        lineEdit_FocusExposureTime->setAlignment(Qt::AlignCenter);
        checkBox_EnableFocus = new QCheckBox(groupBox_3);
        checkBox_EnableFocus->setObjectName(QStringLiteral("checkBox_EnableFocus"));
        checkBox_EnableFocus->setGeometry(QRect(630, 25, 171, 31));
        checkBox_EnableFocus->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(630, 70, 121, 21));
        lineEdit_FocusGain = new QLineEdit(groupBox_3);
        lineEdit_FocusGain->setObjectName(QStringLiteral("lineEdit_FocusGain"));
        lineEdit_FocusGain->setGeometry(QRect(760, 160, 121, 31));
        lineEdit_FocusGain->setAlignment(Qt::AlignCenter);
        checkBox_EnableFrameDown1 = new QCheckBox(groupBox_3);
        checkBox_EnableFrameDown1->setObjectName(QStringLiteral("checkBox_EnableFrameDown1"));
        checkBox_EnableFrameDown1->setGeometry(QRect(320, 115, 171, 31));
        checkBox_EnableFrameDown1->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        checkBox_EnableFocus1 = new QCheckBox(groupBox_3);
        checkBox_EnableFocus1->setObjectName(QStringLiteral("checkBox_EnableFocus1"));
        checkBox_EnableFocus1->setGeometry(QRect(630, 120, 171, 31));
        checkBox_EnableFocus1->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(630, 165, 121, 21));
        lineEdit_FrameDownGain = new QLineEdit(groupBox_3);
        lineEdit_FrameDownGain->setObjectName(QStringLiteral("lineEdit_FrameDownGain"));
        lineEdit_FrameDownGain->setGeometry(QRect(450, 155, 121, 31));
        lineEdit_FrameDownGain->setAlignment(Qt::AlignCenter);
        checkBox_EnableFrameUp1 = new QCheckBox(groupBox_3);
        checkBox_EnableFrameUp1->setObjectName(QStringLiteral("checkBox_EnableFrameUp1"));
        checkBox_EnableFrameUp1->setGeometry(QRect(20, 115, 171, 31));
        checkBox_EnableFrameUp1->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lineEdit_FrameUpGain = new QLineEdit(groupBox_3);
        lineEdit_FrameUpGain->setObjectName(QStringLiteral("lineEdit_FrameUpGain"));
        lineEdit_FrameUpGain->setGeometry(QRect(150, 155, 121, 31));
        lineEdit_FrameUpGain->setAlignment(Qt::AlignCenter);
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(20, 160, 121, 21));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(320, 160, 121, 21));
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        comboBox_ParamIndex->raise();
        lineEdit_Channel0->raise();
        label->raise();
        label_2->raise();
        lineEdit_Channel1->raise();
        lineEdit_Channel2->raise();
        label_3->raise();
        lineEdit_Channel3->raise();
        label_4->raise();
        lineEdit_Channel4->raise();
        label_5->raise();
        lineEdit_Channel7->raise();
        label_6->raise();
        lineEdit_Channel5->raise();
        label_7->raise();
        label_8->raise();
        lineEdit_Channel6->raise();
        lineEdit_Channel12->raise();
        lineEdit_Channel11->raise();
        lineEdit_Channel10->raise();
        lineEdit_Channel8->raise();
        lineEdit_Channel9->raise();
        label_9->raise();
        label_10->raise();
        label_11->raise();
        label_12->raise();
        label_13->raise();
        plainTextEdit_Show->raise();
        comboBox_ModelIndex->raise();
        lineEdit_FrameUpExposureTime->raise();
        label_14->raise();
        lineEdit_FrameDownExposureTime->raise();
        label_15->raise();
        checkBox_EnableFrameUp->raise();
        checkBox_EnableFrameDown->raise();
        lineEdit_FocusLightIntensity->raise();
        label_17->raise();

        retranslateUi(CDlgLightParam);

        QMetaObject::connectSlotsByName(CDlgLightParam);
    } // setupUi

    void retranslateUi(QDialog *CDlgLightParam)
    {
        CDlgLightParam->setWindowTitle(QApplication::translate("CDlgLightParam", "\346\211\213\346\234\272\345\244\226\350\247\202\346\243\200\346\265\213\345\205\211\346\272\220\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("CDlgLightParam", "\346\255\243\351\235\242\345\220\214\350\275\264\345\205\211\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("CDlgLightParam", "\346\255\243\351\235\242\344\275\216\350\247\222\345\272\246[\345\211\215]\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("CDlgLightParam", "\346\255\243\351\235\242\344\275\216\350\247\222\345\272\246[\345\220\216]\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("CDlgLightParam", "\346\255\243\351\235\242\345\267\246\344\276\247\350\241\245\345\205\211\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("CDlgLightParam", "\346\255\243\351\235\242\345\217\263\344\276\247\350\241\245\345\205\211\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("CDlgLightParam", "\344\270\255\346\241\206\345\220\214\350\275\264\345\205\211[\344\270\212]\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("CDlgLightParam", "\344\270\255\346\241\206\345\220\214\350\275\264\345\205\211[\344\270\213]\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("CDlgLightParam", "\344\270\255\346\241\206\346\237\261\345\205\211\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("CDlgLightParam", "\345\217\215\351\235\242\345\217\263\344\276\247\350\241\245\345\205\211\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("CDlgLightParam", "\345\217\215\351\235\242\344\275\216\350\247\222\345\272\246[\345\211\215]\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("CDlgLightParam", "\345\217\215\351\235\242\344\275\216\350\247\222\345\272\246[\345\220\216]\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("CDlgLightParam", "\345\217\215\351\235\242\345\220\214\350\275\264\345\205\211\357\274\232", Q_NULLPTR));
        label_13->setText(QApplication::translate("CDlgLightParam", "\345\217\215\351\235\242\345\267\246\344\276\247\350\241\245\345\205\211\357\274\232", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("CDlgLightParam", "\345\205\211\346\272\220\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("CDlgLightParam", "\346\250\241\346\235\277\345\220\215\347\247\260", Q_NULLPTR));
        label_14->setText(QApplication::translate("CDlgLightParam", "\346\233\235\345\205\211\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        label_15->setText(QApplication::translate("CDlgLightParam", "\346\233\235\345\205\211\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        checkBox_EnableFrameUp->setText(QApplication::translate("CDlgLightParam", "\344\275\277\350\203\275\344\270\255\346\241\206\344\270\212\347\233\270\346\234\272", Q_NULLPTR));
        checkBox_EnableFrameDown->setText(QApplication::translate("CDlgLightParam", "\344\275\277\350\203\275\344\270\255\346\241\206\344\270\213\347\233\270\346\234\272", Q_NULLPTR));
        label_17->setText(QApplication::translate("CDlgLightParam", "\346\221\204\345\203\217\345\244\264\345\205\211\346\272\220\344\272\256\345\272\246\357\274\232", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("CDlgLightParam", "\346\233\235\345\205\211\345\217\212\345\205\211\346\272\220\344\272\256\345\272\246\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_Save->setText(QApplication::translate("CDlgLightParam", "\344\277\235\345\255\230\345\217\202\346\225\260", Q_NULLPTR));
        checkBox_EnableFocus->setText(QApplication::translate("CDlgLightParam", "\344\275\277\350\203\275\346\221\204\345\203\217\345\244\264\347\233\270\346\234\272", Q_NULLPTR));
        label_16->setText(QApplication::translate("CDlgLightParam", "\346\233\235\345\205\211\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        checkBox_EnableFrameDown1->setText(QApplication::translate("CDlgLightParam", "\344\275\277\350\203\275\344\270\255\346\241\206\344\270\213\347\233\270\346\234\272", Q_NULLPTR));
        checkBox_EnableFocus1->setText(QApplication::translate("CDlgLightParam", "\344\275\277\350\203\275\346\221\204\345\203\217\345\244\264\347\233\270\346\234\272", Q_NULLPTR));
        label_18->setText(QApplication::translate("CDlgLightParam", "\345\242\236\347\233\212\357\274\232", Q_NULLPTR));
        checkBox_EnableFrameUp1->setText(QApplication::translate("CDlgLightParam", "\344\275\277\350\203\275\344\270\255\346\241\206\344\270\212\347\233\270\346\234\272", Q_NULLPTR));
        label_19->setText(QApplication::translate("CDlgLightParam", "\345\242\236\347\233\212\357\274\232", Q_NULLPTR));
        label_20->setText(QApplication::translate("CDlgLightParam", "\345\242\236\347\233\212\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CDlgLightParam: public Ui_CDlgLightParam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLIGHTPARAM_H
