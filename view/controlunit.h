#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ControlUnit : public QGraphicsItem
{
public:
    ControlUnit();
    ~ControlUnit();

private:
    bool state;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CONTROLUNIT_H
