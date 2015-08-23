#include "historyprovidertest.h"
#include <QSignalSpy>

void HistoryProviderTest::initTestCase()
{
    object = new HistoryProvider();
}

void HistoryProviderTest::testDisableUndoOptionAfterResetImageInProject()
{
    QSignalSpy signalSpy(object, SIGNAL(undoStatusChanged(bool)));
    QImage *image = new QImage();
    object->resetToImage(image);
    QCOMPARE( signalSpy.count(), 1 ); //sygnał został wyemitowany dokładnie raz?

    QList<QVariant> arguments = signalSpy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == false);  //argumentem było "false"?
}

void HistoryProviderTest::cleanup()
{
    delete object;
}

