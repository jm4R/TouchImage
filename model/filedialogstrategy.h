#ifndef FILEDIALOGSTRATEGY_H
#define FILEDIALOGSTRATEGY_H

#include <QObject>

class FileDialogStrategy : public QObject
{
    Q_OBJECT
public:
    explicit FileDialogStrategy(QObject *parent = 0);
    virtual ~FileDialogStrategy();
    virtual bool provideExistingFileName() = 0;

signals:
    void existingFileNameReady(QString result);
};

#endif // FILEDIALOGSTRATEGY_H
