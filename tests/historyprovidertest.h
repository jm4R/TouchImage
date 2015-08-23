#ifndef HISTORYPROVIDERTEST_H
#define HISTORYPROVIDERTEST_H

#include "../model/historyprovider.h"
#include <QTest>

class HistoryProviderTest : public QObject
{
    Q_OBJECT
private:
    HistoryProvider *object;
private slots:
    void initTestCase();
    void testDisableUndoOptionAfterResetImageInProject();
    void cleanup();
};

#endif // HISTORYPROVIDERTEST_H
