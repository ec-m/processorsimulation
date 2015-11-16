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

#include "arrowaluaccu.h"

// @author: Daniel Muszkiet

ArrowAluAccu::ArrowAluAccu()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAluAccu::~ArrowAluAccu()
{
}

QRectF ArrowAluAccu::boundingRect() const
{
}

QPolygonF ArrowAluAccu::polygon() const
{
    QPolygonF p;
    p << QPointF(732,271) << QPointF(732,305) << QPointF(947,305) << QPointF(947,-110)
      << QPointF(827,-110) << QPointF(827,-80) << QPointF(819,-80) << QPointF(835,-50)
      << QPointF(851,-80) << QPointF(843,-80) << QPointF(843,-94) << QPointF(931,-94)
      << QPointF(931,289) << QPointF(748,289) << QPointF(748,271);
    return p;
}

void ArrowAluAccu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowAluAccu::activate(bool t)
{
    this->isActive = t;
}

void ArrowAluAccu::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAluAccu::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
