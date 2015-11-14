#include "arrowalu2.h"

// @author: Daniel Muszkiet

ArrowAlu2::ArrowAlu2()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAlu2::~ArrowAlu2()
{
}

QRectF ArrowAlu2::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowAlu2::polygon() const
{
    QPolygonF p;
    p << QPointF(172,312+2+2+2+2+2+2+2+2+2+9)
      << QPointF(181,312+2+2+2+2+2+2+2+2+2+9)
      << QPointF(181,309+2+2+2+2+2+2+2+2+2+9)
      << QPointF(191,314+2+2+2+2+2+2+2+2+2+9)
      << QPointF(181,319+2+2+2+2+2+2+2+2+2+9)
      << QPointF(181,316+2+2+2+2+2+2+2+2+2+9)
      << QPointF(172,316+2+2+2+2+2+2+2+2+2+9);
    return p;
}

void ArrowAlu2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," ALU 2");

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

void ArrowAlu2::activate(bool t)
{
    this->isActive = t;
}

void ArrowAlu2::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAlu2::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
