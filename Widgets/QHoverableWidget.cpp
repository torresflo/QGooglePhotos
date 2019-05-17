#include <QEvent>
#include <QHoverEvent>

#include <Widgets/QHoverableWidget.hpp>

QHoverableWidget::QHoverableWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_Hover, true);
}

bool QHoverableWidget::event(QEvent* event)
{
    switch(event->type())
    {
        case QEvent::HoverEnter:
            mouseHoverEnter(static_cast<QHoverEvent*>(event));
            break;
        case QEvent::HoverMove:
            mouseHoverMove(static_cast<QHoverEvent*>(event));
            break;
        case QEvent::HoverLeave:
            mouseHoverLeave(static_cast<QHoverEvent*>(event));
            break;
        default:
            QWidget::event(event);
            break;
    }

    return event->isAccepted();
}

void QHoverableWidget::mouseHoverEnter(QHoverEvent* event)
{
    QWidget::event(event);
}

void QHoverableWidget::mouseHoverMove(QHoverEvent* event)
{
    QWidget::event(event);
}

void QHoverableWidget::mouseHoverLeave(QHoverEvent* event)
{
    QWidget::event(event);
}
