#ifndef DRAWERSWIDGET_H
#define DRAWERSWIDGET_H

#include <QWidget>
#include <QGesture>
#include <QScroller>
#include <QProgressBar>

/**
 * @brief
 * Klasa odpowiadająca za wyświetlanie i zarządzanie widżetem szufladek bocznych.
 */
class DrawersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawersWidget(QWidget *parent = 0);
    ~DrawersWidget();


    QWidget *getLeftWidget() const;
    void setLeftWidget(QWidget *value, int widgetWidth);
    void setRightWidget(QWidget *value, int widgetWidth);

    int getHandlerWidth() const;
    void setHandlerWidth(int value);

    QWidget *getBottomWidget() const;
    void setBottomWidget(QWidget *value);

    QWidget *getTopWidgetToLeft() const;
    void setTopWidgetToLeft(QWidget *value);

    QWidget *getTopWidgetToRight() const;
    void setTopWidgetToRight(QWidget *value);

protected:
    virtual bool event(QEvent *event);
    virtual void resizeEvent(QResizeEvent * event);

signals:

private:
    void prepareLeftScroller(QScrollPrepareEvent *event);
    void handleLeftDragging(QScrollEvent *event);
    void prepareRightScroller(QScrollPrepareEvent *event);
    void handleRightDragging(QScrollEvent *event);

    QScroller *scroller;
    int handlerWidth;

    QWidget *leftWidget;
    int leftWidgetWidth;
    QWidget *rightWidget;
    int rightWidgetWidth;

    QWidget *bottomWidget;
    QWidget *topWidgetToLeft;
    QWidget *topWidgetToRight;

    enum State {
        STATE_LAZY,
        STATE_LEFT_DRAGGING,
        STATE_LEFT_BACKWARDS,
        STATE_RIGHT_DRAGGING,
        STATE_RIGHT_BACKWARDS
    } state;

    enum LayoutState {
        LS_BOTH_HIDDEN,
        LS_LEFT_VISIBLE,
        LS_RIGHT_VISIBLE
    } layoutState;

    void setState(State newState);
    void setLayoutState(LayoutState newLayoutState);

    void updateUI();

public slots:
    void hideDrawers();
};

#endif // DRAWERSWIDGET_H
