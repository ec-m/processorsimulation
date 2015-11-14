#include "arrowaccupc.h"

// @author: Daniel Muszkiet

ArrowAccuPc::ArrowAccuPc()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAccuPc::~ArrowAccuPc()
{
}

QRectF ArrowAccuPc::boundingRect() const
{
}

QPolygonF ArrowAccuPc::polygon() const
{
    QPolygonF p;
    p << QPointF(749,-2) << QPointF(484,-2) << QPointF(484,162) << QPointF(481,162)
      << QPointF(486,171)   << QPointF(491,162)  << QPointF(488,162)  << QPointF(488,1)
      << QPointF(749,1);
    return p;
}

void ArrowAccuPc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->isActive){
        QBrush brush(notActiveColor);

        painter->setPen(Qt::NoPen);
        painter->setBrush(brush);
        painter->drawPolygon(polygon());
    }else{
        QBrush brush(activeColor);

        painter->setPen(Qt::NoPen);
        painter->setBrush(brush);
        painter->drawPolygon(polygon());
    }
}

void ArrowAccuPc::activate(bool t)
{
    this->isActive = t;
}

void ArrowAccuPc::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAccuPc::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
