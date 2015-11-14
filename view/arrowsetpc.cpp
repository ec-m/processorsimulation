#include "arrowsetpc.h"

// @author: Daniel Muszkiet

ArrowSetPc::ArrowSetPc()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowSetPc::~ArrowSetPc()
{
}

QRectF ArrowSetPc::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowSetPc::polygon() const
{
    QPolygonF p;
    p << QPointF(172,214+2+2+2)
      << QPointF(181,214+2+2+2)
      << QPointF(181,211+2+2+2)
      << QPointF(191,216+2+2+2)
      << QPointF(181,221+2+2+2)
      << QPointF(181,218+2+2+2)
      << QPointF(172,218+2+2+2);
    return p;
}

void ArrowSetPc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," Set[PC]");

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

void ArrowSetPc::activate(bool t)
{
    this->isActive = t;
}

void ArrowSetPc::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowSetPc::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

