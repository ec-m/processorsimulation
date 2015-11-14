#ifndef CLOCK_H
#define CLOCK_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class Clock : public QGraphicsItem
{
public:
    Clock();
    ~Clock();

private:
    bool state;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CLOCK_H
