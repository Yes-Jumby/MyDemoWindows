#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QStatusBar>
#include <QLabel>

#include "SpendTime.h"
class KeyEvent : public QWidget
{
    Q_OBJECT
    
public:
    KeyEvent(QWidget *parent = 0);
    ~KeyEvent();
    void keyPressEvent(QKeyEvent *);
private:    
    QLabel *statusLabel;
    QString m_Code;
    CSpendTime m_SpendTime;
    int m_iMiliSecond;
    bool m_bCodeStart;
    bool m_bCode;
    void TranslateCode(QString &strIn);
};

#endif // KEYEVENT_H
