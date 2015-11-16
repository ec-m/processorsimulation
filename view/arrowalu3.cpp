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

#include "arrowalu3.h"

// @author: Daniel Muszkiet

ArrowAlu3::ArrowAlu3()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAlu3::~ArrowAlu3()
{
}

QRectF ArrowAlu3::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowAlu3::polygon() const
{
    QPolygonF p;
    p << QPointF(172,298+2+2+2+2+2+2+2+2+8)
      << QPointF(181,298+2+2+2+2+2+2+2+2+8)
      << QPointF(181,295+2+2+2+2+2+2+2+2+8)
      << QPointF(191,300+2+2+2+2+2+2+2+2+8)
      << QPointF(181,305+2+2+2+2+2+2+2+2+8)
      << QPointF(181,302+2+2+2+2+2+2+2+2+8)
      << QPointF(172,302+2+2+2+2+2+2+2+2+8);
    return p;
}

void ArrowAlu3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," ALU 3");

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

void ArrowAlu3::activate(bool t)
{
    this->isActive = t;
}

void ArrowAlu3::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAlu3::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
