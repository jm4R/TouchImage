#ifndef GRAYSCALEFILTER_H
#define GRAYSCALEFILTER_H
#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra konwersji do odcieni szarości.
 * @sa Filter ColorFilter
 */
class GrayscaleFilter : public ColorFilter
{
public:
    GrayscaleFilter(QObject *parent = 0);
    ~GrayscaleFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // GRAYSCALEFILTER_H
