#ifndef QWIDGETFORMODEL_H
#define QWIDGETFORMODEL_H

#include <QWidget>
#include <QImage>
#include <memory>
#include "GIDataType.h"
#include <QPen>

class QWidgetForModel : public QWidget
{
    Q_OBJECT


public:
    explicit QWidgetForModel(QWidget *parent = nullptr);

    bool InitModelImageFile(QString strImageFile);

    //清空缺陷
    bool RemoveAllDefect();

    //添加缺陷
    bool PushDefect(DEFECT_LOCATION_CODE enumDefectInfo);
    bool PushDefect(std::vector<DEFECT_LOCATION_CODE> &vecenumDefectInfo);

protected:
    void paintEvent(QPaintEvent *);
    //////////////////////////////////////////////

    std::shared_ptr<QImage> m_pImage;

    std::vector<DEFECT_LOCATION_CODE> m_vecDefectRectShow;

    QColor m_ColorD;
    QColor m_ColorH;
    QColor m_ColorT;
    QColor m_ColorB;
    QColor m_ColorL;
    QColor m_ColorR;

    //正面
    QRect m_iD[14];
    //背面
    QRect m_iH[14];

    //上面
    QRect m_iT[3];
    //下面
    QRect m_iB[8];
    //左面
    QRect m_iL[6];
    //右面
    QRect m_iR[5];
signals:

public slots:
};

#endif // QWIDGETFORMODELIMAGE_H
