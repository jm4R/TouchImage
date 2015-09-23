#ifndef TOAST_H
#define TOAST_H

#include <QObject>
#include <QLabel>
#include <QTimer>

/**
 * @brief
 * Klasa odpowiadająca za zarządzanie widżetem wyświetlania krótkich informacji statusu aplikacji.
 */
class Toast : public QObject
{
    Q_OBJECT
public:
    explicit Toast(QWidget *parent = 0);
    ~Toast();

signals:

public slots:

    void showToast(QString text, int ms = 2000);
    void hideToast();

private:
    QLabel toastLabel;
    QTimer timer;
    QWidget *parentWidget;
};

#endif // TOAST_H
