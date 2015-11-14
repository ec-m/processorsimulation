#ifndef ARROWADDRISIR_H
#define ARROWADDRISIR_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowAddrIsIR : public QGraphicsItem
{
public:
    ArrowAddrIsIR();
    ~ArrowAddrIsIR();
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

#endif // ARROWADDRISIR_H
