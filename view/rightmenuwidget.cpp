#include "rightmenuwidget.h"
#include "ui_rightmenuwidget.h"

RightMenuWidget::RightMenuWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RightMenuWidget)
{
    ui->setupUi(this);
}

RightMenuWidget::~RightMenuWidget()
{
    delete ui;
}
