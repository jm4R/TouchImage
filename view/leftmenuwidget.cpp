#include "leftmenuwidget.h"
#include "ui_leftmenuwidget.h"

LeftMenuWidget::LeftMenuWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LeftMenuWidget)
{
    ui->setupUi(this);
    buttonGroup.addButton(ui->brushesButton);
    buttonGroup.addButton(ui->colorsButton);
    buttonGroup.addButton(ui->filtersButton);
    ui->brushesButton->setChecked(true);
}

LeftMenuWidget::~LeftMenuWidget()
{
    delete ui;
}
