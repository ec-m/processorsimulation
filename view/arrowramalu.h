#ifndef ARROWRAMALU_H
#define ARROWRAMALU_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowRamAlu : public QGraphicsItem
{
public:
    ArrowRamAlu();
    ~ArrowRamAlu();
    void activate(bool t);
    bool isActive;
    void setActiveColor(QColor c);
    void setNotActiveColor(QColor c);

private:    
    QColor activeColor;
    QColor notActiveColor;
    QRectF boundingRect()const;
    QPolygonF polygon()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ARROWRAMALU_H
