#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QFrame>
#include <QColor>
#include "screenadapter.h"

namespace Ui {
class ColorWidget;
}

/**
 * @brief
 * Klasa odpowiadająca za wyświetlanie i zarządzanie widżetem wyboru koloru.
 */
class ColorWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = 0);
    ~ColorWidget();

signals:
    void colorChanged(QColor color);

public slots:
    void setHsv(int h, int s, int v);

private:
    Ui::ColorWidget *ui;
    QColor color;
    void refreshLabels();
};

#endif // COLORWIDGET_H
