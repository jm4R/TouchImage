#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QFrame>

namespace Ui {
class FilterWidget;
}

class FilterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit FilterWidget(QWidget *parent = 0);
    ~FilterWidget();

private:
    Ui::FilterWidget *ui;
};

#endif // FILTERWIDGET_H
