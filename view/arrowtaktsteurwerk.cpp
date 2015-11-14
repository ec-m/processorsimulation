#include "arrowtaktsteurwerk.h"

// @author: Daniel Muszkiet

ArrowTaktSteuerwerk::ArrowTaktSteuerwerk()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowTaktSteuerwerk::~ArrowTaktSteuerwerk()
{
}

QRectF ArrowTaktSteuerwerk::boundingRect() const
{
}

QPolygonF ArrowTaktSteuerwerk::polygon() const
{
    QPolygonF p;
    p << QPointF(37,89) << QPointF(37,148) << QPointF(29, 148) << QPointF(45, 177) << QPointF(61,148)
      << QPointF(53, 148) << QPointF(53,89) << QPointF(37,89);
    return p;
}

void ArrowTaktSteuerwerk::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->isActive){
        QBrush brush(QColor(150, 150, 150,255));

        painter->setPen(Qt::NoPen);
        painter->setBrush(notActiveColor);
        painter->drawPolygon(polygon());
    }else{
        QBrush brush(QColor(255, 174, 201,255));

        painter->setPen(Qt::NoPen);
        painter->setBrush(activeColor);
        painter->drawPolygon(polygon());
    }
}

void ArrowTaktSteuerwerk::activate(bool t)
{
    this->isActive =  t;
}

void ArrowTaktSteuerwerk::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowTaktSteuerwerk::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

