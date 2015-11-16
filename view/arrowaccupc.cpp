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

#include "arrowaccupc.h"

// @author: Daniel Muszkiet

ArrowAccuPc::ArrowAccuPc()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowAccuPc::~ArrowAccuPc()
{
}

QRectF ArrowAccuPc::boundingRect() const
{
}

QPolygonF ArrowAccuPc::polygon() const
{
    QPolygonF p;
    p << QPointF(749,-2) << QPointF(484,-2) << QPointF(484,162) << QPointF(481,162)
      << QPointF(486,171)   << QPointF(491,162)  << QPointF(488,162)  << QPointF(488,1)
      << QPointF(749,1);
    return p;
}

void ArrowAccuPc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->isActive){
        QBrush brush(notActiveColor);

        painter->setPen(Qt::NoPen);
        painter->setBrush(brush);
        painter->drawPolygon(polygon());
    }else{
        QBrush brush(activeColor);

        painter->setPen(Qt::NoPen);
        painter->setBrush(brush);
        painter->drawPolygon(polygon());
    }
}

void ArrowAccuPc::activate(bool t)
{
    this->isActive = t;
}

void ArrowAccuPc::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowAccuPc::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}
