#ifndef BRUSH_H
#define BRUSH_H

#include <QObject>
#include <QPainter>

class Brush : public QObject
{
    Q_OBJECT

public:
    explicit Brush(QObject *parent = 0);
    ~Brush();

    QImage *getImage() const;
    QString getName() const;
    static void setTransformationMatrix(QMatrix matrix);

public slots:
    void process(QPainterPath path);
    void setImage(QImage *value);

protected:
    QString name;
    QImage *image;
    static QMatrix transformationMatrix;
};

#endif // BRUSH_H
