#ifndef SATURATEFILTER_H
#define SATURATEFILTER_H
#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra zmiany nasycenia barw w obrazie.
 * @sa Filter ColorFilter
 */
class SaturateFilter : public ColorFilter
{
public:
    SaturateFilter();
    ~SaturateFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // SATURATEFILTER_H
