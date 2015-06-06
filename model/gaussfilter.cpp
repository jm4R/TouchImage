#include "gaussfilter.h"

GaussFilter::GaussFilter()
{
    name = tr("Rozmycie");
}

GaussFilter::~GaussFilter()
{

}

uint GaussFilter::processMatrix(uint m[])
{
    int newR = 1 * (qRed(m[0]) + qRed(m[2]) + qRed(m[6]) + qRed(m[8])) +
               2 * (qRed(m[1]) + qRed(m[3]) + qRed(m[5]) + qRed(m[7])) +
               4 * qRed(m[4]);
    newR >>= 4;
    int newG = 1 * (qGreen(m[0]) + qGreen(m[2]) + qGreen(m[6]) + qGreen(m[8])) +
               2 * (qGreen(m[1]) + qGreen(m[3]) + qGreen(m[5]) + qGreen(m[7])) +
               4 * qGreen(m[4]);
    newG >>= 4;
    int newB = 1 * (qBlue(m[0]) + qBlue(m[2]) + qBlue(m[6]) + qBlue(m[8])) +
               2 * (qBlue(m[1]) + qBlue(m[3]) + qBlue(m[5]) + qBlue(m[7])) +
               4 * qBlue(m[4]);
    newB >>= 4;

    return qRgb(newR, newG, newB);
}

