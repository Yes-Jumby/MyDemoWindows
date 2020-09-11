#ifndef QWIDGETREDESIGN_H
#define QWIDGETREDESIGN_H

#include <QWidget>
#include "QwidgetForModel.h"
namespace Ui {
class CQwidgetReDesign;
}

class CQwidgetReDesign : public QWidget
{
    Q_OBJECT

public:
    explicit CQwidgetReDesign(QWidget *parent = nullptr);
    ~CQwidgetReDesign();

private:
    Ui::CQwidgetReDesign *ui;
    QWidgetForModel* m_pWidgetForModelImagePromoted;
    std::shared_ptr<QWidgetForModel> m_pWidgetForModelImageDirectred1;
    std::shared_ptr<QWidgetForModel> m_pWidgetForModelImageDirectred2;
};

#endif // QWIDGETREDESIGN_H
