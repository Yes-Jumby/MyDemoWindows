#include "keyevent.h"
#include <QPainter>
#pragma execution_character_set("utf-8")
KeyEvent::KeyEvent(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("扫码枪测试[2648437]");
    statusLabel = new QLabel(this);
    statusLabel->setStyle(style());
    statusLabel->resize(300,50);
    statusLabel->setEnabled(true);
    statusLabel->setText(tr("Plz Insert Char!"));

    setMinimumSize(300,100);
    setMaximumSize(300,100);

    m_bCodeStart = true;
    m_bCode = false;
}

KeyEvent::~KeyEvent()
{
    
}

void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    if(m_bCodeStart)
    {
        if(event->nativeVirtualKey() == 16)//开头码
        {
            m_bCode = true;
            m_bCodeStart = false;
            m_SpendTime.Start();
            return;
        }
    }

    if(m_bCode)
    {
        if(event->nativeVirtualKey() != 13)
        {
            m_Code = m_Code + event->text();
        }
        else
        {
            m_iMiliSecond = m_SpendTime.End();
            if(m_Code.size() > 12)
            {
                TranslateCode(m_Code);
            }

            if(m_iMiliSecond < 1100)
            {
                statusLabel->setText(QString("条码：%1  耗时：%2ms[%3]").arg(m_Code).arg(m_iMiliSecond).arg(m_SpendTime.GetFrequency()));
            }
            else
            {
                statusLabel->setText(QString("键盘：%1  耗时：%2ms[%3]").arg(m_Code).arg(m_iMiliSecond).arg(m_SpendTime.GetFrequency()));
            }
            m_Code.clear();
            m_bCodeStart = true;
            m_bCode = false;
        }
    }
}
void KeyEvent::TranslateCode(QString &strIn)
{

    int index = 0;
    int pos = 0;
    int length = 0;
    for(int i = 0;i < strIn.size();i++)
    {
        if(strIn.at(i)==":")
        {
            index++;
            if(index==2)
            {
                pos = i + 1;
                continue;
            }
            if(index==3)
            {
                length = i - pos;
                break;
            }
        }
    }
    strIn = strIn.mid(pos,length);
}
