#include "arrowwriteram.h"

// @author: Daniel Muszkiet

ArrowWriteRam::ArrowWriteRam()
{
    this->isActive = false;

    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowWriteRam::~ArrowWriteRam()
{
}

QRectF ArrowWriteRam::boundingRect() const
{
    QRectF rect =  polygon().boundingRect();
    return rect;
}

QPolygonF ArrowWriteRam::polygon() const
{
    QPolygonF p;
    p << QPointF(172,186)
      << QPointF(181,186)
      << QPointF(181,183)
      << QPointF(191,188)
      << QPointF(181,193)
      << QPointF(181,190)
      << QPointF(172,190);
    return p;
}

void ArrowWriteRam::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," Write[Ram]");

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

void ArrowWriteRam::activate(bool t)
{    
    this->isActive = t;
}

void ArrowWriteRam::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowWriteRam::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
