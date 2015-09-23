#ifndef GAMMAFILTER_H
#define GAMMAFILTER_H

#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra zmiany rozkładu jasności pikseli.
 * @sa Filter ColorFilter
 */
class GammaFilter : public ColorFilter
{
public:
    GammaFilter();
    ~GammaFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // GAMMAFILTER_H
