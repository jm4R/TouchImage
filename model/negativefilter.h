#ifndef NEGATVEFILTER_H
#define NEGATVEFILTER_H

#include "colorfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra negatywu.
 * @sa Filter ColorFilter
 */
class NegativeFilter : public ColorFilter
{
public:
    NegativeFilter();
    ~NegativeFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // NEGATVEFILTER_H
