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

#include "arrowincpc.h"

// @author: Daniel Muszkiet

ArrowIncPc::ArrowIncPc()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

QRectF ArrowIncPc::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowIncPc::polygon() const
{
    QPolygonF p;
    p << QPointF(172,200+2+1)
      << QPointF(181,200+2+1)
      << QPointF(181,197+2+1)
      << QPointF(191,202+2+1)
      << QPointF(181,207+2+1)
      << QPointF(181,204+2+1)
      << QPointF(172,204+2+1);
    return p;
}

void ArrowIncPc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," Inc[PC]");

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

void ArrowIncPc::activate(bool t)
{
    this->isActive = t;    
}

void ArrowIncPc::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowIncPc::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
