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

#include "arrowirprogramcounter.h"

// @author: Daniel Muszkiet

ArrowIrProgramcounter::ArrowIrProgramcounter()
{
    this->isActive = false;
    this->activeColor = QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);
}

ArrowIrProgramcounter::~ArrowIrProgramcounter()
{
}

QRectF ArrowIrProgramcounter::boundingRect() const
{
}

QPolygonF ArrowIrProgramcounter::polygon() const
{
    QPolygonF p;
    p << QPointF(279,89) << QPointF(279,124) << QPointF(428,124) << QPointF(428,143)
      << QPointF(420,143) << QPointF(436,173) << QPointF(452,143) << QPointF(444,143)
      << QPointF(444,109)  << QPointF(295,109) << QPointF(295,89) ;
    return p;
}

void ArrowIrProgramcounter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!this->isActive){
        QBrush brush(notActiveColor);

        painter->setPen(Qt::NoPen);
        painter->setBrush(brush);
        painter->drawPolygon(polygon());
    }else{
        QBrush brush(QColor(255, 174, 201,255));

        painter->setPen(Qt::NoPen);
        painter->setBrush(activeColor);
        painter->drawPolygon(polygon());
    }
}

void ArrowIrProgramcounter::activate(bool t)
{
    this->isActive = t;
}

void ArrowIrProgramcounter::setActiveColor(QColor c)
{
    this->activeColor = c;
}

void ArrowIrProgramcounter::setNotActiveColor(QColor c)
{
    this->notActiveColor = c;
}


