#ifndef FILTER_H
#define FILTER_H
class Filter;

#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include "filterprocess.h"

/**
 * @brief
 * Klasa abstrakcyjna, której szczegółowe implementacje odpowiadają za nakładanie filtra.
 * Klasa ta zapewnia działanie wielowątkowe, a jej działanie jest transparentne dla podklas.
 * @sa FilterProcess
 */
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
    void wait() const;

    QString getName() const;

    int getParameter() const;
    void setParameter(int value);

    int getDefaultParameter() const;

signals:
    void startProcesses();
    void ready();
private slots:
    void handleProcessReady();
protected:
    virtual void processLine(int lineNumber)=0;
    QString name;
    QImage *image;
    int parameter;
    int defaultParameter;

private:
    typedef QSharedPointer<FilterProcess> FilterProcessPointer;
    static QList<FilterProcessPointer> filterProcessPool;
    static int threadCount;
    int threadRuns;
    static QMutex processMutex;
    QMutex handleMutex;
};

#endif // FILTER_H
