#include "brushwidget.h"
#include "ui_brushwidget.h"

BrushWidget::BrushWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushWidget)
{
    ui->setupUi(this);
}

BrushWidget::~BrushWidget()
{
    delete ui;
}
