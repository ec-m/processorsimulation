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

#include "multiplexer.h"

// @author: Daniel Muszkiet

Multiplexer::Multiplexer()
{
    this->state=true;
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

Multiplexer::~Multiplexer()
{
}

QRectF Multiplexer::boundingRect()const
{
    return polygon().boundingRect();
}

QPolygonF Multiplexer::polygon()const
{
    QPolygonF p;
    p << QPointF(287,360) << QPointF(365,360)<< QPointF(378,373) << QPointF(391,360)
      << QPointF(469,360) << QPointF(434,447) << QPointF(322, 447) << QPointF(287,360);
    return p;
}

void Multiplexer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(boundingRect(),Qt::AlignCenter,"Multiplexer");
}

void Multiplexer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{        
    update();
    if(state)
        state = false;
    else
        state = true;
}

