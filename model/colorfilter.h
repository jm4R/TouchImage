#ifndef COLORFILTER_H
#define COLORFILTER_H

#include <QObject>
#include "filter.h"

class ColorFilter : public Filter
{
    Q_OBJECT
public:
    explicit ColorFilter(QObject *parent = 0);
    ~ColorFilter();
protected:
    virtual void processLine(int lineNumber);
    virtual uint processPixel(uint pixel) = 0;
signals:

public slots:
};

#endif // COLORFILTER_H
