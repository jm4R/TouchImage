#ifndef HISTORYPROVIDER_H
#define HISTORYPROVIDER_H

#include <QObject>
#include <QList>
#include <QElapsedTimer>
#include "filter.h"
#include "brush.h"

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
    void operationFinished(int time);
    void errorOccured(QString message);
public slots:
    void doFilterAndAppend(Filter *filter);
    void doBrushAndAppend(Brush *brush, QPainterPath path);
    void undo();
    void redo();
private slots:
    void filterFinished();
private:
    QList<QImage*> list;
    typedef QList<QImage*>::Iterator Iterator;
    Iterator currentIterator;
    Filter *runningFilter;

    QElapsedTimer timer;
};

#endif // HISTORYPROVIDER_H
