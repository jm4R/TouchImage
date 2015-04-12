#ifndef FILTER_H
#define FILTER_H
class Filter;

#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include "filterprocess.h"

class Filter : public QObject
{
    Q_OBJECT
    friend class FilterProcess;
public:
    explicit Filter(QObject *parent = 0);
    ~Filter();

    QImage *getImage() const;
    void setImage(QImage *value);

    void process();
    void wait();

    QString getName() const;

signals:
    void startProcesses();
    void ready();
private slots:
    void handleProcessReady();
protected:
    virtual void processLine(int lineNumber)=0;
    QString name;
    QImage *image;

private:
    typedef QSharedPointer<FilterProcess> FilterProcessPointer;
    static QList<FilterProcessPointer> filterProcessPool;
    static int threadCount;
    int threadRuns;
    QMutex processMutex;
    QMutex handleMutex;
};

#endif // FILTER_H
