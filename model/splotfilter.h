#ifndef SPLOTFILTER_H
#define SPLOTFILTER_H
#include "filter.h"

/**
 * @brief
 * Klasa abstrakcyjna, służąca do nakładania na obraz różnego rodzaju filtrów splotowych.
 * @sa Filter ColorFilter
 */
class SplotFilter : public Filter
{
public:
    SplotFilter();
    ~SplotFilter();
protected:
    void processLine(int lineNumber);
    virtual uint processMatrix(uint m[9]) = 0;
};

#endif // SPLOTFILTER_H
