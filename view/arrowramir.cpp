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

#include "arrowramir.h"

// @author: Daniel Muszkiet

ArrowRamIr::ArrowRamIr()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowRamIr::~ArrowRamIr()
{
}

QRectF ArrowRamIr::boundingRect() const
{
}

QPolygonF ArrowRamIr::polygon() const
{
    QPolygonF p;
    p << QPointF(592,405) << QPointF(548,405) << QPointF(548,-103) << QPointF(237,-103)
      << QPointF(237,-70) << QPointF(229,-70) << QPointF(245,-41) << QPointF(261,-70)
      << QPointF(253,-70) << QPointF(253,-87) << QPointF(531,-87) << QPointF(531,421)
      << QPointF(592,421);
    return p;
}

void ArrowRamIr::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowRamIr::activate(bool t)
{
    this->isActive = t;
}

void ArrowRamIr::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowRamIr::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
