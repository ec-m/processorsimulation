#include "arrowmultiplexerram.h"

// @author: Daniel Muszkiet

ArrowMultiplexerRam::ArrowMultiplexerRam()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowMultiplexerRam::~ArrowMultiplexerRam()
{
}

QRectF ArrowMultiplexerRam::boundingRect() const
{
}

QPolygonF ArrowMultiplexerRam::polygon() const
{
    QPolygonF p;
    p << QPointF(375,448) << QPointF(375,495) << QPointF(565,495) << QPointF(565,503)
      << QPointF(594,487) << QPointF(565,471) << QPointF(565,479) << QPointF(391,479)
      << QPointF(391,448);
    return p;
}

void ArrowMultiplexerRam::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowMultiplexerRam::activate(bool t)
{
    this->isActive = t;
}

void ArrowMultiplexerRam::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowMultiplexerRam::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

