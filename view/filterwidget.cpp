#include "filterwidget.h"
#include "ui_filterwidget.h"
#include <QDebug>

FilterWidget::FilterWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FilterWidget),
    filter(0),
    image(0)
{
    ui->setupUi(this);
    QScroller::grabGesture(ui->menuScrollArea, QScroller::LeftMouseButtonGesture);
    connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(filterInvoked()));
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
        button->setParent(ui->menuScrollArea);
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

void FilterWidget::setFilter(Filter *newFilter)
{
    filter = newFilter;
    refreshMiniature();
}

void FilterWidget::setImage(const QImage *newImage)
{
    image = newImage;
    refreshMiniature();
}

void FilterWidget::refreshMiniature()
{
    if (!filter || !image) {
        return;
    }
    QImage filteredImage = image->scaled(ui->label->size(), Qt::KeepAspectRatio);
    filter->setImage(&filteredImage);
    filter->process();
    filter->wait();
    QPixmap miniature;
    miniature.convertFromImage(filteredImage);
    ui->label->setPixmap(miniature);
    repaint();
}
