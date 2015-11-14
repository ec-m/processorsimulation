#include "arrowramalu.h"

// @author: Daniel Muszkiet

ArrowRamAlu::ArrowRamAlu()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowRamAlu::~ArrowRamAlu()
{
}

QRectF ArrowRamAlu::boundingRect() const
{
}

QPolygonF ArrowRamAlu::polygon() const
{
    QPolygonF p;
    p << QPointF(592,405) << QPointF(548,405) << QPointF(548,95) << QPointF(635,95)
      << QPointF(635,113) << QPointF(627,113) << QPointF(643,142) << QPointF(659,113)
      << QPointF(651,113) << QPointF(651,79) << QPointF(531,79) << QPointF(531,421)
      << QPointF(592,421)   ;
    return p;
}

void ArrowRamAlu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowRamAlu::activate(bool t)
{
    this->isActive = t;
}

void ArrowRamAlu::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowRamAlu::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
