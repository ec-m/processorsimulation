#ifndef ARITHMETICLOGICALUNIT_H
#define ARITHMETICLOGICALUNIT_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArithmeticLogicalUnit : public QGraphicsItem
{
public:
    ArithmeticLogicalUnit();
    ~ArithmeticLogicalUnit();

private:
    bool state;    
    QRectF boundingRect()const;
    QPolygonF polygon()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ARITHMETICLOGICALUNIT_H
