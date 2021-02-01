#ifndef QWIDGETFORPCVIEW_H
#define QWIDGETFORPCVIEW_H
#include <QWidget>
#include <QWebEngineView>
#include <QUrl>
class QWidgetForPCView : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetForPCView(QWidget *parent = nullptr);
    //~QWidgetForPCView();
    void setDisplayWeb(const QUrl &url);
protected:
    void resizeEvent(QResizeEvent *);
private:
    QWebEngineView* m_webView;
};

#endif // QWIDGETFORPCVIEW_H
