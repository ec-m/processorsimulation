#include "arrrowirsteuerwerk.h"

// @author: Daniel Muszkiet

ArrowIRSteuerwerk::ArrowIRSteuerwerk()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowIRSteuerwerk::~ArrowIRSteuerwerk()
{
}

QRectF ArrowIRSteuerwerk::boundingRect() const
{
}

QPolygonF ArrowIRSteuerwerk::polygon() const
{
    QPolygonF p;
    p << QPointF(162,89) << QPointF(162,109) << QPointF(119,109) << QPointF(119,148)
      << QPointF(111, 148) << QPointF(127, 177) << QPointF(143, 148) << QPointF(135, 148)
      << QPointF(135, 124) << QPointF(178, 124) << QPointF(178, 89);
    return p;
}

void ArrowIRSteuerwerk::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowIRSteuerwerk::activate(bool t)
{
    this->isActive = t;
}

void ArrowIRSteuerwerk::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowIRSteuerwerk::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
