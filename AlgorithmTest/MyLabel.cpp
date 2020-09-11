
#include "myLabel.h"


myLabel::myLabel(QWidget *parent):
    QLabel(parent)
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    lineColor = QColor(Qt::red);
    lineSize = 1;
    m_vecRect.clear();

    m_Hratio = 0.0;
    m_Wratio = 0.0;
    m_offset = 0.0;
    m_bHratioMax = false;
    //初始化调色板
    for (int i = 0; i < 256; i++)
    {
        vcolorTable.append(qRgb(i, i, i));
    }
}

myLabel::~myLabel()
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    lineColor = QColor(Qt::red);
    lineSize = 1;
    m_image.~QImage();
}

void myLabel::ShowOriginalImage(QByteArray &image,int iWidth, int iHeight)
{
    m_size = size();
    //m_image.loadFromData((uchar *)image.data(),image.size());
    m_image.loadFromData(image);
    setPixmap(QPixmap::fromImage(m_image.scaled(m_size, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    this->setAlignment(Qt::AlignCenter);
    m_Hratio = 1.0 * iHeight / m_size.height();
    m_Wratio = 1.0 * iWidth / m_size.width();
    if(m_Hratio >= m_Wratio)
    {
        m_offset = m_size.width()/2 - iWidth/m_Hratio/2;
        m_bHratioMax = true;
    }
    else
    {
        m_offset = m_size.height()/2 - iHeight/m_Hratio/2;
        m_bHratioMax = false;
    }
}

void myLabel::ShowAlgedImage(QVector<QRect> &vecError)
{
    m_vecRect.clear();
    m_vecRect = vecError;
//    QRect rect;
//    rect.setLeft(100);
//    rect.setTop(100);
//    rect.setRight(1900);
//    rect.setBottom(10900);
//    m_vecRect.push_back(rect);
//    m_bHratioMax = true;
    if(m_bHratioMax)
    {
        for(int i = 0;i<m_vecRect.size();i++)
        {
            m_vecRect[i].setLeft(m_vecRect[i].left()/m_Hratio + m_offset);
            m_vecRect[i].setTop(m_vecRect[i].top()/m_Hratio);
            m_vecRect[i].setRight(m_vecRect[i].right()/m_Hratio + m_offset);
            m_vecRect[i].setBottom(m_vecRect[i].bottom()/m_Hratio);
        }
    }
    else
    {
        for(int i = 0;i<m_vecRect.size();i++)
        {
            m_vecRect[i].setLeft(m_vecRect[i].left()/m_Hratio);
            m_vecRect[i].setTop(m_vecRect[i].top()/m_Hratio + m_offset);
            m_vecRect[i].setRight(m_vecRect[i].right()/m_Hratio);
            m_vecRect[i].setBottom(m_vecRect[i].bottom()/m_Hratio + m_offset);
        }
    }
    update();//绘制矩形

}
//绘制线条
void myLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);//<span style="color: #FF0000;">必须有，才能让自己设置的背景图片显示出来</span>
    QPainter painter(this);
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(lineSize);
    painter.setPen(pen);
    painter.drawRects(m_vecRect);
}


void myLabel::setLineColor(const QColor lineColor)
{
    this->lineColor = lineColor;
}

void myLabel::setLineSize(const int lineSize)
{
    this->lineSize = lineSize;
}

QPoint myLabel::getStartPoint()
{
    return lineStartPoint;
}

QPoint myLabel::getEndPoint()
{
    return lineEndPoint;
}

void myLabel::setImage(const QImage &pic)
{
    this->setPixmap(QPixmap::fromImage(pic));
}

void myLabel::clear()
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    update();
}

QImage myLabel::Pk8bitGrayToQIm(const BYTE *pBuffer, const int &bufWidth, const int &bufHight ,const int &BitCount)
{
    //对参数的有效性进行检查
    Q_ASSERT((pBuffer != NULL) && (bufWidth > 0) && (bufHight > 0));
    int biBitCount = BitCount; //灰度图像像素bit数
    int lineByte = (bufWidth * biBitCount/8 + 3) / 4 * 4; //bmp行byte数（格式宽度，为4的倍数）
    if (bufWidth == lineByte) //判断图像宽度与格式宽度
    {
        QImage qIm = QImage(pBuffer, bufWidth, bufHight, QImage::Format_Indexed8);  //封装QImage
        qIm.setColorTable(vcolorTable); //设置颜色表
        return qIm;
    }
    else
    {
        BYTE *qImageBuffer = new BYTE[lineByte * bufHight]; //分配内存空间
        uchar *QImagePtr = qImageBuffer;
        for (int i = 0; i < bufHight; i++) //Copy line by line
        {
            memcpy(QImagePtr, pBuffer, bufWidth);
            QImagePtr += lineByte;
            pBuffer += bufWidth;
        }
        QImage qImage = QImage(qImageBuffer, bufWidth, bufHight, QImage::Format_Indexed8);  //封装QImage
        qImage.setColorTable(vcolorTable); //设置颜色表
        return qImage;
    }
}
