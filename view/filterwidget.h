#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QScroller>
#include "model/filter.h"

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

signals:
    void filterInvoked();
public slots:
    void setFilter(Filter *newFilter);
    void setImage(const QImage *newImage);

private:
    void refreshMiniature();
    Ui::FilterWidget *ui;
    Filter *filter;
    const QImage *image;
    QScroller *scroller;
};

#endif // FILTERWIDGET_H
