#ifndef QWIDGETPROMOTED_H
#define QWIDGETPROMOTED_H

#include <QMainWindow>
#include "QWidgetReDesign.h"
namespace Ui {
class QwidgetPromoted;
}

class QwidgetPromoted : public QMainWindow
{
    Q_OBJECT

public:
    explicit QwidgetPromoted(QWidget *parent = 0);
    ~QwidgetPromoted();

private:
    Ui::QwidgetPromoted *ui;
};

#endif // QWIDGETPROMOTED_H
