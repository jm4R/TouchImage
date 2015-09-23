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

/**
 * @brief
 * Klasa odpowiadająca za wyświetlanie i zarządzanie widżetem wyboru i nakładania filtrów.
 */
class FilterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit FilterWidget(QWidget *parent = 0);
    ~FilterWidget();

    void putButtonGroup(const QButtonGroup &buttonGroup);
    void setMenuHeight(int newHeight);

protected:
    virtual void resizeEvent(QResizeEvent *);
signals:
    void filterInvoked();
public slots:
    void setFilter(Filter *newFilter);
    void setImage(QImage *newImage);

private slots:
    void changeParameterValue();

private:
    void refreshMiniature();
    Ui::FilterWidget *ui;
    Filter *filter;
    const QImage *image;
};

#endif // FILTERWIDGET_H
