#include "arrowalu0.h"

// @author: Daniel Muszkiet

ArrowAlu0::ArrowAlu0()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAlu0::~ArrowAlu0()
{
}

QRectF ArrowAlu0::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowAlu0::polygon() const
{
    QPolygonF p;
    p << QPointF(172,340+2+2+2+2+2+2+2+2+2+2+2+11)
      << QPointF(181,340+2+2+2+2+2+2+2+2+2+2+2+11)
      << QPointF(181,337+2+2+2+2+2+2+2+2+2+2+2+11)
      << QPointF(191,342+2+2+2+2+2+2+2+2+2+2+2+11)
      << QPointF(181,347+2+2+2+2+2+2+2+2+2+2+2+11)
      << QPointF(181,344+2+2+2+2+2+2+2+2+2+2+2+11)
      << QPointF(172,344+2+2+2+2+2+2+2+2+2+2+2+11);
    return p;
}

void ArrowAlu0::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," ALU 0");

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

void ArrowAlu0::activate(bool t)
{
    this->isActive = t;
}

void ArrowAlu0::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAlu0::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}


