#ifndef ARROWALU2_H
#define ARROWALU2_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowAlu2 : public QGraphicsItem
{
public:
    ArrowAlu2();
    ~ArrowAlu2();
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

#endif // ARROWALU2_H
