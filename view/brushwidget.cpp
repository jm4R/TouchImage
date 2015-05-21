#include "brushwidget.h"
#include "ui_brushwidget.h"
#include <QPainter>

BrushWidget::BrushWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushWidget)
{
    ui->setupUi(this);
    connect(ui->antialiasingCheckBox, SIGNAL(toggled(bool)), this, SLOT(updatePen()));
    connect(ui->cosmeticCheckBox, SIGNAL(toggled(bool)), this, SLOT(updatePen()));
    connect(ui->opacitySlider, SIGNAL(sliderReleased()), this, SLOT(updatePen()));
    connect(ui->roundCheckBox, SIGNAL(toggled(bool)), this, SLOT(updatePen()));
    connect(ui->widthSlider, SIGNAL(sliderReleased()), this, SLOT(updatePen()));
}

BrushWidget::~BrushWidget()
{
    delete ui;
}

void BrushWidget::setColor(QColor color)
{
    this->color = color;
    updatePen();
}

void BrushWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updatePen();
}

QPen BrushWidget::generatePen()
{
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
    color.setAlpha(ui->opacitySlider->value());
    pen.setColor(color);

    return qMove(pen);
}

void BrushWidget::drawPreview(QPen pen, bool antialiasing)
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

    painter.setPen(pen);
    painter.setRenderHint(painter.Antialiasing, antialiasing);

    painter.drawPath(path);
    ui->previewLabel->setPixmap(previewPixmap);
}

void BrushWidget::updatePen()
{
    QPen pen = generatePen();
    bool antialiasing = ui->antialiasingCheckBox->isChecked();

    drawPreview(pen, antialiasing);

    emit penChanged(pen);
    emit antialiasingChanged(antialiasing);
}
