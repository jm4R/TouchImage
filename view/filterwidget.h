#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QScroller>

namespace Ui {
class FilterWidget;
}

class FilterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit FilterWidget(QWidget *parent = 0);
    ~FilterWidget();

    void putButtonGroup(const QButtonGroup &buttonGroup);
    void setMenuHeight(int newHeight);

private:
    Ui::FilterWidget *ui;
};

#endif // FILTERWIDGET_H
