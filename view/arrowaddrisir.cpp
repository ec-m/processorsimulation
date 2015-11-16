/*
 * This file is part of Processorsimulation.
 *
 * The Processorsimulation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, Version 3.
 *
 * The Processorsimulation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "arrowaddrisir.h"

// @author: Daniel Muszkiet

ArrowAddrIsIR::ArrowAddrIsIR()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAddrIsIR::~ArrowAddrIsIR()
{
}

QRectF ArrowAddrIsIR::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowAddrIsIR::polygon() const
{
    QPolygonF p;
    p << QPointF(172,228+2+2+2+3)
      << QPointF(181,228+2+2+2+3)
      << QPointF(181,225+2+2+2+3)
      << QPointF(191,230+2+2+2+3)
      << QPointF(181,235+2+2+2+3)
      << QPointF(181,232+2+2+2+3)
      << QPointF(172,232+2+2+2+3);
    return p;
}

void ArrowAddrIsIR::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," ADDR=IR");

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

void ArrowAddrIsIR::activate(bool t)
{
    this->isActive = t;
}

void ArrowAddrIsIR::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAddrIsIR::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}


