#include "arrowaccualu.h"

// @author: Daniel Muszkiet

ArrowAccuAlu::ArrowAccuAlu()
{
    this->isActive = false;
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAccuAlu::~ArrowAccuAlu()
{
}

QRectF ArrowAccuAlu::boundingRect() const
{
}

QPolygonF ArrowAccuAlu::polygon() const
{
    QPolygonF p;
    p << QPointF(827,58) << QPointF(827,113) << QPointF(819,113) << QPointF(835,142)
      << QPointF(851,113) << QPointF(843,113) << QPointF(843,58);
    return p;
}

void ArrowAccuAlu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowAccuAlu::activate(bool t)
{
    this->isActive = t;
}

void ArrowAccuAlu::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAccuAlu::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
