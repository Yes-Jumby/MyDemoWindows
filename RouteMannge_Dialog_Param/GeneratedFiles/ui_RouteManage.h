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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QPushButton *pushButton_VelAccDlg;
    QPushButton *pushButton_FrameCameraOn;
    QPushButton *pushButton_DebugDlg;
    QPushButton *pushButton_Path_Frame_1;
    QPushButton *pushButton_Path_Frame_2;
    QPushButton *pushButton_Path_Frame_3;
    QPushButton *pushButton_Path_Frame_4;
    QPushButton *pushButton_Path_FrameCorner_1;
    QPushButton *pushButton_Path_FrameCorner_2;
    QPushButton *pushButton_Path_FrameCorner_3;
    QPushButton *pushButton_Path_FrameCorner_4;
    QPushButton *pushButton_PutPhoneOnAxis;
    QPushButton *pushButton_CameraFocus;
    QPushButton *pushButton_PutPhoneOut;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_Pos_Axis_1;
    QLineEdit *lineEdit_Pos_Axis_2;
    QLineEdit *lineEdit_Pos_Axis_3;
    QLabel *label_4;
    QPushButton *pushButton_FocusCameraOn;
    QLabel *label_5;
    QComboBox *comboBox_AxisNum;
    QLabel *label_6;
    QLineEdit *lineEdit_P2p_Length;
    QPushButton *pushButton_P2P;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Cylinder;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RouteManage)
    {
        if (RouteManage->objectName().isEmpty())
            RouteManage->setObjectName(QStringLiteral("RouteManage"));
        RouteManage->resize(892, 582);
        centralWidget = new QWidget(RouteManage);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(160, 20, 101, 41));
        pushButton_Reset = new QPushButton(centralWidget);
        pushButton_Reset->setObjectName(QStringLiteral("pushButton_Reset"));
        pushButton_Reset->setGeometry(QRect(160, 90, 101, 41));
        pushButton_Check = new QPushButton(centralWidget);
        pushButton_Check->setObjectName(QStringLiteral("pushButton_Check"));
        pushButton_Check->setGeometry(QRect(300, 50, 101, 41));
        pushButton_Stop = new QPushButton(centralWidget);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setGeometry(QRect(20, 90, 101, 41));
        plainTextEdit_Show = new QPlainTextEdit(centralWidget);
        plainTextEdit_Show->setObjectName(QStringLiteral("plainTextEdit_Show"));
        plainTextEdit_Show->setGeometry(QRect(10, 440, 871, 81));
        pushButton_Init = new QPushButton(centralWidget);
        pushButton_Init->setObjectName(QStringLiteral("pushButton_Init"));
        pushButton_Init->setGeometry(QRect(20, 20, 101, 41));
        pushButton_ParamDlg = new QPushButton(centralWidget);
        pushButton_ParamDlg->setObjectName(QStringLiteral("pushButton_ParamDlg"));
        pushButton_ParamDlg->setGeometry(QRect(560, 30, 101, 41));
        pushButton_LightParamDlg = new QPushButton(centralWidget);
        pushButton_LightParamDlg->setObjectName(QStringLiteral("pushButton_LightParamDlg"));
        pushButton_LightParamDlg->setGeometry(QRect(440, 80, 101, 41));
        pushButton_VelAccDlg = new QPushButton(centralWidget);
        pushButton_VelAccDlg->setObjectName(QStringLiteral("pushButton_VelAccDlg"));
        pushButton_VelAccDlg->setGeometry(QRect(440, 30, 101, 41));
        pushButton_FrameCameraOn = new QPushButton(centralWidget);
        pushButton_FrameCameraOn->setObjectName(QStringLiteral("pushButton_FrameCameraOn"));
        pushButton_FrameCameraOn->setGeometry(QRect(760, 30, 101, 41));
        pushButton_DebugDlg = new QPushButton(centralWidget);
        pushButton_DebugDlg->setObjectName(QStringLiteral("pushButton_DebugDlg"));
        pushButton_DebugDlg->setGeometry(QRect(560, 80, 101, 41));
        pushButton_Path_Frame_1 = new QPushButton(centralWidget);
        pushButton_Path_Frame_1->setObjectName(QStringLiteral("pushButton_Path_Frame_1"));
        pushButton_Path_Frame_1->setGeometry(QRect(20, 180, 101, 41));
        pushButton_Path_Frame_2 = new QPushButton(centralWidget);
        pushButton_Path_Frame_2->setObjectName(QStringLiteral("pushButton_Path_Frame_2"));
        pushButton_Path_Frame_2->setGeometry(QRect(20, 240, 101, 41));
        pushButton_Path_Frame_3 = new QPushButton(centralWidget);
        pushButton_Path_Frame_3->setObjectName(QStringLiteral("pushButton_Path_Frame_3"));
        pushButton_Path_Frame_3->setGeometry(QRect(20, 300, 101, 41));
        pushButton_Path_Frame_4 = new QPushButton(centralWidget);
        pushButton_Path_Frame_4->setObjectName(QStringLiteral("pushButton_Path_Frame_4"));
        pushButton_Path_Frame_4->setGeometry(QRect(20, 360, 101, 41));
        pushButton_Path_FrameCorner_1 = new QPushButton(centralWidget);
        pushButton_Path_FrameCorner_1->setObjectName(QStringLiteral("pushButton_Path_FrameCorner_1"));
        pushButton_Path_FrameCorner_1->setGeometry(QRect(160, 180, 101, 41));
        pushButton_Path_FrameCorner_2 = new QPushButton(centralWidget);
        pushButton_Path_FrameCorner_2->setObjectName(QStringLiteral("pushButton_Path_FrameCorner_2"));
        pushButton_Path_FrameCorner_2->setGeometry(QRect(160, 240, 101, 41));
        pushButton_Path_FrameCorner_3 = new QPushButton(centralWidget);
        pushButton_Path_FrameCorner_3->setObjectName(QStringLiteral("pushButton_Path_FrameCorner_3"));
        pushButton_Path_FrameCorner_3->setGeometry(QRect(160, 300, 101, 41));
        pushButton_Path_FrameCorner_4 = new QPushButton(centralWidget);
        pushButton_Path_FrameCorner_4->setObjectName(QStringLiteral("pushButton_Path_FrameCorner_4"));
        pushButton_Path_FrameCorner_4->setGeometry(QRect(160, 360, 101, 41));
        pushButton_PutPhoneOnAxis = new QPushButton(centralWidget);
        pushButton_PutPhoneOnAxis->setObjectName(QStringLiteral("pushButton_PutPhoneOnAxis"));
        pushButton_PutPhoneOnAxis->setGeometry(QRect(310, 180, 101, 41));
        pushButton_CameraFocus = new QPushButton(centralWidget);
        pushButton_CameraFocus->setObjectName(QStringLiteral("pushButton_CameraFocus"));
        pushButton_CameraFocus->setGeometry(QRect(310, 300, 101, 41));
        pushButton_PutPhoneOut = new QPushButton(centralWidget);
        pushButton_PutPhoneOut->setObjectName(QStringLiteral("pushButton_PutPhoneOut"));
        pushButton_PutPhoneOut->setGeometry(QRect(310, 360, 101, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(460, 190, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(460, 230, 54, 12));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(460, 270, 54, 12));
        lineEdit_Pos_Axis_1 = new QLineEdit(centralWidget);
        lineEdit_Pos_Axis_1->setObjectName(QStringLiteral("lineEdit_Pos_Axis_1"));
        lineEdit_Pos_Axis_1->setGeometry(QRect(530, 179, 101, 31));
        lineEdit_Pos_Axis_1->setAlignment(Qt::AlignCenter);
        lineEdit_Pos_Axis_1->setReadOnly(true);
        lineEdit_Pos_Axis_2 = new QLineEdit(centralWidget);
        lineEdit_Pos_Axis_2->setObjectName(QStringLiteral("lineEdit_Pos_Axis_2"));
        lineEdit_Pos_Axis_2->setGeometry(QRect(530, 220, 101, 31));
        lineEdit_Pos_Axis_2->setAlignment(Qt::AlignCenter);
        lineEdit_Pos_Axis_2->setReadOnly(true);
        lineEdit_Pos_Axis_3 = new QLineEdit(centralWidget);
        lineEdit_Pos_Axis_3->setObjectName(QStringLiteral("lineEdit_Pos_Axis_3"));
        lineEdit_Pos_Axis_3->setGeometry(QRect(530, 260, 101, 31));
        lineEdit_Pos_Axis_3->setAlignment(Qt::AlignCenter);
        lineEdit_Pos_Axis_3->setReadOnly(true);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(690, 40, 54, 12));
        pushButton_FocusCameraOn = new QPushButton(centralWidget);
        pushButton_FocusCameraOn->setObjectName(QStringLiteral("pushButton_FocusCameraOn"));
        pushButton_FocusCameraOn->setGeometry(QRect(760, 80, 101, 41));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(690, 90, 71, 16));
        comboBox_AxisNum = new QComboBox(centralWidget);
        comboBox_AxisNum->setObjectName(QStringLiteral("comboBox_AxisNum"));
        comboBox_AxisNum->setGeometry(QRect(660, 180, 141, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(660, 230, 31, 16));
        lineEdit_P2p_Length = new QLineEdit(centralWidget);
        lineEdit_P2p_Length->setObjectName(QStringLiteral("lineEdit_P2p_Length"));
        lineEdit_P2p_Length->setGeometry(QRect(700, 220, 101, 31));
        lineEdit_P2p_Length->setAlignment(Qt::AlignCenter);
        pushButton_P2P = new QPushButton(centralWidget);
        pushButton_P2P->setObjectName(QStringLiteral("pushButton_P2P"));
        pushButton_P2P->setGeometry(QRect(660, 260, 141, 31));
        pushButton_Save = new QPushButton(centralWidget);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(570, 310, 141, 31));
        pushButton_Cylinder = new QPushButton(centralWidget);
        pushButton_Cylinder->setObjectName(QStringLiteral("pushButton_Cylinder"));
        pushButton_Cylinder->setGeometry(QRect(310, 240, 101, 41));
        RouteManage->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RouteManage);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 892, 23));
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
        RouteManage->setWindowTitle(QApplication::translate("RouteManage", "\346\211\213\346\234\272\345\244\226\350\247\202\346\243\200\346\265\213\350\267\257\345\276\204\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("RouteManage", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_Reset->setText(QApplication::translate("RouteManage", "\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_Check->setText(QApplication::translate("RouteManage", "\345\274\200\345\247\213\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_Stop->setText(QApplication::translate("RouteManage", "\345\201\234\346\255\242", Q_NULLPTR));
        pushButton_Init->setText(QApplication::translate("RouteManage", "\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        pushButton_ParamDlg->setText(QApplication::translate("RouteManage", "\350\267\257\345\276\204\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_LightParamDlg->setText(QApplication::translate("RouteManage", "\345\205\211\346\272\220\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_VelAccDlg->setText(QApplication::translate("RouteManage", "\350\277\220\345\212\250\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_FrameCameraOn->setText(QString());
        pushButton_DebugDlg->setText(QApplication::translate("RouteManage", "\350\260\203\350\257\225\347\225\214\351\235\242", Q_NULLPTR));
        pushButton_Path_Frame_1->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206\347\233\264\350\276\2711", Q_NULLPTR));
        pushButton_Path_Frame_2->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206\347\233\264\350\276\2712", Q_NULLPTR));
        pushButton_Path_Frame_3->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206\347\233\264\350\276\2713", Q_NULLPTR));
        pushButton_Path_Frame_4->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206\347\233\264\350\276\2714", Q_NULLPTR));
        pushButton_Path_FrameCorner_1->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206R\350\247\2221", Q_NULLPTR));
        pushButton_Path_FrameCorner_2->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206R\350\247\2222", Q_NULLPTR));
        pushButton_Path_FrameCorner_3->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206R\350\247\2223", Q_NULLPTR));
        pushButton_Path_FrameCorner_4->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206R\350\247\2224", Q_NULLPTR));
        pushButton_PutPhoneOnAxis->setText(QApplication::translate("RouteManage", "\351\242\204\345\244\207", Q_NULLPTR));
        pushButton_CameraFocus->setText(QApplication::translate("RouteManage", "\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        pushButton_PutPhoneOut->setText(QApplication::translate("RouteManage", "\345\207\272\345\217\243", Q_NULLPTR));
        label->setText(QApplication::translate("RouteManage", "X\350\275\264\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("RouteManage", "Y\350\275\264\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("RouteManage", "Z\350\275\264\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("RouteManage", "\344\270\255\346\241\206\347\233\270\346\234\272\357\274\232", Q_NULLPTR));
        pushButton_FocusCameraOn->setText(QString());
        label_5->setText(QApplication::translate("RouteManage", "\346\221\204\345\203\217\345\244\264\347\233\270\346\234\272\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("RouteManage", "\346\255\245\351\225\277\357\274\232", Q_NULLPTR));
        pushButton_P2P->setText(QApplication::translate("RouteManage", "\347\247\273\345\212\250", Q_NULLPTR));
        pushButton_Save->setText(QApplication::translate("RouteManage", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_Cylinder->setText(QApplication::translate("RouteManage", "\347\277\273\350\275\254\346\234\272\346\236\204", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RouteManage: public Ui_RouteManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTEMANAGE_H
