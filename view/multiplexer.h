#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class Multiplexer : public QGraphicsItem
{
public:
    Multiplexer();
    ~Multiplexer();

private:
    bool state;    
    QRectF boundingRect()const;
    QPolygonF polygon()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MULTIPLEXER_H
