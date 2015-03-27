#include "drawerswidget.h"
#include <QDebug>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QtMath>


DrawersWidget::DrawersWidget(QWidget *parent) :
    QWidget(parent),
    handlerWidth(40),
    leftWidget(0),
    rightWidget(0),
    bottomWidget(0),
    topWidgetToLeft(0),
    topWidgetToRight(0),
    state(STATE_LAZY),
    layoutState(LS_BOTH_HIDDEN)
{
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);
    scroller = QScroller::scroller(this);
    QScrollerProperties scrollerProperties;
    scrollerProperties.setScrollMetric(QScrollerProperties::SnapPositionRatio, 0.1);
}

DrawersWidget::~DrawersWidget()
{

}

//----------------------EVENTS
bool DrawersWidget::event(QEvent *event)
{
    if (event->type() == QEvent::ScrollPrepare) {
        QScrollPrepareEvent *se = static_cast<QScrollPrepareEvent *>(event);
        switch (state) {
        case STATE_LEFT_BACKWARDS:
            prepareLeftScroller(se);
            return true;
        case STATE_RIGHT_BACKWARDS:
            prepareRightScroller(se);
            return true;
        default:
            if (layoutState == LS_BOTH_HIDDEN && se->startPos().x() < handlerWidth) {
                setState(STATE_LEFT_DRAGGING);
                prepareLeftScroller(se);
                return true;
            } else if (layoutState == LS_BOTH_HIDDEN && se->startPos().x() > width() - handlerWidth) {
                setState(STATE_RIGHT_DRAGGING);
                prepareRightScroller(se);
                return true;
            }
        }

    } else if (event->type() == QEvent::Scroll) {
        QScrollEvent *se = static_cast<QScrollEvent *>(event);
        switch (state) {
        case STATE_LEFT_DRAGGING:
        case STATE_LEFT_BACKWARDS:
            handleLeftDragging(se);
            return true;
        case STATE_RIGHT_DRAGGING:
        case STATE_RIGHT_BACKWARDS:
            handleRightDragging(se);
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        hideDrawers();
    }
    return QWidget::event(event);
}

void DrawersWidget::prepareLeftScroller(QScrollPrepareEvent *event)
{
    QList<qreal> snapPositions;
    snapPositions << leftWidgetWidth;
    snapPositions << 0;
    scroller->setSnapPositionsX(snapPositions);
    event->setViewportSize(QSize(20,0));
    event->setContentPosRange(QRect(0, 0, leftWidgetWidth, 0));
    int start = (layoutState != LS_LEFT_VISIBLE) ? leftWidgetWidth : 0;
    event->setContentPos(QPointF(start,0));
    event->accept();
}

void DrawersWidget::handleLeftDragging(QScrollEvent *event)
{
    int value = -event->contentPos().x() - event->overshootDistance().x();
    leftWidget->setGeometry(value, 0, leftWidgetWidth, height());
    if (event->scrollState() == QScrollEvent::ScrollFinished) {
        setLayoutState( (value==-leftWidgetWidth) ? LS_BOTH_HIDDEN : LS_LEFT_VISIBLE );
        setState(STATE_LAZY);
    }
    event->accept();
}

void DrawersWidget::prepareRightScroller(QScrollPrepareEvent *event)
{
    QList<qreal> snapPositions;
    snapPositions << 0;
    snapPositions << rightWidgetWidth;
    scroller->setSnapPositionsX(snapPositions);
    event->setViewportSize(QSize(20,0));
    event->setContentPosRange(QRect(0, 0, rightWidgetWidth, 0));
    int start = (layoutState != LS_RIGHT_VISIBLE) ? 0 : rightWidgetWidth;
    event->setContentPos(QPointF(start,0));
    event->accept();
}

void DrawersWidget::handleRightDragging(QScrollEvent *event)
{
    int value = event->contentPos().x() + event->overshootDistance().x();
    rightWidget->setGeometry(width()-value, 0, rightWidgetWidth, height());
    if (event->scrollState() == QScrollEvent::ScrollFinished) {
        setLayoutState( (value==0) ? LS_BOTH_HIDDEN : LS_RIGHT_VISIBLE );
        setState(STATE_LAZY);
    }
    event->accept();
}

void DrawersWidget::setState(DrawersWidget::State newState)
{
    state = newState;
}

void DrawersWidget::setLayoutState(DrawersWidget::LayoutState newLayoutState)
{
    layoutState = newLayoutState;
    updateUI();
}

void DrawersWidget::hideDrawers()
{
    int targetPosition;
    switch (layoutState) {
    case LS_BOTH_HIDDEN:
        return;
    case LS_LEFT_VISIBLE:
        setState(STATE_LEFT_BACKWARDS);
        targetPosition = leftWidgetWidth;
        break;
    case LS_RIGHT_VISIBLE:
        setState(STATE_RIGHT_BACKWARDS);
        targetPosition = 0;
        break;
    }
    scroller->scrollTo(QPointF(targetPosition,0));
}
//----------------------EVENTS

void DrawersWidget::resizeEvent(QResizeEvent *event)
{
    //MOCK{
    setLeftWidget(0, 400);
    setRightWidget(0, 400);
    setTopWidgetToLeft(0);
    setTopWidgetToRight(0);
    //}MOCK
    updateUI();
}

int DrawersWidget::getHandlerWidth() const
{
    return handlerWidth;
}

void DrawersWidget::setHandlerWidth(int value)
{
    handlerWidth = value;
}

QWidget *DrawersWidget::getLeftWidget() const
{
    return leftWidget;
}

void DrawersWidget::setLeftWidget(QWidget *value, int widgetWidth)
{
    //MOCK{
    if (leftWidget != 0) return;
    value = new QWidget();
    value->setPalette(QPalette(QColor(0,0,0, 196)));
    value->setAutoFillBackground(true);
    value->setFixedWidth(400);
    //}MOCK
    leftWidget = value;
    leftWidgetWidth = widgetWidth;
    updateUI();
}

void DrawersWidget::setRightWidget(QWidget *value, int widgetWidth)
{
    //MOCK{
    if (rightWidget != 0) return;
    value = new QWidget();
    value->setPalette(QPalette(QColor(0,0,0, 196)));
    value->setAutoFillBackground(true);
    value->setFixedWidth(400);
    //}MOCK
    rightWidget = value;
    rightWidgetWidth = widgetWidth;
    updateUI();
}

QWidget *DrawersWidget::getTopWidgetToRight() const
{
    return topWidgetToRight;
}

void DrawersWidget::setTopWidgetToRight(QWidget *value)
{
    //MOCK{
    //if (topWidgetToRight != 0) return;
    //value = new QWidget();
    //value->setPalette(QPalette(QColor(0,0,0, 196)));
    //value->setAutoFillBackground(true);
    //}MOCK
    topWidgetToRight = value;
    updateUI();
}

QWidget *DrawersWidget::getTopWidgetToLeft() const
{
    return topWidgetToLeft;
}

void DrawersWidget::setTopWidgetToLeft(QWidget *value)
{
    //MOCK{
    if (topWidgetToLeft != 0) return;
    value = new QWidget();
    value->setPalette(QPalette(QColor(0,0,50, 196)));
    value->setAutoFillBackground(true);
    //}MOCK
    topWidgetToLeft = value;
    updateUI();
}

QWidget *DrawersWidget::getBottomWidget() const
{
    return bottomWidget;
}

void DrawersWidget::setBottomWidget(QWidget *value)
{
    bottomWidget = value;
    updateUI();
}

void DrawersWidget::updateUI()
{
    if (layoutState == LS_LEFT_VISIBLE && !leftWidget) {
        layoutState = LS_BOTH_HIDDEN;
    } else if (layoutState == LS_RIGHT_VISIBLE && !rightWidget) {
        layoutState = LS_BOTH_HIDDEN;
    }

    QList<QWidget*> widgetsToHide;
    QWidget* topWidget;
    int topWidgetX, topWidgetWidth;

    switch (layoutState) {
    case LS_BOTH_HIDDEN:
        widgetsToHide << topWidgetToLeft << topWidgetToRight;
        topWidget = 0;
        break;
    case LS_LEFT_VISIBLE:
        widgetsToHide << topWidgetToRight;
        topWidget = topWidgetToLeft;
        topWidgetX = leftWidgetWidth;
        topWidgetWidth = width() - leftWidgetWidth;
        break;
    case LS_RIGHT_VISIBLE:
        widgetsToHide << topWidgetToLeft;
        topWidget = topWidgetToRight;
        topWidgetX = 0;
        topWidgetWidth = width() - rightWidgetWidth;
    }

    foreach (QWidget *widget, widgetsToHide) {
        if (widget) {
            widget->setParent(0);
            widget->hide();
        }
    }

    if (bottomWidget) {
        bottomWidget->setParent(this);
        bottomWidget->setGeometry(handlerWidth, 0, width() - handlerWidth*2, height());
        bottomWidget->show();
        bottomWidget->lower();
    }

    if (topWidget) {
        topWidget->setParent(this);
        topWidget->setGeometry(topWidgetX, 0, topWidgetWidth, height());
        topWidget->show();
        topWidget->raise();
    }

    if (leftWidget) {
        leftWidget->setParent(this);
        leftWidget->show();
        leftWidget->raise();
        if (layoutState == LS_LEFT_VISIBLE) {
            leftWidget->setGeometry(0, 0, leftWidgetWidth, height());
        } else {
            leftWidget->setGeometry(-leftWidgetWidth, 0, leftWidgetWidth, height());
        }
    }

    if (rightWidget) {
        rightWidget->setParent(this);
        rightWidget->show();
        rightWidget->raise();
        if (layoutState == LS_RIGHT_VISIBLE) {
            rightWidget->setGeometry(width() - rightWidgetWidth, 0, rightWidgetWidth, height());
        } else {
            rightWidget->setGeometry(width(), 0, rightWidgetWidth, height());
        }
    }

}
