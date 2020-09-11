/********************************************************************************
** Form generated from reading UI file 'AlgorithmTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMTEST_H
#define UI_ALGORITHMTEST_H

#include <Mylabel.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AlgorithmTest
{
public:
    QPushButton *pushButton_selectFile;
    QLineEdit *lineEdit_filePath;
    myLabel *label_1;
    QTableWidget *tableWidget_file;
    QTableWidget *tableWidget_defect;
    QTextEdit *textEdit_show;
    QPushButton *pushButton_CallAlgDlg;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_PageIndex;
    QPushButton *pushButton_PageIndex;
    QPushButton *pushButton_ResolutionH;
    QLineEdit *lineEdit_ResolutionH;
    QPushButton *pushButton_ResolutionV;
    QLineEdit *lineEdit_ResolutionV;
    QPushButton *pushButton_ParamPath;
    QPushButton *pushButton_ModelPath;
    QPushButton *pushButton_SingleFrame;
    QPushButton *pushButton_ContinuFrame;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_Init;
    QPushButton *pushButton_LogPath;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_OriginalIMG;
    QPushButton *pushButton_Alg;

    void setupUi(QDialog *AlgorithmTest)
    {
        if (AlgorithmTest->objectName().isEmpty())
            AlgorithmTest->setObjectName(QStringLiteral("AlgorithmTest"));
        AlgorithmTest->resize(1360, 708);
        AlgorithmTest->setContextMenuPolicy(Qt::NoContextMenu);
        pushButton_selectFile = new QPushButton(AlgorithmTest);
        pushButton_selectFile->setObjectName(QStringLiteral("pushButton_selectFile"));
        pushButton_selectFile->setGeometry(QRect(1050, 130, 75, 23));
        pushButton_selectFile->setAutoDefault(false);
        lineEdit_filePath = new QLineEdit(AlgorithmTest);
        lineEdit_filePath->setObjectName(QStringLiteral("lineEdit_filePath"));
        lineEdit_filePath->setGeometry(QRect(740, 130, 291, 20));
        label_1 = new myLabel(AlgorithmTest);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(20, 20, 691, 671));
        label_1->setCursor(QCursor(Qt::ArrowCursor));
        label_1->setStyleSheet(QStringLiteral(""));
        label_1->setFrameShape(QFrame::Panel);
        tableWidget_file = new QTableWidget(AlgorithmTest);
        tableWidget_file->setObjectName(QStringLiteral("tableWidget_file"));
        tableWidget_file->setGeometry(QRect(740, 220, 601, 201));
        tableWidget_defect = new QTableWidget(AlgorithmTest);
        tableWidget_defect->setObjectName(QStringLiteral("tableWidget_defect"));
        tableWidget_defect->setGeometry(QRect(740, 460, 601, 231));
        textEdit_show = new QTextEdit(AlgorithmTest);
        textEdit_show->setObjectName(QStringLiteral("textEdit_show"));
        textEdit_show->setGeometry(QRect(740, 20, 391, 71));
        pushButton_CallAlgDlg = new QPushButton(AlgorithmTest);
        pushButton_CallAlgDlg->setObjectName(QStringLiteral("pushButton_CallAlgDlg"));
        pushButton_CallAlgDlg->setGeometry(QRect(870, 170, 75, 23));
        pushButton_CallAlgDlg->setAutoDefault(false);
        groupBox = new QGroupBox(AlgorithmTest);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1150, 0, 201, 201));
        lineEdit_PageIndex = new QLineEdit(groupBox);
        lineEdit_PageIndex->setObjectName(QStringLiteral("lineEdit_PageIndex"));
        lineEdit_PageIndex->setGeometry(QRect(20, 140, 71, 20));
        pushButton_PageIndex = new QPushButton(groupBox);
        pushButton_PageIndex->setObjectName(QStringLiteral("pushButton_PageIndex"));
        pushButton_PageIndex->setGeometry(QRect(110, 140, 75, 23));
        pushButton_PageIndex->setAutoDefault(false);
        pushButton_ResolutionH = new QPushButton(groupBox);
        pushButton_ResolutionH->setObjectName(QStringLiteral("pushButton_ResolutionH"));
        pushButton_ResolutionH->setGeometry(QRect(110, 20, 75, 23));
        pushButton_ResolutionH->setAutoDefault(false);
        lineEdit_ResolutionH = new QLineEdit(groupBox);
        lineEdit_ResolutionH->setObjectName(QStringLiteral("lineEdit_ResolutionH"));
        lineEdit_ResolutionH->setGeometry(QRect(20, 20, 71, 20));
        pushButton_ResolutionV = new QPushButton(groupBox);
        pushButton_ResolutionV->setObjectName(QStringLiteral("pushButton_ResolutionV"));
        pushButton_ResolutionV->setGeometry(QRect(110, 50, 75, 23));
        pushButton_ResolutionV->setAutoDefault(false);
        lineEdit_ResolutionV = new QLineEdit(groupBox);
        lineEdit_ResolutionV->setObjectName(QStringLiteral("lineEdit_ResolutionV"));
        lineEdit_ResolutionV->setGeometry(QRect(20, 50, 71, 20));
        pushButton_ParamPath = new QPushButton(groupBox);
        pushButton_ParamPath->setObjectName(QStringLiteral("pushButton_ParamPath"));
        pushButton_ParamPath->setGeometry(QRect(60, 80, 75, 23));
        pushButton_ParamPath->setAutoDefault(false);
        pushButton_ModelPath = new QPushButton(groupBox);
        pushButton_ModelPath->setObjectName(QStringLiteral("pushButton_ModelPath"));
        pushButton_ModelPath->setGeometry(QRect(20, 110, 75, 23));
        pushButton_ModelPath->setAutoDefault(false);
        pushButton_SingleFrame = new QPushButton(groupBox);
        pushButton_SingleFrame->setObjectName(QStringLiteral("pushButton_SingleFrame"));
        pushButton_SingleFrame->setGeometry(QRect(20, 170, 75, 23));
        pushButton_SingleFrame->setAutoDefault(false);
        pushButton_ContinuFrame = new QPushButton(groupBox);
        pushButton_ContinuFrame->setObjectName(QStringLiteral("pushButton_ContinuFrame"));
        pushButton_ContinuFrame->setGeometry(QRect(110, 170, 75, 23));
        pushButton_ContinuFrame->setAutoDefault(false);
        groupBox_2 = new QGroupBox(AlgorithmTest);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 711, 701));
        groupBox_4 = new QGroupBox(AlgorithmTest);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(730, 0, 411, 101));
        groupBox_5 = new QGroupBox(AlgorithmTest);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(730, 110, 411, 51));
        pushButton_Init = new QPushButton(AlgorithmTest);
        pushButton_Init->setObjectName(QStringLiteral("pushButton_Init"));
        pushButton_Init->setGeometry(QRect(780, 170, 75, 23));
        pushButton_Init->setAutoDefault(false);
        pushButton_LogPath = new QPushButton(AlgorithmTest);
        pushButton_LogPath->setObjectName(QStringLiteral("pushButton_LogPath"));
        pushButton_LogPath->setGeometry(QRect(1260, 110, 75, 23));
        pushButton_LogPath->setAutoDefault(false);
        groupBox_3 = new QGroupBox(AlgorithmTest);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(730, 200, 621, 231));
        groupBox_6 = new QGroupBox(AlgorithmTest);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(730, 440, 621, 261));
        pushButton_OriginalIMG = new QPushButton(AlgorithmTest);
        pushButton_OriginalIMG->setObjectName(QStringLiteral("pushButton_OriginalIMG"));
        pushButton_OriginalIMG->setGeometry(QRect(960, 170, 75, 23));
        pushButton_OriginalIMG->setAutoDefault(false);
        pushButton_Alg = new QPushButton(AlgorithmTest);
        pushButton_Alg->setObjectName(QStringLiteral("pushButton_Alg"));
        pushButton_Alg->setGeometry(QRect(1050, 170, 75, 23));
        pushButton_Alg->setAutoDefault(false);
        groupBox_3->raise();
        groupBox_6->raise();
        groupBox_5->raise();
        groupBox_4->raise();
        groupBox_2->raise();
        groupBox->raise();
        pushButton_selectFile->raise();
        lineEdit_filePath->raise();
        label_1->raise();
        tableWidget_file->raise();
        tableWidget_defect->raise();
        textEdit_show->raise();
        pushButton_CallAlgDlg->raise();
        pushButton_Init->raise();
        pushButton_LogPath->raise();
        pushButton_OriginalIMG->raise();
        pushButton_Alg->raise();

        retranslateUi(AlgorithmTest);

        QMetaObject::connectSlotsByName(AlgorithmTest);
    } // setupUi

    void retranslateUi(QDialog *AlgorithmTest)
    {
        AlgorithmTest->setWindowTitle(QApplication::translate("AlgorithmTest", "\346\211\213\346\234\272\345\205\250\346\243\200\347\256\227\346\263\225\346\265\213\350\257\225\302\251\345\215\232\344\274\227\347\262\276\345\267\245\345\214\227\344\272\254\346\212\200\346\234\257\347\240\224\347\251\266\351\231\2422018", Q_NULLPTR));
        pushButton_selectFile->setText(QApplication::translate("AlgorithmTest", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        label_1->setText(QString());
        pushButton_CallAlgDlg->setText(QApplication::translate("AlgorithmTest", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("AlgorithmTest", "\347\256\227\346\263\225\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_PageIndex->setText(QApplication::translate("AlgorithmTest", "\347\224\273\351\235\242\345\217\267", Q_NULLPTR));
        pushButton_ResolutionH->setText(QApplication::translate("AlgorithmTest", "\346\250\252\345\220\221\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        pushButton_ResolutionV->setText(QApplication::translate("AlgorithmTest", "\347\272\265\345\220\221\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        pushButton_ParamPath->setText(QApplication::translate("AlgorithmTest", "\345\217\202\346\225\260\350\267\257\345\276\204", Q_NULLPTR));
        pushButton_ModelPath->setText(QApplication::translate("AlgorithmTest", "\346\250\241\346\235\277\350\267\257\345\276\204", Q_NULLPTR));
        pushButton_SingleFrame->setText(QApplication::translate("AlgorithmTest", "\345\215\225\345\270\247\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_ContinuFrame->setText(QApplication::translate("AlgorithmTest", "\350\277\236\347\273\255\346\243\200\346\265\213", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("AlgorithmTest", "\345\233\276\345\203\217\346\230\276\347\244\272", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("AlgorithmTest", "\347\212\266\346\200\201\346\230\276\347\244\272", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("AlgorithmTest", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        pushButton_Init->setText(QApplication::translate("AlgorithmTest", "\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        pushButton_LogPath->setText(QApplication::translate("AlgorithmTest", "\346\227\245\345\277\227\350\267\257\345\276\204", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("AlgorithmTest", "\345\233\276\345\203\217\345\210\227\350\241\250", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("AlgorithmTest", "\347\274\272\351\231\267\346\230\276\347\244\272", Q_NULLPTR));
        pushButton_OriginalIMG->setText(QApplication::translate("AlgorithmTest", "\351\200\211\346\213\251\345\233\276\347\211\207", Q_NULLPTR));
        pushButton_Alg->setText(QApplication::translate("AlgorithmTest", "\347\256\227\346\263\225\346\243\200\346\265\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmTest: public Ui_AlgorithmTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMTEST_H
