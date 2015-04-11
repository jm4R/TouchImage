#include "filterwidget.h"
#include "ui_filterwidget.h"

FilterWidget::FilterWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FilterWidget)
{
    ui->setupUi(this);
    QScroller::grabGesture(ui->menuScrollArea, QScroller::LeftMouseButtonGesture);
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::putButtonGroup(const QButtonGroup &buttonGroup)
{
    QWidget *widget = ui->menuScrollArea->widget();
    if (!widget->layout()) {
        widget->setLayout(new QHBoxLayout());
    }
    foreach(QAbstractButton *button, buttonGroup.buttons()) {
        button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        button->setMinimumWidth(ui->menuScrollArea->minimumHeight());
        widget->layout()->addWidget(button);
    }
    repaint();
}

void FilterWidget::setMenuHeight(int newHeight)
{
    ui->menuScrollArea->setMinimumHeight(newHeight);
}
