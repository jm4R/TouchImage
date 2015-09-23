#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QMatrix>
#include <QColor>
#include <QPen>

/**
 * @brief
 * Klasa służąca do przetrzymywania ustawień rysowania.
 */
class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings& instance();
    ~Settings();

    QMatrix getTransformationMatrix() const;
    QPen getPen() const;
    bool getAntialiasing() const;

public slots:
    void setTransformationMatrix(QMatrix value);
    void setPen(QPen value);
    void setAntialiasing(bool value);

private:
    QMatrix transformationMatrix;
    QPen pen;
    bool antialiasing;

    Settings();
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;
};

#endif // SETTINGS_H
