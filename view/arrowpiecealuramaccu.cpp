#include "arrowpiecealuramaccu.h"

// @author: Daniel Muszkiet

ArrowPieceAluRamAccu::ArrowPieceAluRamAccu()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

void ArrowPieceAluRamAccu::activate(bool t)
{
    this->isActive = t;
}

void ArrowPieceAluRamAccu::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowPieceAluRamAccu::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

QRectF ArrowPieceAluRamAccu::boundingRect() const
{
}

QPolygonF ArrowPieceAluRamAccu::polygon() const
{
    QPolygonF p;
    p << QPointF(732,271) << QPointF(732,305) << QPointF(748,305) << QPointF(748,271);
    return p;
}

void ArrowPieceAluRamAccu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

