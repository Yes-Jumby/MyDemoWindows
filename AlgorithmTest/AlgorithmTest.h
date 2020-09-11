#ifndef ALGORITHMTEST_H
#define ALGORITHMTEST_H

#include <QDialog>
#include <QImage>
#include <vector>
#include <QListView>
#include <QTableWidget>
#include "AlgDataType.h"
#include "AlgInspector.h"
#include "MyLabel.h"

#pragma execution_character_set("utf-8")

namespace Ui {
class AlgorithmTest;
}

class AlgorithmTest : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmTest(QWidget *parent = 0);
    ~AlgorithmTest();
private slots:
    void on_pushButton_selectFile_clicked();

    void on_pushButton_Init_clicked();

    void on_pushButton_Alg_clicked();

    void on_pushButton_CallAlgDlg_clicked();

    void on_pushButton_PageIndex_clicked();

    void on_pushButton_OriginalIMG_clicked();

    void on_pushButton_ResolutionH_clicked();

    void on_pushButton_ResolutionV_clicked();

    void on_pushButton_ParamPath_clicked();

    void on_pushButton_ModelPath_clicked();

    void on_pushButton_LogPath_clicked();

    void on_pushButton_SingleFrame_clicked();

    void on_pushButton_ContinuFrame_clicked();

private:
    bool AddTableFileValue(int index);
    bool AddTableDefectValue(const s_AlgDefectInfo &s_AlgDefectInfo);
private:
    Ui::AlgorithmTest *ui;
    QString m_FilePath;        //文件夹路径
    QStringList m_FileInfoList;//完整路径 队列
    QStringList m_FileNameList;//
    QStringList m_FileWidthHeightList;//
    QStringList m_FileBitcountList;//
    int m_iColumnCount;
    short m_iFileCount;
    std::vector<QImage> m_vecImg;
    QImage m_image;
    std::vector<int> m_vecImgSelected;
    std::vector<QString> m_PageName;
    int m_iPageNum;
    byte* m_pCurrentImgData;
    QByteArray m_pCurrentImgInfo;
    int m_iWidth;
    int m_iHeight;
    int m_iChannel;
    int m_iDepth;
    int m_iCurrentImgSize;

    int m_iPageIndex;
    double m_dbResolutionH;//横向分辨率 1个像素 mm
    double m_dbResolutionV;//纵向分辨率 1个像素 mm
    QString m_strParamPath; //参数路径 例如 D:/Bin/AlgConfig
    QString m_strModelPath; //模板路径 例如D:/User/Model/苹果x
    QString m_strLogPath;   //日志路径 例如 D:/User/Log/AlgLog
    //显示相关
    QTableWidget *m_pTableFiles;
    QTableWidget *m_pTableDefects;
    //算法相关
    CAlgInspector *AlgInspector;
    s_AlgInitParam m_sAlgInitParam;
    s_AlgCheckOutputParam m_sAlgOutParam;
    s_AlgCheckInputParam m_sAlgInParam;
    QVector<QRect> m_vecErrorRect;

    BITMAPFILEHEADER m_FILE_HEADER; //文件头;
    BITMAPINFOHEADER m_INFO_HEADER; //信息头;

};

#endif // ALGORITHMTEST_H
