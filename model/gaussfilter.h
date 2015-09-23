#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H

#include "splotfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra rozmycia Gaussa.
 * @sa Filter SplotFilter
 */
class GaussFilter : public SplotFilter
{
public:
    GaussFilter();
    ~GaussFilter();
protected:
    uint processMatrix(uint m[9]);
};

#endif // GAUSSFILTER_H
