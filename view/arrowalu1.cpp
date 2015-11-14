#include "arrowalu1.h"

// @author: Daniel Muszkiet

ArrowAlu1::ArrowAlu1()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAlu1::~ArrowAlu1()
{
}

QRectF ArrowAlu1::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowAlu1::polygon() const
{
    QPolygonF p;
    p << QPointF(172,326+2+2+2+2+2+2+2+2+2+2+10)
      << QPointF(181,326+2+2+2+2+2+2+2+2+2+2+10)
      << QPointF(181,323+2+2+2+2+2+2+2+2+2+2+10)
      << QPointF(191,328+2+2+2+2+2+2+2+2+2+2+10)
      << QPointF(181,333+2+2+2+2+2+2+2+2+2+2+10)
      << QPointF(181,330+2+2+2+2+2+2+2+2+2+2+10)
      << QPointF(172,330+2+2+2+2+2+2+2+2+2+2+10);
    return p;
}

void ArrowAlu1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font = painter->font() ;

    painter->setPen(Qt::black);
    font.setPixelSize(13);
    painter->setFont(font);

    QRectF rect = boundingRect();
    rect.setX(rect.x()+22);
    rect.setY(rect.y()-4);
    rect.setHeight(15);
    rect.setWidth(100);

    painter->drawText(rect,Qt::AlignLeft," ALU 1");

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

void ArrowAlu1::activate(bool t)
{
    this->isActive = t;
}

void ArrowAlu1::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAlu1::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

