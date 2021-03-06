#ifndef ANDROIDFILEDIALOG_H
#define ANDROIDFILEDIALOG_H

#include <QObject>
#include "filedialogstrategy.h"
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QAndroidActivityResultReceiver>

/**
 * @brief
 * Klasa służąca do wywoływania natywnego dialogu wyboru pliku w systemie Android.
 * @sa FileDialogStrategy
 */
class AndroidFileDialog : public FileDialogStrategy
{
    Q_OBJECT

public:
    explicit AndroidFileDialog(QObject *parent = 0);
    virtual ~AndroidFileDialog();
    bool provideExistingFileName();

private:
    class ResultReceiver : public QAndroidActivityResultReceiver {
        AndroidFileDialog *_dialog;
    public:
        ResultReceiver(AndroidFileDialog *dialog);
        virtual ~ResultReceiver();
        void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data);
        QString uriToPath(QAndroidJniObject uri);
    };

    static const int EXISTING_FILE_NAME_REQUEST = 1;
    ResultReceiver *receiver;
    void emitExistingFileNameReady(QString result);

};

#endif // ANDROIDFILEDIALOG_H
