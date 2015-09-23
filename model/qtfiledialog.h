#ifndef QTFILEDIALOG_H
#define QTFILEDIALOG_H

#include "filedialogstrategy.h"

/**
 * @brief
 * Klasa służąca do wyświetlania dialogu otwarcia pliku na systemach desktopowych.
 */
class QtFileDialog : public FileDialogStrategy
{
public:
    QtFileDialog(QObject *parent = 0);
    ~QtFileDialog();
    bool provideExistingFileName();
};

#endif // QTFILEDIALOG_H
