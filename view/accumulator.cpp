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

#include "accumulator.h"

// @author: Daniel Muszkiet

Accumulator::Accumulator()
{
    this->state = true;
    this->curValue = 0;
}

Accumulator::~Accumulator()
{
}

QRectF Accumulator::boundingRect() const
{
    return QRectF(750,-49, 166, 105);
}

void Accumulator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush blueBrush(QColor(20, 49, 99,255));

    QPen blackPen;
    blackPen.setWidth(1);

    if(state)
        blackPen.setColor(Qt::black);
    else
        blackPen.setColor(Qt::red);

    painter->setPen(blackPen);
    painter->setBrush(blueBrush);
    painter->drawRect(boundingRect());

    QFont font = painter->font() ;

    /* twice the size than the current font size */
    painter->setPen(Qt::white);
    font.setPixelSize(20);
    font.setBold(true);

    /* set the modified font to the painter */
    painter->setFont(font);
    QRectF rect = boundingRect();
    rect.setY(rect.y()+10);
    painter->drawText(rect,Qt::AlignHCenter,"ACCU");
    font.setPixelSize(15);
    font.setBold(false);
    rect.setY(rect.y()+22);
    painter->setFont(font);
    painter->drawText(rect,Qt::AlignHCenter,"Inhalt:");
}

void Accumulator::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

