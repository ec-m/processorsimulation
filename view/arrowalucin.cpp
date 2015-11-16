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

#include "arrowalucin.h"

// @author: Daniel Muszkiet

ArrowAluCin::ArrowAluCin()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAluCin::~ArrowAluCin()
{
}

QRectF ArrowAluCin::boundingRect() const
{
    return polygon().boundingRect();
}

QPolygonF ArrowAluCin::polygon() const
{
    QPolygonF p;
    p << QPointF(172,270+2+2+2+2+2+2+6)
      << QPointF(181,270+2+2+2+2+2+2+6)
      << QPointF(181,267+2+2+2+2+2+2+6)
      << QPointF(191,272+2+2+2+2+2+2+6)
      << QPointF(181,277+2+2+2+2+2+2+6)
      << QPointF(181,274+2+2+2+2+2+2+6)
      << QPointF(172,274+2+2+2+2+2+2+6);
    return p;
}

void ArrowAluCin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignLeft," ALUCIN");

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

void ArrowAluCin::activate(bool t)
{
    this->isActive = t;
}

void ArrowAluCin::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAluCin::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
