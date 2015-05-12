#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QMatrix>
#include <QColor>

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings& instance();
    ~Settings();

    QColor getColor() const;
    QMatrix getTransformationMatrix() const;
    int getBrushWidth() const;

public slots:
    void setColor(QColor value);
    void setTransformationMatrix(QMatrix value);
    void setBrushWidth(int value);

private:
    QColor color;
    QMatrix transformationMatrix;
    int brushWidth;

    Settings();
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;
};

#endif // SETTINGS_H
