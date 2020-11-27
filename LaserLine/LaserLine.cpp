//#include "stdafx.h"
#include "LaserLine.h"

LaserLine::LaserLine(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.lineEdit_ThresholdValue->setValidator(new QIntValidator(0, 255, this));//������ֵ���뷶Χ
    ui.lineEdit_ThresholdValue->setText("100");//��ֵĬ��ֵ��Ϊ100
    m_iThresHoldValue = 100;

    connect(ui.pushButton_LoadImg, SIGNAL(clicked()), this, SLOT(OnLoadImg()));
    connect(ui.pushButton_RotateImg, SIGNAL(clicked()), this, SLOT(OnRotateImg()));
    connect(ui.lineEdit_ThresholdValue, SIGNAL(editingFinished()), this, SLOT(OnThresholdValue()));
    connect(ui.pushButton_ReIdentifi, SIGNAL(clicked()), this, SLOT(OnReIdentifi()));
}

void LaserLine::LabelDisplayMat(QLabel *label, cv::Mat &mat)
{
    cv::Mat Rgb;
    QImage Img;
    if (mat.channels() == 3)//RGB Img
    {
        cv::cvtColor(mat, Rgb, CV_BGR2RGB);//��ɫ�ռ�ת��
        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
    }
    else//Gray Img
    {
        Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(Img.
                                        scaled(label->size(),
                                               Qt::KeepAspectRatio,
                                               Qt::SmoothTransformation)));
}

void LaserLine::OnLoadImg()
{
    QString SrcImgName = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Images (*.png *.bmp *.jpg *.tif)"));//ѡ��ͼƬ·��
    if (SrcImgName.isEmpty())
    {
        return;
    }
    m_strSrcImgName = SrcImgName.toStdString();
    m_mSrcImg = cv::imread(m_strSrcImgName, 1);
    ProcessSrcImg();
}

void LaserLine::ProcessSrcImg()
{
    LabelDisplayMat(ui.label_SrcImg, m_mSrcImg);//չʾԭͼ
    cv::Mat Grayimg;
    cvtColor(m_mSrcImg, Grayimg, CV_BGR2GRAY);//ԭͼ��ת��Ϊ�Ҷ�ͼ
    //blur(Grayimg, m_mSmoothImg, Size(3, 3), Point(-1, -1));
    GaussianBlur(Grayimg, m_mSmoothImg, cv::Size(9, 9), 0, 0);//ƽ��ȥ�롪����˹�˲�
    ProcessThreshold();
}

void LaserLine::OnRotateImg()
{
    if (m_mSrcImg.empty() || !m_mSrcImg.data)//�ж�ԭͼ�Ƿ��Ѽ��سɹ�
    {
        return;
    }
    cv::Point2f center = cv::Point2f(m_mSrcImg.cols / 2, m_mSrcImg.rows / 2);//��ת����
    cv::Mat rotateMat = getRotationMatrix2D(center, 90, 1);
    cv::Mat tmpSrcImg;
    warpAffine(m_mSrcImg, tmpSrcImg, rotateMat, m_mSrcImg.size());
    m_mSrcImg = tmpSrcImg;
    ProcessSrcImg();
}

void LaserLine::OnThresholdValue()
{
    int ThresholeValue = ui.lineEdit_ThresholdValue->text().toInt();
    if (m_iThresHoldValue != ThresholeValue)//�ж���ֵ�Ƿ�ı�
    {
        m_iThresHoldValue = ThresholeValue;
        if (m_mSrcImg.empty() || !m_mSrcImg.data)//�ж�ԭͼ�Ƿ��Ѽ��سɹ�
        {
            return;
        }
    }
    ProcessThreshold();
}

void LaserLine::ProcessThreshold()
{
    cv::threshold(m_mSmoothImg, m_mThresholdImg, m_iThresHoldValue, 255, cv::THRESH_TOZERO);//���ֶ�ֵ��ͼ��
    LabelDisplayMat(ui.label_GrayImg, m_mThresholdImg);//չʾ���ֶ�ֵ��ͼ��
    ProcessIdentifi();
}

void LaserLine::OnReIdentifi()
{
    ProcessThreshold();
//    if (m_mThresholdImg.empty() || !m_mThresholdImg.data)//�жϲ��ֶ�ֵ��ͼ�Ƿ��Ѽ��سɹ�
//    {
//        return;
//    }
//    ProcessIdentifi();
}

void LaserLine::ProcessIdentifi()
{

    cv::Mat stats, centroids, sensor_color;
    sensor_color = cv::Mat::zeros(m_mThresholdImg.size(), CV_8UC3);
    cv::Mat labels;
    int n_comps = cv::connectedComponentsWithStats(
        m_mThresholdImg, //��ֵͼ��
        labels,     //��ԭͼһ����ı��ͼ
        stats, //nccomps��5�ľ��� ��ʾÿ����ͨ�������Ӿ��κ������pixel��
        centroids //nccomps��2�ľ��� ��ʾÿ����ͨ���������
    );
    ui.textEdit->append(QString("src regions:%1").arg(n_comps));
    //��ʼ����ɫ��
    vector<cv::Vec3b> colors(n_comps);
    colors[0] = cv::Vec3b(0, 0, 0); // background pixels remain black
    for (int i = 1; i < n_comps; i++) {
        colors[i] = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
    }
    for (int y = 0; y < sensor_color.rows; y++)
        for (int x = 0; x < sensor_color.cols; x++)
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= n_comps);
            sensor_color.at<cv::Vec3b>(y, x) = colors[label];
        }
    LabelDisplayMat(ui.label_SrcImg, sensor_color);
    cv::imwrite("D:\\Stereo3D\\data\\DemoIMG\\sensor_color.bmp", sensor_color);

    vector<int> region_size(n_comps);
    for (int i = 0; i < n_comps; i++) {
        region_size.push_back(stats.at<int>(i, cv::CC_STAT_AREA));
        ui.textEdit->append(QString("src regions size:%1").arg(stats.at<int>(i, cv::CC_STAT_AREA)));
    }
    sort(region_size.begin(), region_size.end(), greater<int>());
    int size_threod = region_size.at(1)*0.8;
    cout << size_threod << endl;
    for (int i = 1; i < n_comps; i++) {
        colors[i] = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
        if (stats.at<int>(i, cv::CC_STAT_AREA) < size_threod)
            colors[i] = cv::Vec3b(0, 0, 0); // small regions are painted with black too.
    }

    //����labelֵ���Բ�ͬ����ͨ�������ɫ
    for (int y = 0; y < sensor_color.rows; y++)
        for (int x = 0; x < sensor_color.cols; x++)
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= n_comps);
            sensor_color.at<cv::Vec3b>(y, x) = colors[label];
        }

    LabelDisplayMat(ui.label_GrayImg, sensor_color);
    cv::imwrite("D:\\Stereo3D\\data\\DemoIMG\\sensor_color_reduced.bmp", sensor_color);
    //ͳ�ƽ�������ͨ����
    cv::cvtColor(sensor_color, m_mThresholdImg, cv::COLOR_BGR2GRAY);
    cv::threshold(m_mThresholdImg, m_mThresholdImg, 0, 255, cv::THRESH_BINARY);


    cv::Mat linePre(m_mThresholdImg.rows, m_mThresholdImg.cols, CV_8UC1, cv::Scalar(0));
    for (int i = 0; i < linePre.cols; i++)
    {
        long long syp = 0, sp = 0, ypos;
        for (int j = 0; j < linePre.rows; j++)
        {
            syp += (j*(long long)(m_mThresholdImg.at<uchar>(j, i)));
            sp += (long long)(m_mThresholdImg.at<uchar>(j, i));
        }
        if (sp)
        {
            ypos = syp / sp;//ypos��Ϊÿһlie����������
            linePre.at<uchar>(ypos, i) = 255;//������ͼ����DstImg���ð׵��ʶ����
        }
    }
//    for (int i = 0; i < DstImg.rows; i++)
//    {
//        long long sxp = 0, sp = 0, xpos;
//        for (int j = 0; j < DstImg.cols; j++)
//        {
//            sxp += (j*(long long)(m_mThresholdImg.at<uchar>(i, j)));
//            sp += (long long)(m_mThresholdImg.at<uchar>(i, j));
//        }
//        if (sp)
//        {
//            xpos = sxp / sp;//xpos��Ϊÿһ�е���������
//            DstImg.at<uchar>(i, xpos) = 255;//������ͼ����DstImg���ð׵��ʶ����
//        }
//    }


    cv::imwrite("D:\\Stereo3D\\data\\DemoIMG\\ProcessIdentifi.bmp", linePre);
    LabelDisplayMat(ui.label_DstImg, linePre);
}
