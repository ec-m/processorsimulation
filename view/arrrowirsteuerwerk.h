#ifndef ARRROWIRSTEUERWERK_H
#define ARRROWIRSTEUERWERK_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowIRSteuerwerk: public QGraphicsItem
{
public:
    ArrowIRSteuerwerk();
    ~ArrowIRSteuerwerk();
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

#endif // ARRROWIRSTEUERWERK_H
