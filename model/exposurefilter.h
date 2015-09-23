#ifndef EXPOSUREFILTER_H
#define EXPOSUREFILTER_H

#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra symulacji zmiany ekspozycji zdjęcia.
 * @sa Filter ColorFilter
 */
class ExposureFilter : public ColorFilter
{
public:
    ExposureFilter();
    ~ExposureFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // EXPOSUREFILTER_H
