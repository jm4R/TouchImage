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
    float changedFactor = parameter / 100.0f;
    float preservedFactor = (100 - parameter) / 100.0f;
    for (int i=0; i<width; i++) {
        uint newValue = processPixel(line[i]);
        line[i] = qRgb (
                    qRed(newValue) * changedFactor + qRed(line[i]) * preservedFactor,
                    qGreen(newValue) * changedFactor + qGreen(line[i]) * preservedFactor,
                    qBlue(newValue) * changedFactor + qBlue(line[i]) * preservedFactor );
    }
}

