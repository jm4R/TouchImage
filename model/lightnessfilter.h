#ifndef LIGHTNESSFILTER_H
#define LIGHTNESSFILTER_H

#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra symulacji zmiany jasności zdjęcia.
 * @sa Filter ColorFilter
 */
class LightnessFilter : public ColorFilter
{
public:
    LightnessFilter();
    ~LightnessFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // LIGHTNESSFILTER_H
