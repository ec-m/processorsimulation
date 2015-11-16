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

#include "arrowtaktsteurwerk.h"

// @author: Daniel Muszkiet

ArrowTaktSteuerwerk::ArrowTaktSteuerwerk()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowTaktSteuerwerk::~ArrowTaktSteuerwerk()
{
}

QRectF ArrowTaktSteuerwerk::boundingRect() const
{
}

QPolygonF ArrowTaktSteuerwerk::polygon() const
{
    QPolygonF p;
    p << QPointF(37,89) << QPointF(37,148) << QPointF(29, 148) << QPointF(45, 177) << QPointF(61,148)
      << QPointF(53, 148) << QPointF(53,89) << QPointF(37,89);
    return p;
}

void ArrowTaktSteuerwerk::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void ArrowTaktSteuerwerk::activate(bool t)
{
    this->isActive =  t;
}

void ArrowTaktSteuerwerk::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowTaktSteuerwerk::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}

