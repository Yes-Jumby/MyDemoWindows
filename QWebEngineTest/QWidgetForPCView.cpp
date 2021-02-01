#include "QWidgetForPCView.h"


QWidgetForPCView::QWidgetForPCView(QWidget *parent) : QWidget(parent),
    m_webView(nullptr)
{
    m_webView = new QWebEngineView(this);

    //m_webView->show();
}
//QWidgetForPCView::~QWidgetForPCView()
//{
//    if(m_webView != nullptr)
//    {
//        m_webView->deleteLater();
//    }
//}
void QWidgetForPCView::setDisplayWeb(const QUrl &url)
{
    if(m_webView != nullptr)
    {
        m_webView->load(url);
    }
}
void QWidgetForPCView::resizeEvent(QResizeEvent *)
{
    if(m_webView != nullptr)
    {
        m_webView->resize(this->size());
    }
}
