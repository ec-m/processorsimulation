#ifndef ARROWRAMIR_H
#define ARROWRAMIR_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowRamIr : public QGraphicsItem
{
public:
    ArrowRamIr();
    ~ArrowRamIr();    
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

#endif // ARROWRAMIR_H
