#include "brushwidget.h"
#include "ui_brushwidget.h"
#include <QPainter>

BrushWidget::BrushWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushWidget)
{
    ui->setupUi(this);
    connect(ui->antialiasingCheckBox, SIGNAL(toggled(bool)), this, SLOT(updatePreview()));
    connect(ui->cosmeticCheckBox, SIGNAL(toggled(bool)), this, SLOT(updatePreview()));
    connect(ui->opacitySlider, SIGNAL(sliderReleased()), this, SLOT(updatePreview()));
    connect(ui->roundCheckBox, SIGNAL(toggled(bool)), this, SLOT(updatePreview()));
    connect(ui->widthSlider, SIGNAL(sliderReleased()), this, SLOT(updatePreview()));
}

BrushWidget::~BrushWidget()
{
    delete ui;
}

void BrushWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updatePreview();
}

void BrushWidget::updatePreview()
{
    QSize size = ui->previewLabel->size();
    QPixmap previewPixmap(size);

    QLinearGradient gradient(QPointF(0,0), QPoint(size.width(),0));
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    QBrush brush(gradient);

    QPainter painter(&previewPixmap);
    painter.setBrush(brush);
    painter.drawRect(0,0,size.width(),size.height());

    QPainterPath path(QPointF(size.width()*0.2, size.height()*0.1));
    path.lineTo(QPointF(size.width()*0.8, size.height()*0.1));
    path.lineTo(QPointF(size.width()*0.2, size.height()*0.4));
    path.lineTo(QPointF(size.width()*0.5, size.height()*0.5));
    path.lineTo(QPointF(size.width()*0.7, size.height()*0.6));
    path.lineTo(QPointF(size.width()*0.8, size.height()*0.8));

    QPen pen;
    pen.setWidth(ui->widthSlider->value());
    if (ui->roundCheckBox->isChecked()) {
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
    } else {
        pen.setCapStyle(Qt::SquareCap);
        pen.setJoinStyle(Qt::MiterJoin);
    }
    pen.setCosmetic(ui->cosmeticCheckBox->isChecked());
    pen.setColor(QColor(0,255,0,ui->opacitySlider->value()));
    painter.setPen(pen);
    painter.setRenderHint(painter.Antialiasing, ui->antialiasingCheckBox->isChecked());

    painter.drawPath(path);

    ui->previewLabel->setPixmap(previewPixmap);
}
