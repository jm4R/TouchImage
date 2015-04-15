#ifndef HISTORYPROVIDER_H
#define HISTORYPROVIDER_H

#include <QObject>
#include <QList>
#include "filter.h"

class HistoryProvider : public QObject
{
    Q_OBJECT
public:
    explicit HistoryProvider(QObject *parent = 0);
    ~HistoryProvider();
    void resetToImage(QImage *newImage);
signals:
    void currentImageChanged(QImage *currentImage);
    void undoStatusChanged(bool enabled);
    void redoStatusChanged(bool enabled);
public slots:
    void doFilterAndAppend(Filter *filter);
    void undo();
    void redo();
private slots:
    void filterFinished();
private:
    QList<QImage*> list;
    typedef QList<QImage*>::Iterator Iterator;
    Iterator currentIterator;
    Filter *runningFilter;
};

#endif // HISTORYPROVIDER_H
