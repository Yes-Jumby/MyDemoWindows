
#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QPoint>
#include <QColor>
#include <QPaintEvent>
#include <QImage>
#include <QPixmap>
#include <QPen>
#include<QPainter>
#include <Windows.h>

class myLabel : public QLabel
{
    //Q_OBJECT  //<span style="color: #FF0000;">必须没有，要不然会报错，因为Label不是Widget等</span>
public:
    myLabel(QWidget *parent);
    ~myLabel();


    void ShowOriginalImage(QByteArray &image,int iWidth, int iHeight);
    void ShowAlgedImage(QVector<QRect> &vecError);
    //绘制线条
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    //设置所画线条属性
    void setLineColor(const QColor lineColor);
    void setLineSize(const int lineSize);
    //得到画线的起点和终点
    QPoint getStartPoint();
    QPoint getEndPoint();
    //将图片设置为背景
    void setImage(const QImage &pic);

    void clear();
    QImage Pk8bitGrayToQIm(const BYTE *pBuffer, const int &bufWidth, const int &bufHight ,const int &BitCount);
private:
    QPoint lineStartPoint;          //画线起点
    QPoint lineEndPoint;            //画线终点
    QColor lineColor;               //线条颜色
    QVector<QRect>  m_vecRect;
    int lineSize;                  //5种线型
    bool isPressed;
    QLabel *mylabel;
    QImage m_image;
    QVector<QRgb> vcolorTable; //生成灰度颜色表
    QSize m_size;
    double m_Hratio;
    double m_Wratio;
    double m_offset;
    bool m_bHratioMax;
};

#endif // MYLABEL_H
