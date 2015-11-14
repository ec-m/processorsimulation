#include "arrowaluram.h"

// @author: Daniel Muszkiet

ArrowAluRam::ArrowAluRam()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAluRam::~ArrowAluRam()
{
}

QRectF ArrowAluRam::boundingRect() const
{
}

QPolygonF ArrowAluRam::polygon() const
{
    QPolygonF p;
    p << QPointF(732,271) << QPointF(732,326) << QPointF(724,326) << QPointF(740,355)
      << QPointF(756,326) << QPointF(748,326) << QPointF(748,271);
    return p;
}

void ArrowAluRam::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowAluRam::activate(bool t)
{
    this->isActive = t;
}

void ArrowAluRam::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAluRam::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
