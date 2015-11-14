#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class Accumulator : public QGraphicsItem
{
public:
    Accumulator();
    ~Accumulator();
    ushort curValue;

private:
    bool state;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ACCUMULATOR_H
