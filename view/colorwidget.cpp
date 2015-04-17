#include "colorwidget.h"
#include "ui_colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ColorWidget),
    color(255,255,255)
{
    ui->setupUi(this);
    ui->colorPicker->setCol(0, 0);
    ui->luminancePicker->setCol(0,0,255);
    ui->luminancePicker->setMinimumWidth(ScreenAdapter().cmToPx(1.0f));
    connect(ui->colorPicker, SIGNAL(colorChanged(int,int)), ui->luminancePicker, SLOT(setCol(int,int)));
    connect(ui->luminancePicker, SIGNAL(newHsv(int,int,int)), this, SLOT(setHsv(int,int,int)));
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::setHsv(int h, int s, int v)
{
    color = QColor::fromHsv(h,s,v);
    refreshLabels();
    emit colorChanged(color);
}

void ColorWidget::refreshLabels()
{
    ui->colorFrame->setPalette(QPalette(color));

    ui->rLabel->setText(QString::number(color.red()));
    ui->gLabel->setText(QString::number(color.green()));
    ui->bLabel->setText(QString::number(color.blue()));

    ui->hLabel->setText(QString::number(color.hsvHue()));
    ui->sLabel->setText(QString::number(color.hsvSaturation()));
    ui->vLabel->setText(QString::number(color.value()));

    ui->cLabel->setText(QString::number(color.cyan()));
    ui->mLabel->setText(QString::number(color.magenta()));
    ui->yLabel->setText(QString::number(color.yellow()));
    ui->kLabel->setText(QString::number(color.black()));
}
