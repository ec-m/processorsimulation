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

#include "arrowpcmultiplexer.h"

// @author: Daniel Muszkiet

ArrowPcMultiplexer::ArrowPcMultiplexer()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowPcMultiplexer::~ArrowPcMultiplexer()
{
}

QRectF ArrowPcMultiplexer::boundingRect() const
{
}

QPolygonF ArrowPcMultiplexer::polygon() const
{
    QPolygonF p;
    p << QPointF(428,277)<< QPointF(428,330)<< QPointF(420,330)<< QPointF(436,359)
      << QPointF(452,330)<< QPointF(444,330)<<QPointF(444,277);
    return p;
}

void ArrowPcMultiplexer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowPcMultiplexer::activate(bool t)
{
    this->isActive = t;
}

void ArrowPcMultiplexer::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowPcMultiplexer::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

