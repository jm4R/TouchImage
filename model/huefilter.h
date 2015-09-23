#ifndef HUEFILTER_H
#define HUEFILTER_H

#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra zmiany odcienia zdjęcia.
 * @sa Filter ColorFilter
 */
class HueFilter : public ColorFilter
{
public:
    HueFilter();
    ~HueFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // HUEFILTER_H
