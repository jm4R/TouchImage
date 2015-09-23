#ifndef COLORFILTER_H
#define COLORFILTER_H

#include <QObject>
#include <QColor>
#include "filter.h"

/**
 * @brief
 * Klasa abstrakcyjna odpowiedzialna za działanie filtrów, działających na podstawie koloru przetwarzanego piksela.
 * @sa Filter SplotFilter
 */
class ColorFilter : public Filter
{
    Q_OBJECT
public:
    explicit ColorFilter(QObject *parent = 0);
    ~ColorFilter();
protected:
    virtual void processLine(int lineNumber);
    virtual uint processPixel(uint pixel) = 0;
    uint mergePixel(uint in, uint out);
signals:

public slots:
};

#endif // COLORFILTER_H
