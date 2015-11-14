#ifndef ARROWIRMULTIPLEXER_H
#define ARROWIRMULTIPLEXER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowIrMultiplexer : public QGraphicsItem
{
public:
    ArrowIrMultiplexer();
    ~ArrowIrMultiplexer();
    void activate(bool t);
    void setActiveColor(QColor c);
    void setNotActiveColor(QColor c);

private:
    bool isActive;
    QColor activeColor;
    QColor notActiveColor;
    QRectF boundingRect()const;
    QPolygonF polygon()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ARROWIRMULTIPLEXER_H
