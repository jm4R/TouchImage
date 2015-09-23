#ifndef SEPIAFILTER_H
#define SEPIAFILTER_H
#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra sepii.
 * @sa Filter ColorFilter
 */
class SepiaFilter : public ColorFilter
{
public:
    SepiaFilter();
    ~SepiaFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // SEPIAFILTER_H
