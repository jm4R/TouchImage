#ifndef FILTERPROCESS_H
#define FILTERPROCESS_H
class FilterProcess;

#include <QObject>
#include <QThread>
#include <QImage>
#include "filter.h"

class FilterProcess : public QObject
{
    Q_OBJECT
public:
    explicit FilterProcess(int threadNumber, int threadCount);
    ~FilterProcess();

    Filter *getFilter() const;
    void setFilter(Filter *value);

signals:
    void ready();
public slots:
    void startThread();
    void run();
    void freeThread();
    void waitForThread();

private:
    int threadNumber;
    int threadCount;
    QThread thread;
    Filter *filter;
};

#endif // FILTERPROCESS_H
