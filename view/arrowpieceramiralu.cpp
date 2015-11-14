#include "arrowpieceramiralu.h"

// @author: Daniel Muszkiet

ArrowPieceRamIrAlu::ArrowPieceRamIrAlu()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

void  ArrowPieceRamIrAlu::activate(bool t)
{
    this->isActive = t;
}

void ArrowPieceRamIrAlu::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowPieceRamIrAlu::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

QRectF ArrowPieceRamIrAlu::boundingRect() const
{
}

QPolygonF ArrowPieceRamIrAlu::polygon() const
{
    QPolygonF p;
    p << QPointF(592,405) << QPointF(548,405) << QPointF(548,79)
      << QPointF(531,79) << QPointF(531,421) << QPointF(592,421);
    return p;
}

void ArrowPieceRamIrAlu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

