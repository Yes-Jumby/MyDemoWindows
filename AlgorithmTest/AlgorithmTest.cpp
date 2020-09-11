#include "AlgorithmTest.h"
#include "ui_AlgorithmTest.h"
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QHeaderView>//#注意设置表头时需要用到头文件
#include <QStandardItemModel>
#include <QFont>
#include <QList>
#include <QPainter>
#include <QSettings>
#include <QDebug>
#define WIDTH_BYTES(bits) (((bits) + 31) / 32 * 4)

AlgorithmTest::AlgorithmTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlgorithmTest)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(tr(":/image/res/imac.ico")));//设置应用程序图标
    //设置窗口有最小化按钮
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);


    //设置按钮状态
    ui->pushButton_selectFile->setEnabled(true);

    ui->pushButton_Init->setEnabled(false);//初始化算法
    ui->pushButton_CallAlgDlg->setEnabled(false);
    ui->pushButton_Alg->setEnabled(false);

    ui->pushButton_OriginalIMG->setEnabled(false);//显示图片

    ui->pushButton_PageIndex->setEnabled(false);//模板参数设置
    ui->pushButton_ResolutionH->setEnabled(false);
    ui->pushButton_ResolutionV->setEnabled(false);
    ui->pushButton_ParamPath->setEnabled(false);
    ui->pushButton_ModelPath->setEnabled(false);
    ui->pushButton_LogPath->setEnabled(false);

    ui->pushButton_SingleFrame->setEnabled(false);
    ui->pushButton_ContinuFrame->setEnabled(false);

    //初始化算法
    AlgInspector = new CAlgInspector();

    //初始化类成员变量
    m_pCurrentImgData = nullptr;
    m_iWidth = 0;
    m_iHeight = 0;
    m_iChannel = 0;
    m_iDepth = 0;
    m_iCurrentImgSize = 0;
    m_iFileCount = 0;
    //m_iPageIndex = 0;
    m_pCurrentImgData = nullptr;
    m_iColumnCount = 5;
    m_iPageNum = 0;
    //m_dbResolutionH = m_sAlgInitParam.dbResolutionH;
    //m_dbResolutionV = m_sAlgInitParam.dbResolutionV;
    m_vecErrorRect.clear();
    m_PageName.clear();
    //初始化画面号
    QSettings *configIniRead = new QSettings("./AlgorithmTest.ini", QSettings::IniFormat);
    m_iPageIndex = configIniRead->value("/AlgorithmParam/PageIndex").toInt();
    m_dbResolutionH = configIniRead->value("/AlgorithmParam/ResolutionH").toDouble();
    m_dbResolutionV = configIniRead->value("/AlgorithmParam/ResolutionV").toDouble();
    m_strParamPath = configIniRead->value("/AlgorithmParam/ParamPath").toString();
    m_strModelPath = configIniRead->value("/AlgorithmParam/ModelPath").toString();
    m_strLogPath = configIniRead->value("/AlgorithmParam/LogPath").toString();

    m_iPageNum = configIniRead->value("/BASE_PARAM/PAGE_NUM").toInt();
//    if(configIniRead != nullptr)
//    {
//        delete configIniRead;
//        configIniRead = nullptr;
//    }

    QString temp;
    for(int i=0;i<m_iPageNum;i++)
    {
        temp = tr("/PAGE_%1/PAGE_NAME").arg(i);
        m_PageName.push_back(configIniRead->value(temp).toString());
    }
    if(configIniRead != nullptr)
    {
        delete configIniRead;
        configIniRead = nullptr;
    }
    if(m_PageName.size() != m_iPageNum)
    {
        ui->textEdit_show->append("读取画面名称有误，请重启软件！");
    }

    QString str = tr("%1").arg(m_iPageIndex);
    ui->lineEdit_PageIndex->setText(str);
    str = tr("%1").arg(m_dbResolutionH);
    ui->lineEdit_ResolutionH->setText(str);
    str = tr("%1").arg(m_dbResolutionV);
    ui->lineEdit_ResolutionV->setText(str);
    str = tr("参数路径为:%1").arg(m_strParamPath);
    ui->textEdit_show->append(str);
    str = tr("模型路径为:%1").arg(m_strModelPath);
    ui->textEdit_show->append(str);
    str = tr("日志路径为:%1").arg(m_strLogPath);
    ui->textEdit_show->append(str);
    //初始化文件table
    m_pTableFiles = ui->tableWidget_file;
    QStringList header;
    m_pTableFiles->setColumnCount(m_iColumnCount);//设置列数
    header << tr("序号")<< tr("名称") << tr("分辨率") << tr("位数") << tr("位置");
    m_pTableFiles->setHorizontalHeaderLabels(header);
    m_pTableFiles->verticalHeader()->setVisible(false);//设置横排是否有行标题
    m_pTableFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);//编辑触发
    m_pTableFiles->setSelectionBehavior(QAbstractItemView::SelectRows);//选择整行/列
    m_pTableFiles->setSelectionMode(QAbstractItemView::SingleSelection);//是否可多选
    m_pTableFiles->setShowGrid(true);//显示表格线
    m_pTableFiles->setStyleSheet("gridline-color: rgb(210, 210, 210)");
    m_pTableFiles->verticalHeader()->setDefaultSectionSize(30); //设置行距
    m_pTableFiles->verticalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(229, 241, 251);}");
    m_pTableFiles->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    m_pTableFiles->horizontalHeader()->setDefaultAlignment (Qt::AlignCenter | Qt::AlignVCenter); //居左
    m_pTableFiles->horizontalHeader()->setTextElideMode (Qt::ElideRight); //...效果
    m_pTableFiles->horizontalHeader()->setStretchLastSection (true); //尾不留空白
    m_pTableFiles->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(229, 241, 251);"
                                                      " color: black;"
                                                      /*"border:1px solid rgb(229, 241, 251);"*/
                                                      "}");
    m_pTableFiles->horizontalHeader()->setHighlightSections(false);//点击表时不对表头行光亮（获取焦点）

    m_pTableFiles->setColumnWidth(0,40);
    m_pTableFiles->setColumnWidth(1,100);
    m_pTableFiles->setColumnWidth(2,100);
    m_pTableFiles->setColumnWidth(3,40);
    m_pTableFiles->setColumnWidth(4,100);
    m_pTableFiles->clearContents();
    m_pTableFiles->setRowCount(0);

    //初始化缺陷table
    m_pTableDefects = ui->tableWidget_defect;
    header.clear();
    m_pTableDefects->setColumnCount(10);//设置列数
    header<< tr("缺陷类型") << tr("画面号")<< tr("宽度") << tr("长度") << tr("面积") << tr("对比度")<< tr("圆度")<< tr("矩形度")<< tr("JND")<< tr("能量");
    m_pTableDefects->setHorizontalHeaderLabels(header);
    m_pTableDefects->verticalHeader()->setVisible(true);//设置横排是否有行标题
    m_pTableDefects->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableDefects->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableDefects->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableDefects->setShowGrid(true);//显示表格线
    m_pTableDefects->setStyleSheet("gridline-color: rgb(210, 210, 210)");
    m_pTableDefects->verticalHeader()->setDefaultSectionSize(30); //设置行距
    m_pTableDefects->verticalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(229, 241, 251);}");
    m_pTableDefects->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    m_pTableDefects->horizontalHeader()->setDefaultAlignment (Qt::AlignCenter | Qt::AlignVCenter); //居左
    m_pTableDefects->horizontalHeader()->setTextElideMode (Qt::ElideRight); //...效果
    m_pTableDefects->horizontalHeader()->setStretchLastSection (true); //尾不留空白
    m_pTableDefects->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(229, 241, 251);"
                                                      " color: black;"
                                                      /*"border:1px solid rgb(229, 241, 251);"*/
                                                      "}");
    m_pTableDefects->horizontalHeader()->setHighlightSections(false);//点击表时不对表头行光亮（获取焦点）

    m_pTableDefects->setColumnWidth(0,80);
    m_pTableDefects->setColumnWidth(1,60);
    m_pTableDefects->setColumnWidth(2,50);
    m_pTableDefects->setColumnWidth(3,50);
    m_pTableDefects->setColumnWidth(4,50);
    m_pTableDefects->setColumnWidth(5,60);
    m_pTableDefects->setColumnWidth(6,50);
    m_pTableDefects->setColumnWidth(7,60);
    m_pTableDefects->setColumnWidth(8,50);
    m_pTableDefects->setColumnWidth(9,50);
    m_pTableDefects->clearContents();
    m_pTableDefects->setRowCount(0);


}

AlgorithmTest::~AlgorithmTest()
{
    if(AlgInspector !=nullptr)
    {
        AlgInspector->Free();
		delete AlgInspector;
		AlgInspector = nullptr;
    }
    if(m_pCurrentImgData !=nullptr)
    {
        //delete []m_pCurrentImgData;
        m_pCurrentImgData = nullptr;
    }

    QSettings *config = new QSettings("./AlgorithmTest.ini", QSettings::IniFormat);
    //将信息写入配置文件
    config->beginGroup("AlgorithmParam");
    QString str = tr("%1").arg(m_iPageIndex);
    config->setValue("PageIndex", str);
    str = tr("%1").arg(m_dbResolutionH);
    config->setValue("ResolutionH", str);
    str = tr("%1").arg(m_dbResolutionV);
    config->setValue("ResolutionV", str);
    config->setValue("ParamPath", m_strParamPath);
    config->setValue("ModelPath", m_strModelPath);
    config->setValue("LogPath", m_strLogPath);
    config->endGroup();
    config->beginGroup("BASE_PARAM");
    str = tr("%1").arg(m_iPageNum);
    config->setValue("PAGE_NUM", str);
    config->endGroup();
    if(config !=nullptr)
    {
        delete config;
        config = nullptr;
    }
    delete ui;
}

void AlgorithmTest::on_pushButton_selectFile_clicked()//选择文件
{
    //清除列表
    m_pTableFiles->clearContents();
    m_pTableFiles->setRowCount(0);
    m_FileInfoList.clear();
    m_FileNameList.clear();
    m_FileBitcountList.clear();
    m_FileWidthHeightList.clear();
    //获取图像路径和名称 存到向量中
    QFileDialog *fileDialog = new QFileDialog(this);//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
    fileDialog->setDirectory("D:\\BZVisualInspect\\PICTURE");
    fileDialog->setWindowTitle(tr("Select Bmp"));//设置文件保存对话框的标题
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);//设置文件对话框为保存模式
    fileDialog->setFileMode(QFileDialog::Directory);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
    fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
    fileDialog->setFilter(QDir::Dirs);

    if(fileDialog->exec() == QDialog::Accepted)
    {
        m_FilePath = fileDialog->selectedFiles()[0];//得到用户选择的文件名
        ui->lineEdit_filePath->setText(m_FilePath);
    }

    QDir dir(m_FilePath);
    if (!dir.exists())
    {
        return ;
    }
    dir.setFilter(QDir::Dirs|QDir::NoDot|QDir::NoDotAndDotDot);//除了文件，其他的过滤掉
    QFileInfoList FileInfoList = dir.entryInfoList();//完整路径
    QStringList FileNameList=dir.entryList();//文件名
    QStringList FileNameList1;
    for(int i = 0; i<FileInfoList.size();i++)
    {
        dir.setPath(FileInfoList.at(i).filePath());
        dir.setFilter(QDir::Dirs|QDir::NoDot|QDir::NoDotAndDotDot);//除了文件，其他的过滤掉
        QStringList FileNameList2 = dir.entryList();
        QStringList Temp;

            for(int j =0;j<dir.entryList().size();j++)
            Temp.push_back(FileInfoList.at(i).filePath()+"/"+dir.entryList().at(j));

        FileNameList1=FileNameList1 +Temp;
    }

    QString  imgPath;
    m_iFileCount = FileInfoList.size();
    for(int i=0;i<m_iFileCount;i++)
    {
        imgPath = FileInfoList.at(i).filePath();
        m_FileInfoList.push_back(imgPath);
        m_FileNameList.push_back(FileNameList.at(i));
        //读取数据
        QFile *file = new QFile(imgPath);
        file->open(QFile::ReadOnly);
        QByteArray data = file->read(sizeof(BITMAPFILEHEADER));
        memcpy(&m_FILE_HEADER,data.constData(),sizeof(BITMAPFILEHEADER));
        if (m_FILE_HEADER.bfType != 0x4d42)
        {
            delete file;
            file = nullptr;
            break;
        }
        data = file->read(sizeof(BITMAPINFOHEADER));
        memcpy(&m_INFO_HEADER,data.constData(),sizeof(BITMAPINFOHEADER));
        m_iWidth = m_INFO_HEADER.biWidth;
        m_iHeight = m_INFO_HEADER.biHeight;
        m_iDepth = m_INFO_HEADER.biBitCount;
        m_iChannel = m_iDepth / 8;
        imgPath = tr("%1*%2").arg(m_INFO_HEADER.biWidth).arg(m_INFO_HEADER.biHeight);
        m_FileWidthHeightList.push_back(imgPath);
        imgPath = tr("%1").arg(m_INFO_HEADER.biBitCount);
        m_FileBitcountList.push_back(imgPath);
        AddTableFileValue(i);
    }
    if(fileDialog != nullptr)
    {
        delete fileDialog;
    }

    ui->pushButton_Init->setEnabled(true);//初始化算法

    ui->pushButton_PageIndex->setEnabled(true);//模板参数设置
    ui->pushButton_ResolutionH->setEnabled(true);
    ui->pushButton_ResolutionV->setEnabled(true);
    ui->pushButton_ParamPath->setEnabled(true);
    ui->pushButton_ModelPath->setEnabled(true);
    ui->pushButton_LogPath->setEnabled(true);

    //ui->pushButton_OriginalIMG->setEnabled(true);//显示图片
}

void AlgorithmTest::on_pushButton_PageIndex_clicked()//设置画面号
{
    m_iPageIndex = ui->lineEdit_PageIndex->text().toInt();
    QString str;
    str = tr("画面号设置为 %1 ！").arg(m_iPageIndex);
    ui->textEdit_show->append(str);
}

void AlgorithmTest::on_pushButton_SingleFrame_clicked()//单帧检测
{
    //读取图像数据
    QString str1 = m_FilePath + "/" + m_PageName.at(m_iPageIndex) + ".bmp";
    QFile *file = new QFile(str1);
    if(!file->open(QFile::ReadOnly))
    {
        delete file;
        file = nullptr;
        str1 = tr("画面号(%1):%2 打开失败！").arg(m_iPageIndex).arg(str1);
        ui->textEdit_show->append(str1);
        return;
    }
    m_pCurrentImgInfo = file->readAll();
    memcpy(&m_INFO_HEADER,&m_pCurrentImgInfo.constData()[sizeof(BITMAPFILEHEADER)],sizeof(BITMAPINFOHEADER));
    m_iWidth = m_INFO_HEADER.biWidth;
    m_iHeight = m_INFO_HEADER.biHeight;
    m_iDepth = m_INFO_HEADER.biBitCount;
    m_iChannel = m_iDepth / 8;
    m_pCurrentImgData = (byte*)&m_pCurrentImgInfo.constData()[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
    delete file;
    file = nullptr;
    //显示图像
    ui->label_1->ShowOriginalImage(m_pCurrentImgInfo,m_iWidth, m_iHeight);
    //设置算法输入参数
    m_sAlgInParam.vecPbuffer.clear();
    m_sAlgOutParam.vecDefInfo.clear();
    m_vecErrorRect.clear();

    m_sAlgInParam.strBatchNo = "0";
    m_sAlgInParam.strProductNo = "0";

    m_sAlgInParam.iPageIndex = m_iPageIndex;
    m_sAlgInParam.iImageHeight = m_iHeight;
    m_sAlgInParam.iImageWidth = m_iWidth;
    m_sAlgInParam.iImageChannel = m_iChannel;
    m_sAlgInParam.dbResolutionH = m_dbResolutionH;
    m_sAlgInParam.dbResolutionV = m_dbResolutionV;

    m_sAlgInParam.vecPbuffer.push_back(m_pCurrentImgData);
    m_sAlgInParam.sReferParam.bNeedRefParam = true;
    m_sAlgInParam.sReferParam.pInputParam = &m_sAlgInParam;
    m_sAlgInParam.sReferParam.pOutParam = &m_sAlgOutParam;


    //算法检测
    if(AlgInspector->GCheck(m_sAlgInParam, m_sAlgOutParam))
    {
		m_sAlgOutParam.eResultFlag = RESULT_OK;

        ui->textEdit_show->append(str1);
        ui->textEdit_show->append("单帧算法检测成功！");
        if(m_sAlgOutParam.eResultFlag == RESULT_OK)
        {
            ui->textEdit_show->append("该图像为良品！");
            return ;
        }
        else
        {
            int size = (int)m_sAlgOutParam.vecDefInfo.size();
            if(size > 0)
            {
                for(int i = 0; i < size ;i++)
                {
                    AddTableDefectValue(m_sAlgOutParam.vecDefInfo[i]);
                    ARect Arect = m_sAlgOutParam.vecDefInfo[i].nRect;
                    QRect rect;
                    rect.setLeft(Arect.left);
                    rect.setTop(Arect.top);
                    rect.setBottom(Arect.bottom);
                    rect.setRight(Arect.right);
                    m_vecErrorRect.push_back(rect);
                }
                ui->label_1->ShowAlgedImage(m_vecErrorRect);
                m_vecErrorRect.clear();
            }
        }
    }
    else
    {
        ui->textEdit_show->append("单帧算法检测失败！");
    }
}

void AlgorithmTest::on_pushButton_ContinuFrame_clicked()//多帧检测
{
    for(int i = 0; i < m_iPageNum;i++)
    {
        //读取图像数据
        QString str1 = m_FilePath + "/" + m_PageName.at(i) + ".bmp";
        QFile *file = new QFile(str1);
        if(!file->open(QFile::ReadOnly))
        {
            delete file;
            file = nullptr;
            str1 = tr("画面号(%1):%2 打开失败！").arg(i).arg(str1);
            ui->textEdit_show->append(str1);
            return;
        }
        m_pCurrentImgInfo = file->readAll();
        memcpy(&m_INFO_HEADER,&m_pCurrentImgInfo.constData()[sizeof(BITMAPFILEHEADER)],sizeof(BITMAPINFOHEADER));
        m_iWidth = m_INFO_HEADER.biWidth;
        m_iHeight = m_INFO_HEADER.biHeight;
        m_iDepth = m_INFO_HEADER.biBitCount;
        m_iChannel = m_iDepth / 8;
        m_pCurrentImgData = (byte*)&m_pCurrentImgInfo.constData()[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
        delete file;
        file = nullptr;
        //显示图像
        ui->label_1->ShowOriginalImage(m_pCurrentImgInfo,m_iWidth, m_iHeight);
        Sleep(1000);
        //设置算法输入参数
        m_sAlgInParam.vecPbuffer.clear();
        m_sAlgOutParam.vecDefInfo.clear();
        m_vecErrorRect.clear();

        m_sAlgInParam.strBatchNo = "0";
        m_sAlgInParam.strProductNo = "0";

        m_sAlgInParam.iPageIndex = i;
        m_sAlgInParam.iImageHeight = m_iHeight;
        m_sAlgInParam.iImageWidth = m_iWidth;
        m_sAlgInParam.iImageChannel = m_iChannel;
        m_sAlgInParam.dbResolutionH = m_dbResolutionH;
        m_sAlgInParam.dbResolutionV = m_dbResolutionV;

        m_sAlgInParam.vecPbuffer.push_back(m_pCurrentImgData);
        m_sAlgInParam.sReferParam.bNeedRefParam = true;
        m_sAlgInParam.sReferParam.pInputParam = &m_sAlgInParam;
        m_sAlgInParam.sReferParam.pOutParam = &m_sAlgOutParam;


        //算法检测
        if (AlgInspector->GCheck(m_sAlgInParam, m_sAlgOutParam))
		{
			m_sAlgOutParam.eResultFlag = RESULT_OK;
            str1 = tr("画面号(%1):%2 检测成功！").arg(i).arg(str1);
            ui->textEdit_show->append(str1);
            if(m_sAlgOutParam.eResultFlag == RESULT_OK)
            {
                ui->textEdit_show->append("该图像为良品！");
                //return ;
            }
            else
            {
                int size = (int)m_sAlgOutParam.vecDefInfo.size();
                if(size > 0)
                {
                    for(int i = 0; i < size ;i++)
                    {
                        AddTableDefectValue(m_sAlgOutParam.vecDefInfo[i]);
                        ARect Arect = m_sAlgOutParam.vecDefInfo[i].nRect;
                        QRect rect;
                        rect.setLeft(Arect.left);
                        rect.setTop(Arect.top);
                        rect.setBottom(Arect.bottom);
                        rect.setRight(Arect.right);
                        m_vecErrorRect.push_back(rect);
                    }
                    ui->label_1->ShowAlgedImage(m_vecErrorRect);
                    m_vecErrorRect.clear();
                }
            }
        }
        else
        {
            ui->textEdit_show->append("算法检测失败！");
        }
    }
}

void AlgorithmTest::on_pushButton_ResolutionH_clicked()//设置横向分辨率
{
    m_dbResolutionH = ui->lineEdit_ResolutionH->text().toDouble();
    QString str;
    str = tr("横向分辨率设置为 %1 ！").arg(m_dbResolutionH);
    ui->textEdit_show->append(str);
}

void AlgorithmTest::on_pushButton_ResolutionV_clicked()//设置纵向分辨率
{
    m_dbResolutionV = ui->lineEdit_ResolutionV->text().toDouble();
    QString str;
    str = tr("横向分辨率设置为 %1 ！").arg(m_dbResolutionV);
    ui->textEdit_show->append(str);
}

void AlgorithmTest::on_pushButton_ParamPath_clicked()//设置参数路径
{
    QFileDialog *fileDialog = new QFileDialog(this);//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
    fileDialog->setWindowTitle(tr("Select ParamPath"));//设置文件保存对话框的标题
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);//设置文件对话框为保存模式
    fileDialog->setFileMode(QFileDialog::DirectoryOnly);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
    fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString str = fileDialog->selectedFiles()[0];;//得到用户选择的文件名
        m_strParamPath = str;
        str = tr("设置参数路径为 %1 ！").arg(str);
        ui->textEdit_show->append(str);
    }
    if(fileDialog != nullptr)
    {
        delete fileDialog;
    }
}

void AlgorithmTest::on_pushButton_ModelPath_clicked()//设置模板路径
{
    QFileDialog *fileDialog = new QFileDialog(this);//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
    fileDialog->setWindowTitle(tr("Select ModelPath"));//设置文件保存对话框的标题
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);//设置文件对话框为保存模式
    fileDialog->setFileMode(QFileDialog::DirectoryOnly);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
    fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString str = fileDialog->selectedFiles()[0];;//得到用户选择的文件名
        m_strModelPath = str;
        str = tr("设置模板路径为 %1 ！").arg(str);
        ui->textEdit_show->append(str);
    }
    if(fileDialog != nullptr)
    {
        delete fileDialog;
    }
}

void AlgorithmTest::on_pushButton_LogPath_clicked()//设置日志路径
{
    QFileDialog *fileDialog = new QFileDialog(this);//创建一个QFileDialog对象，构造函数中的参数可以有所添加。
    fileDialog->setWindowTitle(tr("Select LogPath"));//设置文件保存对话框的标题
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);//设置文件对话框为保存模式
    fileDialog->setFileMode(QFileDialog::DirectoryOnly);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
    fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString str = fileDialog->selectedFiles()[0];;//得到用户选择的文件名
        m_strLogPath = str;
        str = tr("设置日志路径为 %1 ！").arg(str);
        ui->textEdit_show->append(str);
    }
    if(fileDialog != nullptr)
    {
        delete fileDialog;
    }
}
void AlgorithmTest::on_pushButton_Init_clicked()//初始化算法
{
    m_sAlgInitParam.iPageIndex = m_iPageIndex;
    m_sAlgInitParam.iImageHeight = m_iHeight;
    m_sAlgInitParam.iImageWidth = m_iWidth;
    m_sAlgInitParam.iImageChannel = m_iChannel;
    m_sAlgInitParam.dbResolutionH = m_dbResolutionH;
    m_sAlgInitParam.dbResolutionV = m_dbResolutionV;
    m_sAlgInitParam.strLogPath = "0";
    m_sAlgInitParam.strModelPath = "0";
    m_sAlgInitParam.strParamPath = "0";
//    if(AlgInspector->Init(m_sAlgInitParam))
    if(true)
    {
        ui->textEdit_show->append("算法初始化成功！");
        ui->pushButton_CallAlgDlg->setEnabled(true);
        ui->pushButton_OriginalIMG->setEnabled(true);//显示图片
        ui->pushButton_SingleFrame->setEnabled(true);
        ui->pushButton_ContinuFrame->setEnabled(true);
    }
    else
    {
        ui->textEdit_show->append("算法初始化失败！");
    }
}

void AlgorithmTest::on_pushButton_Alg_clicked()//算法检测
{
    //设置算法输入参数
    m_sAlgInParam.vecPbuffer.clear();
    m_sAlgOutParam.vecDefInfo.clear();

    m_sAlgInParam.strBatchNo = "0";
    m_sAlgInParam.strProductNo = "0";

    m_sAlgInParam.iPageIndex = m_iPageIndex;
    m_sAlgInParam.iImageHeight = m_iHeight;
    m_sAlgInParam.iImageWidth = m_iWidth;
    m_sAlgInParam.iImageChannel = m_iChannel;
    m_sAlgInParam.dbResolutionH = m_dbResolutionH;
    m_sAlgInParam.dbResolutionV = m_dbResolutionV;

    m_sAlgInParam.vecPbuffer.push_back(m_pCurrentImgData);
    m_sAlgInParam.sReferParam.bNeedRefParam = true;
    m_sAlgInParam.sReferParam.pInputParam = &m_sAlgInParam;
    m_sAlgInParam.sReferParam.pOutParam = &m_sAlgOutParam;

    //算法检测
    if(AlgInspector->GCheck(m_sAlgInParam, m_sAlgOutParam))
    {

        ui->textEdit_show->append("算法检测成功！");
        if(m_sAlgOutParam.eResultFlag == RESULT_OK)
        {
            ui->textEdit_show->append("该图像为良品！");
            return ;
        }
        else
        {
            int size = (int)m_sAlgOutParam.vecDefInfo.size();
            if(size > 0)
            {
                for(int i = 0; i < size ;i++)
                {
                    AddTableDefectValue(m_sAlgOutParam.vecDefInfo[i]);
                    ARect Arect = m_sAlgOutParam.vecDefInfo[i].nRect;
                    QRect rect;
                    rect.setLeft(Arect.left);
                    rect.setTop(Arect.top);
                    rect.setBottom(Arect.bottom);
                    rect.setRight(Arect.right);
                    m_vecErrorRect.push_back(rect);
                }
                ui->label_1->ShowAlgedImage(m_vecErrorRect);
                m_vecErrorRect.clear();
            }
        }
    }
    else
    {
        ui->textEdit_show->append("算法检测失败！");
    }

}

void AlgorithmTest::on_pushButton_CallAlgDlg_clicked()
{
    s_StatusModelDlg s = AlgInspector->CallAlgModelDlg();
}

void AlgorithmTest::on_pushButton_OriginalIMG_clicked()//选择 显示原始图片
{
    //选择图像
    m_vecImgSelected.clear();
    QList<QTableWidgetItem*> items = m_pTableFiles->selectedItems();
    int item_count = items.count();
    if(item_count <= 0)
    {
        ui->textEdit_show->append("请先选择一张照片！");
        return;
    }
    for(int i=0; i <item_count;i += m_iColumnCount)
    {
        //获取选中的行
        m_vecImgSelected.push_back(m_pTableFiles->row(items.at(i)));
    }

    for(int i=0;i<m_vecImgSelected.size();i++)
    {
        QFile *file = new QFile(m_FileInfoList.at(m_vecImgSelected.at(i)));
        if(!file->open(QFile::ReadOnly))
        {
            delete file;
            QString str;
            str = tr("%1 打开失败！").arg(m_FileInfoList.at(m_vecImgSelected.at(i)));
            ui->textEdit_show->append(str);
            file = nullptr;
            return;
        }
        m_pCurrentImgInfo = file->readAll();
        memcpy(&m_INFO_HEADER,&m_pCurrentImgInfo.constData()[sizeof(BITMAPFILEHEADER)],sizeof(BITMAPINFOHEADER));
        m_iWidth = m_INFO_HEADER.biWidth;
        m_iHeight = m_INFO_HEADER.biHeight;
        m_iDepth = m_INFO_HEADER.biBitCount;
        m_iChannel = m_iDepth / 8;
        m_pCurrentImgData = (byte*)&m_pCurrentImgInfo.constData()[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
        if(file != nullptr)
        {
            delete file;
            file = nullptr;
        }
    }

    //显示图像
    ui->label_1->ShowOriginalImage(m_pCurrentImgInfo,m_iWidth, m_iHeight);
    QString str;
    str = tr("%1 显示成功！").arg(m_FileInfoList.at(m_vecImgSelected.at(0)));
    ui->textEdit_show->append(str);

    ui->pushButton_Alg->setEnabled(true);

}

bool AlgorithmTest::AddTableFileValue(int index)
{
    int iRowCount = m_pTableFiles->rowCount();
    m_pTableFiles->setRowCount(iRowCount+1);
    QString str;
    QColor colorGrade = QColor(255,255,255);
    str = tr("%1").arg(index+1);
    QTableWidgetItem *itemClass = new QTableWidgetItem;
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableFiles->setItem(iRowCount, 0, itemClass);

    itemClass = new QTableWidgetItem;
    itemClass->setText(m_FileNameList.at(index));
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableFiles->setItem(iRowCount, 1, itemClass);

    itemClass = new QTableWidgetItem;
    itemClass->setText(m_FileWidthHeightList.at(index));
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableFiles->setItem(iRowCount, 2, itemClass);

    itemClass = new QTableWidgetItem;
    itemClass->setText(m_FileBitcountList.at(index));
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableFiles->setItem(iRowCount, 3, itemClass);

    itemClass = new QTableWidgetItem;
    itemClass->setText(m_FileInfoList.at(index));
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableFiles->setItem(iRowCount, 4, itemClass);

    return true;
}

bool AlgorithmTest::AddTableDefectValue(const s_AlgDefectInfo &s_AlgDefectInfo)
{
    int iRowCount = m_pTableDefects->rowCount();
    m_pTableDefects->setRowCount(iRowCount+1);

    QString str;
    QColor colorGrade = QColor(255,255,255);
    switch (s_AlgDefectInfo.iDefectID)
    {
        case 0:
            str = tr("[良品]");
            break;
        case 1:
            str = tr("[划伤]");
            colorGrade = QColor(255,0,0);
            break;
        case 2:
            str = tr("[灰尘]");
            colorGrade = QColor(255,0,0);
            break;
        case 3:
            str = tr("[脏污]");
            colorGrade = QColor(255,0,0);
            break;
        case 4:
            str = tr("[崩边]");
            colorGrade = QColor(200,0,0);
            break;
        case 5:
            str = tr("[白点]");
            colorGrade = QColor(200,0,0);
            break;
        case 6:
            str = tr("[异物]");
            colorGrade = QColor(200,0,0);
            break;
        case 7:
            str = tr("[雨滴]");
            colorGrade = QColor(200,0,0);
            break;
        case 8:
            str = tr("[缺失]");
            colorGrade = QColor(200,0,0);
            break;
        default:
           str = tr("[未知]");
           colorGrade = QColor(100,100,0);
           break;
    }
    QTableWidgetItem *itemClass = new QTableWidgetItem;
    itemClass = new QTableWidgetItem;
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 0, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.nId);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 1, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fWidth);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 2, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fLength);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 3, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fArea);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 4, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fConstract);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 5, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fCirRat);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 6, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fRectRat);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 7, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fJnd);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 8, itemClass);

    itemClass = new QTableWidgetItem;
    str = tr("%1").arg(s_AlgDefectInfo.fEnergy);
    itemClass->setText(str);
    itemClass->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemClass->setBackgroundColor(colorGrade);
    m_pTableDefects->setItem(iRowCount, 9, itemClass);

    return true;
}
