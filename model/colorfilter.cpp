#include "colorfilter.h"

ColorFilter::ColorFilter(QObject *parent) : Filter(parent)
{

}

ColorFilter::~ColorFilter()
{

}

void ColorFilter::processLine(int lineNumber)
{
    QRgb *line = reinterpret_cast<QRgb*>(image->scanLine(lineNumber));
    int width = image->width();
    for (int i=0; i<width; i++) {
        line[i] = processPixel(line[i]);
    }
}

uint ColorFilter::mergePixel(uint in, uint out)
{
    if (parameter == 1000) {
        return out;
    } else if (parameter == 0) {
        return in;
    }
    return qRgb(
                ( qRed(out) * parameter + qRed(in) * (1000-parameter) ) / 1000,
                ( qGreen(out) * parameter + qGreen(in) * (1000-parameter) ) / 1000,
                ( qBlue(out) * parameter + qBlue(in) * (1000-parameter) ) / 1000
                );
}

