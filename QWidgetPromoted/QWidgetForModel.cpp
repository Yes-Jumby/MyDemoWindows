#include "QWidgetForModel.h"
#include <QStyleOption>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QStaticText>
#include <QFontMetrics>

QWidgetForModel::QWidgetForModel(QWidget *parent) : QWidget(parent)
{

    m_pImage = std::make_shared<QImage>();
    m_vecDefectRectShow.clear();


//    m_ColorPlatFront = QColor(255,143,0); //正面颜色
//    m_ColorPlatBack = QColor(143,0,255); //背面
//    m_ColorFrame = QColor(255,0,0); //中框
//    m_ColorAngle = QColor(255,0,0); //R角
//    m_ColorCamera = QColor(255,0,0); //摄像头

}

bool QWidgetForModel::InitModelImageFile(QString strImageFile)
{
   if(m_pImage->load(strImageFile))
   {
       m_vecDefectRectShow.clear();
       //上表面
       m_iD[0] = QRect(291,92,72,150);
       m_iD[1] = QRect(291,242,72,132);
       m_iD[2] = QRect(291,372,72,140);
       m_iD[3] = QRect(223,372,67,140);
       m_iD[4] = QRect(150,372,73,140);
       m_iD[5] = QRect(150,242,73,132);
       m_iD[6] = QRect(150,92,73,150);
       m_iD[7] = QRect(223,92,67,150);
       m_iD[8] = QRect(223,242,67,132);
       m_iD[9] = QRect(212,102,14,14);
       m_iD[10] = QRect(228,102,14,14);
       m_iD[11] = QRect(243,104,27,9);
       m_iD[12] = QRect(270,102,14,14);
       m_iD[13] = QRect(284,102,14,14);

       //下表面
       m_iH[0] = QRect(700,92,72,150);//280+410
       m_iH[1] = QRect(700,242,72,132);
       m_iH[2] = QRect(700,372,72,136);
       m_iH[3] = QRect(633,372,65,136);
       m_iH[4] = QRect(560,372,72,136);
       m_iH[5] = QRect(560,242,72,132);
       m_iH[6] = QRect(560,92,72,150);
       m_iH[7] = QRect(633,92,65,150);
       m_iH[8] = QRect(633,242,65,132);

       m_iH[9] = QRect(576,107,40,40);
       m_iH[10] = QRect(590,145,10,10);
       m_iH[11] = QRect(588,155,15,15);
       m_iH[12] = QRect(640,195,55,55);
       m_iH[13] = QRect(640,390,50,20);

       //左边
       m_iL[0] = QRect(86,88,28,155);
       m_iL[1] = QRect(86,242,28,130);
       m_iL[2] = QRect(86,372,28,144);
       m_iL[3] = QRect(14,145,28,25);
       m_iL[4] = QRect(14,175,28,36);
       m_iL[5] = QRect(14,210,28,36);

       //右边
       m_iR[0] = QRect(410,88,26,155);
       m_iR[1] = QRect(410,242,26,130);
       m_iR[2] = QRect(410,372,26,144);
       m_iR[3] = QRect(487,182,26,54);
       m_iR[4] = QRect(487,380,26,54);
       //上边
       m_iT[0] = QRect(147,21,76,30);
       m_iT[1] = QRect(222,21,68,30);
       m_iT[2] = QRect(290,21,76,30);
       //下边
       m_iB[0] = QRect(147,535,76,30);
       m_iB[1] = QRect(222,535,68,30);
       m_iB[2] = QRect(290,535,76,30);
       m_iB[3] = QRect(188,590,40,30);
       m_iB[4] = QRect(227,590,17,30);
       m_iB[5] = QRect(240,590,30,30);
       m_iB[6] = QRect(268,590,17,30);
       m_iB[7] = QRect(284,590,40,30);
       update();
       return true;
   }
   return false;

}

bool QWidgetForModel::RemoveAllDefect()
{
    m_vecDefectRectShow.clear();
    update();
    return true;

}

bool QWidgetForModel::PushDefect(DEFECT_LOCATION_CODE enumDefectInfo)
{
    m_vecDefectRectShow.push_back(enumDefectInfo);
    update();
    return true;

}

bool QWidgetForModel::PushDefect(std::vector<DEFECT_LOCATION_CODE> &vecenumDefectInfo)
{
    for(int i = 0;i<vecenumDefectInfo.size();i++)
    {
        m_vecDefectRectShow.push_back(vecenumDefectInfo.at(i));
    }

    update();
    return true;

}

void QWidgetForModel::paintEvent(QPaintEvent *)
{

    QRect curRect;
    curRect.setLeft(0);
    curRect.setRight(size().width());
    curRect.setTop(0);
    curRect.setBottom(size().height());

    QPainter p(this);
    p.fillRect(curRect,QColor(255,255,255));


    if(m_pImage->isNull())
    {
        return;
    }

    QRectF targetRect,srcRect;
    float ftargetW_H = (float)curRect.width()/(float)curRect.height();
    float fimageW_H = (float)m_pImage->width()/(float)m_pImage->height();

    if(ftargetW_H > fimageW_H)//高正好，修改宽
    {
        int iWidth = fimageW_H * curRect.height();
        int iLeft = (curRect.width() - iWidth)/2;
        targetRect.setLeft(iLeft);
        targetRect.setRight(iLeft + iWidth);
        targetRect.setTop(curRect.top());
        targetRect.setBottom(curRect.bottom());

    }
    else
    {
        int iHeight = (float)curRect.width()/fimageW_H;
        int iLeft = (curRect.height() - iHeight)/2;
        targetRect.setLeft(curRect.left());
        targetRect.setRight(curRect.right());
        targetRect.setTop(curRect.top()+iLeft);
        targetRect.setBottom(curRect.top()+iLeft + iHeight);

    }

    srcRect.setLeft(0);
    srcRect.setRight(m_pImage->width());
    srcRect.setTop(0);
    srcRect.setBottom(m_pImage->height());

    p.drawImage(targetRect,*m_pImage.get(),srcRect);

    ///
    QPen Pen(QColor(255,0,0));
    Pen.setStyle(Qt::DashDotLine);
    Pen.setWidth(1);
    p.setPen(Pen);
    p.setFont(QFont("Arial", 10,QFont::DemiBold));

    QString sText;
    for(int i = 0;i<m_vecDefectRectShow.size();i++)
    {
        QRect recModleShow;

        switch(m_vecDefectRectShow.at(i))
        {
        case D1:
            recModleShow = m_iD[0];
            sText = QString("D1");
            break;
        case D2:
            recModleShow = m_iD[1];
            sText = QString("D2");
            break;
        case D3:
            recModleShow = m_iD[2];
            sText = QString("D3");
            break;
        case D4:
            recModleShow = m_iD[3];
            sText = QString("D4");
            break;
        case D5:
            recModleShow = m_iD[4];
            sText = QString("D5");
            break;
        case D6:
            recModleShow = m_iD[5];
            sText = QString("D6");
            break;
        case D7:
            recModleShow = m_iD[6];
            sText = QString("D7");
            break;
        case D8:
            recModleShow = m_iD[7];
            sText = QString("D8");
            break;
        case D9:
            recModleShow = m_iD[8];
            sText = QString("D9");
            break;
        case D10:
            recModleShow = m_iD[9];
            sText = QString("D10");
            break;
        case D11:
            recModleShow = m_iD[10];
            sText = QString("D11");
            break;
        case D12:
            recModleShow = m_iD[11];
            sText = QString("D12");
            break;
        case D13:
            recModleShow = m_iD[12];
            sText = QString("D13");
            break;
        case D14:
            recModleShow = m_iD[13];
            sText = QString("D14");
            break;
        case H1:
            recModleShow = m_iH[0];
            sText = QString("H1");
            break;
        case H2:
            recModleShow = m_iH[1];
            sText = QString("H2");
            break;
        case H3:
            recModleShow = m_iH[2];
            sText = QString("H3");
            break;
        case H4:
            recModleShow = m_iH[3];
            sText = QString("H4");
            break;
        case H5:
            recModleShow = m_iH[4];
            sText = QString("H5");
            break;
        case H6:
            recModleShow = m_iH[5];
            sText = QString("H6");
            break;
        case H7:
            recModleShow = m_iH[6];
            sText = QString("H7");
            break;
        case H8:
            recModleShow = m_iH[7];
            sText = QString("H8");
            break;
        case H9:
            recModleShow = m_iH[8];
            sText = QString("H9");
            break;
        case H10:
            recModleShow = m_iH[9];
            sText = QString("H10");
            break;
        case H11:
            recModleShow = m_iH[10];
            sText = QString("H11");
            break;
        case H12:
            recModleShow = m_iH[11];
            sText = QString("H12");
            break;
        case H13:
            recModleShow = m_iH[12];
            sText = QString("H13");
            break;
        case H14:
            recModleShow = m_iH[13];
            sText = QString("H14");
            break;
        case L1:
            recModleShow = m_iL[0];
            sText = QString("L1");
            break;
        case L2:
            recModleShow = m_iL[1];
            sText = QString("L2");
            break;
        case L3:
            recModleShow = m_iL[2];
            sText = QString("L3");
            break;
        case L4:
            recModleShow = m_iL[3];
            sText = QString("L4");
            break;
        case L5:
            recModleShow = m_iL[4];
            sText = QString("L5");
            break;
        case L6:
            recModleShow = m_iL[5];
            sText = QString("L6");
            break;
        case R1:
            recModleShow = m_iR[0];
            sText = QString("R1");
            break;
        case R2:
            recModleShow = m_iR[1];
            sText = QString("R2");
            break;
        case R3:
            recModleShow = m_iR[2];
            sText = QString("R3");
            break;
        case R4:
            recModleShow = m_iR[3];
            sText = QString("R4");
            break;
        case R5:
            recModleShow = m_iR[4];
            sText = QString("R5");
            break;
        case T1:
            recModleShow = m_iT[0];
            sText = QString("T1");
            break;
        case T2:
            recModleShow = m_iT[1];
            sText = QString("T2");
            break;
        case T3:
            recModleShow = m_iT[2];
            sText = QString("T3");
            break;
        case B1:
            recModleShow = m_iB[0];
            sText = QString("B1");
            break;
        case B2:
            recModleShow = m_iB[1];
            sText = QString("B2");
            break;
        case B3:
            recModleShow = m_iB[2];
            sText = QString("B3");
            break;
        case B4:
            recModleShow = m_iB[3];
            sText = QString("B4");
            break;
        case B5:
            recModleShow = m_iB[4];
            sText = QString("B5");
            break;
        case B6:
            recModleShow = m_iB[5];
            sText = QString("B6");
            break;
        case B7:
            recModleShow = m_iB[6];
            sText = QString("B7");
            break;
        case B8:
            recModleShow = m_iB[7];
            sText = QString("B8");
            break;
        default:
            continue;
            break;
        }
        QRect modlgRect;
        modlgRect.setLeft(targetRect.left()+recModleShow.left()*targetRect.width()/srcRect.width());
        modlgRect.setRight(targetRect.left()+recModleShow.right()*targetRect.width()/srcRect.width());
        modlgRect.setTop(targetRect.top()+recModleShow.top()*targetRect.height()/srcRect.height());
        modlgRect.setBottom(targetRect.top()+recModleShow.bottom()*targetRect.height()/srcRect.height());

        p.setPen(Pen);
        p.drawRect(modlgRect);

        p.setFont(QFont("Arial", 10,QFont::DemiBold));
        p.setRenderHint(QPainter::Antialiasing);
        QFontMetrics fm = p.fontMetrics();
        QStaticText staticText;
        switch(m_vecDefectRectShow.at(i))
        {
            case D10:
            case D13:
            case B4:
            case B7:
            case H13:
            case H10:
                p.fillRect(modlgRect.left()-fm.width(sText),modlgRect.top()-fm.height(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.left()-fm.width(sText),modlgRect.top()-fm.height(),staticText);
                break;
            case D11:
            case B5:
                p.fillRect(modlgRect.left()-fm.width(sText),modlgRect.bottom(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.left()-fm.width(sText),modlgRect.bottom(),staticText);
                break;
            case D12:
                p.fillRect(modlgRect.right()-fm.width(sText),modlgRect.bottom(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.right()-fm.width(sText),modlgRect.bottom(),staticText);
                break;
            case B6:
                p.fillRect(modlgRect.left()+5,modlgRect.bottom(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.left()+5,modlgRect.bottom(),staticText);
                break;
            case H11:
                p.fillRect(modlgRect.right(),modlgRect.top()-fm.height(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.right(),modlgRect.top()-fm.height(),staticText);
                break;
            case H12:
                p.fillRect(modlgRect.left()-fm.width(sText),modlgRect.bottom(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.left()-fm.width(sText),modlgRect.bottom(),staticText);
                break;
            default:
                p.fillRect(modlgRect.right(),modlgRect.bottom(),fm.width(sText),fm.height(),Pen.color());
                p.setPen(QPen(QColor(0,0,0)));
                staticText.setText(sText);
                p.drawStaticText(modlgRect.right(),modlgRect.bottom(),staticText);
                break;
        }


    }

}

