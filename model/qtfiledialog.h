#ifndef QTFILEDIALOG_H
#define QTFILEDIALOG_H

#include "filedialogstrategy.h"

class QtFileDialog : public FileDialogStrategy
{
public:
    QtFileDialog(QObject *parent = 0);
    ~QtFileDialog();
    bool provideExistingFileName();
};

#endif // QTFILEDIALOG_H
