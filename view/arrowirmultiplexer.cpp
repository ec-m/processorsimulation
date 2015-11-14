#include "arrowirmultiplexer.h"

// @author: Daniel Muszkiet

ArrowIrMultiplexer::ArrowIrMultiplexer()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowIrMultiplexer::~ArrowIrMultiplexer()
{
}

QRectF ArrowIrMultiplexer::boundingRect() const
{
}

QPolygonF ArrowIrMultiplexer::polygon() const
{
    QPolygonF p;
    p << QPointF(279,89) << QPointF(279,124) <<  QPointF(324,124) << QPointF(324,329)
      << QPointF(316,329) << QPointF(332,359) << QPointF(348,329) << QPointF(340,329)
      << QPointF(340,109) << QPointF(295,109) << QPointF(295,89);
    return p;
}

void ArrowIrMultiplexer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowIrMultiplexer::activate(bool t)
{
    this->isActive = t;
}

void ArrowIrMultiplexer::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowIrMultiplexer::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
