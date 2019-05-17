#ifndef QHOVERABLEWIDGET_HPP
#define QHOVERABLEWIDGET_HPP

#include <QWidget>

class QHoverableWidget : public QWidget
{
    Q_OBJECT
public:
    QHoverableWidget(QWidget *parent = nullptr);

protected:
    bool event(QEvent *event) override;

    virtual void mouseHoverEnter(QHoverEvent *event);
    virtual void mouseHoverLeave(QHoverEvent *event);
    virtual void mouseHoverMove(QHoverEvent *event);
};

#endif // QHOVERABLEWIDGET_HPP
