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

#include "arithmeticlogicalunit.h"

// @author: Daniel Muszkiet

ArithmeticLogicalUnit::ArithmeticLogicalUnit()
{
    this->state = true;
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

ArithmeticLogicalUnit::~ArithmeticLogicalUnit()
{
}

QRectF ArithmeticLogicalUnit::boundingRect() const
{
    return this->polygon().boundingRect();
}

QPolygonF ArithmeticLogicalUnit::polygon() const
{
    QPolygonF p;
    p << QPointF(560,144) << QPointF(725,144) << QPointF(738,157)
      << QPointF(751,144) << QPointF(916,144) << QPointF(880,269) << QPointF(596,269);
    return p;
}

void ArithmeticLogicalUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawPolygon(polygon());

    QFont font = painter->font() ;

    /* twice the size than the current font size */
    painter->setPen(Qt::white);
    font.setPixelSize(20);
    font.setBold(true);

    /* set the modified font to the painter */
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignCenter,"ALU");
}

void ArithmeticLogicalUnit::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

